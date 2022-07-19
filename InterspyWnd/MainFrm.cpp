// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "InterspyWnd.h"
#include "MainFrm.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_GO, OnGo)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(ID_GO, OnUpdateGo)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_NEXT_MESSAGE, OnNextMessage)
	ON_COMMAND(ID_PREV_MESSAGE, OnPrevMessage)
	ON_UPDATE_COMMAND_UI(ID_NEXT_MESSAGE, OnUpdateNextMessage)
	ON_UPDATE_COMMAND_UI(ID_PREV_MESSAGE, OnUpdatePrevMessage)
	ON_COMMAND(ID_CLEAR_DISABLED, OnClearDisabled)
	ON_UPDATE_COMMAND_UI(ID_CLEAR_DISABLED, OnUpdateClearDisabled)
	ON_COMMAND(ID_ITEM_ENABLE, OnItemEnable)
	ON_UPDATE_COMMAND_UI(ID_ITEM_ENABLE, OnUpdateItemEnable)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, OnUpdateClear)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, AFX_IDW_PANE_FIRST, OnCustomDrawTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bPaused = FALSE;
	m_dwCount = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->cx = 200;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_tree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 
						CRect(0, 0, 10, 10), this, AFX_IDW_PANE_FIRST))
		return -1;

	m_tree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// register a special class with the name of the app so
	// we can easily find it
	static WNDCLASS wndcls;
	static CString sClassName = "InterspyWnd";

	HINSTANCE hInst = AfxGetInstanceHandle();
	
	// see if the class already exists
	if (!::GetClassInfo(hInst, sClassName, &wndcls))
	{
		// get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		wndcls.style &= ~(CS_HREDRAW|CS_VREDRAW);
		
		// register a new class
		wndcls.lpszClassName = sClassName;
		wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME)); 
		
		ASSERT(wndcls.hIcon != NULL);
		
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}
	
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.dwExStyle |= WS_EX_TOPMOST;
	cs.lpszClass = sClassName;

	// restore window pos	
	DWORD dwTopLeft = MAKELONG(0, 0);
	DWORD dwBottomRight = MAKELONG(200, 640); // default

	CRegKey reg;
			
	if (reg.Open(HKEY_CURRENT_USER, L"Software\\AbstractSpoon\\InterSpy\\InterSpyWnd") == ERROR_SUCCESS)
	{
		reg.QueryValue(dwTopLeft, L"TopLeft");
		reg.QueryValue(dwBottomRight, L"BottomRight");
	}

	cs.x = LOWORD(dwTopLeft);
	cs.y = HIWORD(dwTopLeft);
	cs.cx = LOWORD(dwBottomRight) - cs.x;
	cs.cy = HIWORD(dwBottomRight) - cs.y;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CMainFrame::OnClose() 
{
	CFrameWnd::OnClose();
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	if (m_bPaused)
		return FALSE;

	if (!pCopyDataStruct)
		return FALSE;

	IS_COPYDATA* pData = (IS_COPYDATA*)pCopyDataStruct->lpData;

	switch (pData->uCmd)
	{
	case IS_CMD_ADDMSG:
		AddMsg(pData);
		return TRUE;

	case IS_CMD_RESET:
		OnClear();
		return TRUE;
	}

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CMainFrame::AddMsg(IS_COPYDATA* pData)
{
	// check msg exclusions
	BOOL bTemp;

	if (m_mapMsgExclusions.Lookup(pData->lParam, bTemp))
		return;

	// and hwnd exclusions
	if (m_mapHwndExclusions.Lookup((HWND)pData->wParam, bTemp))
		return;

	HTREEITEM hti = NULL;
	BOOL bOpen = FALSE;

	HWND hwnd = (HWND)pData->wParam;
	static TCHAR cClass[40], cCaption[128];
	
	if (!m_mapHwnds.Lookup(hwnd, hti))
	{
		hti = m_tree.InsertItem(L"");
		m_mapHwnds[hwnd] = hti;
	
		CString sHwnd;

		::GetClassName(hwnd, cClass, 40);
		::GetWindowText(hwnd, cCaption, 128);

		cClass[39] = 0;
		cCaption[127] = 0;

		sHwnd.Format(L"0x%08X '%s' (%s)", hwnd, cCaption, cClass);

		m_tree.SetItemText(hti, sHwnd);
		m_tree.SetItemData(hti, (DWORD)hwnd);
		m_tree.SetItemState(hti, TVIS_BOLD, TVIS_BOLD);
	}
	else
	{
		bOpen = (m_tree.GetItemState(hti, TVIS_EXPANDED) & TVIS_EXPANDED);

		// update caption if necessary
		if (pData->lParam == WM_SETTEXT || pData->lParam == WM_CREATE)
		{
			CString sHwnd;
			
			::GetClassName(hwnd, cClass, 40);
			::GetWindowText(hwnd, cCaption, 128);
			
			cClass[39] = 0;
			cCaption[127] = 0;
			
			sHwnd.Format(L"0x%08X '%s' (%s)", hwnd, cCaption, cClass);
			
			m_tree.SetItemText(hti, sHwnd);
		}
	}
	
	CString sMsg(pData->sMsg), sParams;
	CStringArray aParams;

	// extract message and params
	int nFind = sMsg.Find('|');

	if (nFind != -1)
	{
		sParams = sMsg.Mid(nFind + 1);
		pData->sMsg[nFind] = 0;
	}

	sMsg.Format(L"%s [%d]", pData->sMsg, ++m_dwCount);

	HTREEITEM htiMsg = m_tree.InsertItem(sMsg, hti);

	// make msg type and msg number into joint key
	m_tree.SetItemData(htiMsg, MAKELONG(LOWORD(m_dwCount), LOWORD(pData->lParam)));

	if (bOpen)
		m_tree.EnsureVisible(htiMsg);

	// parse params putting each param on a new line
	if (!sParams.IsEmpty())
	{
		do
		{
			int nFind = sParams.Find('|');

			if (nFind == -1)
			{
				m_tree.InsertItem(sParams, htiMsg);
				sParams.Empty();
			}
			else
			{
				m_tree.InsertItem(sParams.Left(nFind), htiMsg);
				sParams = sParams.Mid(nFind + 1);
			}
		}
		while (!sParams.IsEmpty());
	}

	// update prev/next msgs
	m_mapMsgs[m_dwCount] = htiMsg;
}

void CMainFrame::OnGo() 
{
	m_bPaused = FALSE;
}

void CMainFrame::OnPause() 
{
	m_bPaused = !m_bPaused;	
}

void CMainFrame::OnClear() 
{
	m_mapHwnds.RemoveAll();
	m_mapMsgs.RemoveAll();
	m_tree.DeleteAllItems();
	m_dwCount = 0;
}

void CMainFrame::OnUpdateGo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bPaused ? 0 : 1);
}

void CMainFrame::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bPaused ? 1 : 0);
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();

	// save window pos	
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);

	CRegKey reg;
			
	if (reg.Create(HKEY_CURRENT_USER, L"Software\\AbstractSpoon\\InterSpy\\InterSpyWnd") == ERROR_SUCCESS)
	{
		DWORD dwTopLeft = MAKELONG(wp.rcNormalPosition.left, wp.rcNormalPosition.top);
		DWORD dwBottomRight = MAKELONG(wp.rcNormalPosition.right, wp.rcNormalPosition.bottom);
				
		reg.SetValue(dwTopLeft, L"TopLeft");
		reg.SetValue(dwBottomRight, L"BottomRight");
	}
}

void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd == &m_tree)
	{
		CPoint ptHittest(point);

		m_tree.ScreenToClient(&ptHittest);

		int nSubMenu = 0;
		UINT uFlags = 0;
		HTREEITEM hti = m_tree.HitTest(ptHittest, &uFlags);

		if ((hti != NULL) && (TVHT_ONITEM & uFlags))
		{
			m_tree.SelectItem(hti);

			if (IsItemHwnd(hti)) 
				nSubMenu = 1;

			else if (IsItemMsg(hti))
				nSubMenu = 2;
		}
		
		CMenu menu;
		
		if (menu.LoadMenu(IDR_CONTEXT))
		{
			CMenu* pMenu = menu.GetSubMenu(nSubMenu);
			
			if (pMenu)
				pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
		}
	}
}

void CMainFrame::OnItemEnable() 
{
	HTREEITEM hti = m_tree.GetSelectedItem();

	if (hti)
	{
		if (IsItemMsg(hti))
		{
			BOOL bTemp;
			UINT uMsg = ItemMsg(hti);

			if (m_mapMsgExclusions.Lookup(uMsg, bTemp))
				m_mapMsgExclusions.RemoveKey(uMsg);
			else
				m_mapMsgExclusions[uMsg] = 1;

			m_tree.Invalidate(FALSE);
		}	
		else if (IsItemHwnd(hti))
		{
			BOOL bTemp;
			HWND hwnd = (HWND)m_tree.GetItemData(hti);

			if (m_mapHwndExclusions.Lookup(hwnd, bTemp))
				m_mapHwndExclusions.RemoveKey(hwnd);
			else
				m_mapHwndExclusions[hwnd] = 1;

			m_tree.Invalidate(FALSE);
		}
	}
}

void CMainFrame::OnUpdateItemEnable(CCmdUI* pCmdUI) 
{
	if (pCmdUI->m_pMenu)
	{
		HTREEITEM hti = m_tree.GetSelectedItem();

		if (hti)
		{
			if (IsItemMsg(hti))
			{
				BOOL bTemp;
				UINT uMsg = ItemMsg(hti);

				if (m_mapMsgExclusions.Lookup(uMsg, bTemp))
					pCmdUI->SetText(L"Enable Message\tSpacebar");
				else
					pCmdUI->SetText(L"Disable Message\tSpacebar");
			}	
			else if (IsItemHwnd(hti))
			{
				BOOL bTemp;
				HWND hwnd = (HWND)m_tree.GetItemData(hti);

				if (m_mapHwndExclusions.Lookup(hwnd, bTemp))
					pCmdUI->SetText(L"Enable Window\tSpacebar");
				else
					pCmdUI->SetText(L"Disable Window\tSpacebar");
			}
		}
		else
		{
			pCmdUI->SetText(L"Enable/Disable\tSpacebar");
			pCmdUI->Enable(FALSE);
		}
	}
}

void CMainFrame::OnNextMessage() 
{
	HTREEITEM hti = m_tree.GetSelectedItem();

	if (hti && IsItemMsg(hti))
	{
		DWORD dwPos = ItemPos(hti);
		HTREEITEM htiNext = NULL;
		
		// note: next message may have been deleted 
		while (!m_mapMsgs.Lookup(dwPos + 1, htiNext) && dwPos < m_dwCount)
			dwPos++;

		if (htiNext)
			m_tree.SelectItem(htiNext);
	}
}

void CMainFrame::OnPrevMessage() 
{
	HTREEITEM hti = m_tree.GetSelectedItem();

	if (hti && IsItemMsg(hti))
	{
		DWORD dwPos = ItemPos(hti);
		HTREEITEM htiPrev = NULL;
		
		// note: prev message may have been deleted 
		while (!m_mapMsgs.Lookup(dwPos - 1, htiPrev) && dwPos)
			dwPos--;

		if (htiPrev)
			m_tree.SelectItem(htiPrev);
	}
}

BOOL CMainFrame::IsItemMsg(HTREEITEM hti)
{
	HTREEITEM htiParent = m_tree.GetParentItem(hti);

	if (!htiParent) // HWND 
		return FALSE;

	// else
	return (m_tree.GetParentItem(htiParent) == NULL);
}

BOOL CMainFrame::IsItemHwnd(HTREEITEM hti)
{
	return (m_tree.GetParentItem(hti) == NULL);
}


void CMainFrame::OnUpdateNextMessage(CCmdUI* pCmdUI) 
{
	HTREEITEM hti = m_tree.GetSelectedItem();

	pCmdUI->Enable(hti && IsItemMsg(hti) && ItemPos(hti) < m_dwCount);
}

void CMainFrame::OnUpdatePrevMessage(CCmdUI* pCmdUI) 
{
	HTREEITEM hti = m_tree.GetSelectedItem();

	pCmdUI->Enable(hti && IsItemMsg(hti) && ItemPos(hti) > 1);
}

void CMainFrame::OnCustomDrawTree(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NMCUSTOMDRAW* pNMCD = (NMCUSTOMDRAW*)pNotifyStruct;

	if (pNMCD->dwDrawStage == CDDS_PREPAINT)
		*pResult = CDRF_NOTIFYITEMDRAW;	
		
	else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
	{
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);
		NMTVCUSTOMDRAW* pTVCD = (NMTVCUSTOMDRAW*)pNMCD;

		HTREEITEM hti = (HTREEITEM)pTVCD->nmcd.dwItemSpec;
		LPARAM lParam = pTVCD->nmcd.lItemlParam;

		if (IsItemMsg(hti))
		{
			HTREEITEM htiParent = m_tree.GetParentItem(hti);
			ASSERT (IsItemHwnd(htiParent));

			BOOL bTemp;
			HWND hwnd = (HWND)m_tree.GetItemData(htiParent);

			if (m_mapHwndExclusions.Lookup(hwnd, bTemp))
			{
				pTVCD->clrText = ::GetSysColor(COLOR_3DSHADOW);
				*pResult = CDRF_NEWFONT;
			}
			else
			{
				UINT uMsgType = (UINT)HIWORD(lParam);

				if (m_mapMsgExclusions.Lookup(uMsgType, bTemp))
				{
					pTVCD->clrText = ::GetSysColor(COLOR_3DFACE);
					*pResult = CDRF_NEWFONT;
				}
			}
		}
		else if (IsItemHwnd(hti))
		{
			BOOL bTemp;

			if (m_mapHwndExclusions.Lookup((HWND)lParam, bTemp))
			{
				pTVCD->clrText = ::GetSysColor(COLOR_3DSHADOW);
				*pResult = CDRF_NEWFONT;
			}
		}
	}
}

void CMainFrame::OnClearDisabled() 
{
	if (m_mapMsgExclusions.GetCount())
	{
		CWaitCursor cursor;
		BOOL bTemp;

		m_tree.SetRedraw(FALSE);

		// iterate all top level items and their children
		HTREEITEM htiWnd = m_tree.GetNextItem(NULL, TVGN_CHILD);

		while (htiWnd)
		{
			HTREEITEM htiMsg = m_tree.GetChildItem(htiWnd);

			while (htiMsg)
			{
				HTREEITEM htiNext = m_tree.GetNextItem(htiMsg, TVGN_NEXT);
				UINT uMsgType = ItemMsg(htiMsg);

				if (m_mapMsgExclusions.Lookup(uMsgType, bTemp))
				{
					m_mapMsgs.RemoveKey(ItemPos(htiMsg)); // must do this first
					m_tree.DeleteItem(htiMsg);
				}

				htiMsg = htiNext;
			}

			htiWnd = m_tree.GetNextItem(htiWnd, TVGN_NEXT);
		}

		m_tree.SetRedraw(TRUE);
	}
}

void CMainFrame::OnUpdateClearDisabled(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_mapMsgExclusions.GetCount() && m_tree.GetCount());
}


void CMainFrame::OnUpdateClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_tree.GetCount());	
}

void CMainFrame::OnFileSave() 
{
	CFileDialog dialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"XML (*.xml)|*.xml|Plain Text (*.txt)|*.txt||", this);

	if (dialog.DoModal() == IDOK)
	{
		CString sFilePath = dialog.GetPathName();
		BOOL bXml = (dialog.m_ofn.nFilterIndex == 1);

		// ensure the file has an appropriate extension
		TCHAR cExt[_MAX_EXT];
		_tsplitpath(sFilePath, NULL, NULL, NULL, cExt);

		if (!cExt[0]) // no extension
		{
			// add default
			sFilePath += bXml ? L".xml" : L".txt";
			AfxMessageBox(sFilePath);
		}

		VERIFY(bXml ? SaveMessagesXml(sFilePath) : SaveMessagesText(sFilePath));
		
		UpdateData(FALSE);
	}
}

void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_tree.GetCount());	
}

BOOL CMainFrame::SaveMessagesXml(LPCTSTR szFilePath)
{
	CStdioFile file;

	if (file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite))
	{
		file.WriteString(L"<INTERSPYLOG>");

		BOOL bWasPaused = m_bPaused;
		m_bPaused = TRUE;

		// iterate all items
		HTREEITEM htiWnd = m_tree.GetNextItem(NULL, TVGN_CHILD);
		BOOL bTemp;
		CString sText;
		
		while (htiWnd)
		{
			HWND hWnd = (HWND)m_tree.GetItemData(htiWnd);

			if (!m_mapHwndExclusions.Lookup(hWnd, bTemp))
			{
				sText.Format(L"<_ hwnd = \"%s\">\n", GetItemText(htiWnd));
				file.WriteString(sText);
				
				// messages
				HTREEITEM htiMsg = m_tree.GetChildItem(htiWnd);

				while (htiMsg)
				{
					UINT uMsgType = ItemMsg(htiMsg);

					if (!m_mapMsgExclusions.Lookup(uMsgType, bTemp))
					{
						sText.Format(L"<_ msg = \"%s\">\n", GetItemText(htiMsg));
						file.WriteString(sText);

						// wParam / lParam
						HTREEITEM htiParam = m_tree.GetChildItem(htiMsg);

						while (htiParam)
						{
							sText.Format(L"<_ param = \"%s\"/>\n", GetItemText(htiParam));
							file.WriteString(sText);

							htiParam = m_tree.GetNextItem(htiParam, TVGN_NEXT);
						}

						file.WriteString(L"</_>\n");
					}

					htiMsg = m_tree.GetNextItem(htiMsg, TVGN_NEXT);
				}

				file.WriteString(L"</_>\n");
			}

			htiWnd = m_tree.GetNextItem(htiWnd, TVGN_NEXT);
		}

		m_bPaused = bWasPaused;
		
		file.WriteString(L"</INTERSPYLOG>\n");
		file.Close();

		return TRUE;
	}

	return FALSE;
}

BOOL CMainFrame::SaveMessagesText(LPCTSTR szFilePath)
{
	CStdioFile file;

	if (file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite))
	{
		file.WriteString(L"INTERSPYLOG\n\n");

		BOOL bWasPaused = m_bPaused;
		m_bPaused = TRUE;

		// iterate all items
		HTREEITEM htiWnd = m_tree.GetNextItem(NULL, TVGN_CHILD);
		BOOL bTemp;
		CString sText;
		
		while (htiWnd)
		{
			HWND hWnd = (HWND)m_tree.GetItemData(htiWnd);

			if (!m_mapHwndExclusions.Lookup(hWnd, bTemp))
			{
				sText.Format(L"hwnd = %s\n", GetItemText(htiWnd));
				file.WriteString(sText);
				
				// messages
				HTREEITEM htiMsg = m_tree.GetChildItem(htiWnd);

				while (htiMsg)
				{
					UINT uMsgType = ItemMsg(htiMsg);

					if (!m_mapMsgExclusions.Lookup(uMsgType, bTemp))
					{
						sText.Format(L"    %s\n", GetItemText(htiMsg));

						// wParam / lParam
						HTREEITEM htiParam = m_tree.GetChildItem(htiMsg);
						file.WriteString(sText);

						while (htiParam)
						{
							sText.Format(L"        %s\n", GetItemText(htiParam));
							file.WriteString(sText);

							htiParam = m_tree.GetNextItem(htiParam, TVGN_NEXT);
						}
					}

					htiMsg = m_tree.GetNextItem(htiMsg, TVGN_NEXT);
				}

				file.WriteString(L"\n");
			}

			htiWnd = m_tree.GetNextItem(htiWnd, TVGN_NEXT);
		}

		m_bPaused = bWasPaused;
		file.Close();

		return TRUE;
	}

	return FALSE;
}

CString CMainFrame::GetItemText(HTREEITEM hti)
{
	CString sText = m_tree.GetItemText(hti);

	sText.Replace('\"', '\'');
	sText.Replace('<', '·');
	sText.Replace('>', '·');

	return sText;
}
