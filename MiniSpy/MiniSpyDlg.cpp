// MiniSpyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiniSpy.h"
#include "MiniSpyDlg.h"
#include "about.h"
#include "styles.h" 

#include <Afxpriv.h>
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// helper structures

// pick corner
enum
{
	TOPLEFT,
	TOPRIGHT,
	BOTTOMRIGHT,
	BOTTOMLEFT,
};

// supported attributes
enum
{
	ATTRIB_SEPARATOR = -1,
	ATTRIB_CLASS,
	ATTRIB_HANDLE,
	ATTRIB_CAPTION,
	ATTRIB_CLASSSTYLE,
	ATTRIB_WNDSTYLE,
	ATTRIB_WNDEXSTYLE,
	ATTRIB_CTLSTYLE,
	ATTRIB_WNDPROPS,
	ATTRIB_PARENTHANDLE,
	ATTRIB_PARENTCAPTION,
	ATTRIB_PARENTCLASS,
	ATTRIB_TOPLEVELPARENT,
	ATTRIB_WINDOWRECT,
	ATTRIB_CLIENTRECT,
	ATTRIB_CONTROLID,
	ATTRIB_HITTEST,
/*	ATTRIB_,
	ATTRIB_,
	ATTRIB_,
	ATTRIB_,
*/
};

struct Attribute
{
	LPCTSTR szAttribute; // descriptive label
	int nAttribute; // enum above
};

// the actual row layout
static Attribute Attributes[] = 
{
	{ "Class Name", ATTRIB_CLASS },
	{ "", ATTRIB_SEPARATOR },
	{ "Window Handle", ATTRIB_HANDLE },
	{ "Window Caption", ATTRIB_CAPTION },
	{ "", ATTRIB_SEPARATOR },
	{ "Class Styles", ATTRIB_CLASSSTYLE },
	{ "Window Styles", ATTRIB_WNDSTYLE },
	{ "Extended Styles", ATTRIB_WNDEXSTYLE },
	{ "Control Styles", ATTRIB_CTLSTYLE },
	{ "Window Properties", ATTRIB_WNDPROPS },
	{ "", ATTRIB_SEPARATOR },
	{ "Parent Handle", ATTRIB_PARENTHANDLE },
	{ "Parent Caption", ATTRIB_PARENTCAPTION },
	{ "Parent Class", ATTRIB_PARENTCLASS },
	{ "", ATTRIB_SEPARATOR },
	{ "Top-Level Parent", ATTRIB_TOPLEVELPARENT },
	{ "", ATTRIB_SEPARATOR },
	{ "Window Rectangle", ATTRIB_WINDOWRECT },
	{ "Client Rectangle", ATTRIB_CLIENTRECT },
	{ "", ATTRIB_SEPARATOR },
	{ "Control ID", ATTRIB_CONTROLID },
	{ "", ATTRIB_SEPARATOR },
	{ "Hit-Test Result", ATTRIB_HITTEST },
/*	{ "", ATTRIB_SEPARATOR },
	{ , },
	{ , },
	{ , },
	{ , },
*/
};

/////////////////////////////////////////////////////////////////////////////
// CMiniSpyDlg dialog

CMiniSpyDlg::CMiniSpyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiniSpyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMiniSpyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_curWnd.SetWnd(NULL);

	m_nCorner = TOPLEFT;
	m_bLockUpdates = FALSE;

	m_hAccelerator = ::LoadAccelerators(NULL, MAKEINTRESOURCE(IDR_ACCELERATOR));
}

void CMiniSpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiniSpyDlg)
	DDX_Control(pDX, IDC_FILTER, m_cbFilter);
	DDX_Control(pDX, IDC_ATTRIBUTES, m_lcAttributes);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMiniSpyDlg, CDialog)
	//{{AFX_MSG_MAP(CMiniSpyDlg)
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVING()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_FILTER, OnSelchangeFilter)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_WM_ACTIVATEAPP()
	ON_COMMAND(ID_RESTORESIZE, OnRestoresize)
	ON_COMMAND_RANGE(ID_TOPLEFT, ID_BOTTOMLEFT, OnChangeCorner)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_GOTOCHILD, OnGotoChild)
	ON_COMMAND(ID_GOTONEXT, OnGotoNextWindow)
	ON_COMMAND(ID_GOTOPARENT, OnGotoParent)
	ON_COMMAND(ID_LOCKUPDATES, OnLockUpdates)
	ON_COMMAND(ID_GOTOPREV, OnGotoPreviousWindow)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnNeedTooltip)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiniSpyDlg message handlers

BOOL CMiniSpyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// toolbar
	VERIFY (m_toolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY)
			&& m_toolbar.LoadToolBar(IDR_MINISPY));

	// very important - turn OFF all the auto positioning and sizing
	// by default have no borders
	int nStyle = m_toolbar.GetBarStyle();

	nStyle &= ~(CCS_NORESIZE | CCS_NOPARENTALIGN);
	nStyle &= ~(CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT);

	m_toolbar.SetBarStyle(nStyle);

	// Set the icon for this dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// init attribute list
	m_lcAttributes.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	m_lcAttributes.InsertColumn(0, "Attribute", LVCFMT_LEFT, 100);
	m_lcAttributes.InsertColumn(1, "Value", LVCFMT_LEFT, 1500);

	// add the attribute labels
	int nAttributes = sizeof(Attributes) / sizeof(Attribute);

	for (int nAttribute = 0; nAttribute < nAttributes; nAttribute++)
	{
		int nIndex = m_lcAttributes.InsertItem(nAttribute, Attributes[nAttribute].szAttribute);
		m_lcAttributes.SetItemData(nIndex, Attributes[nAttribute].nAttribute);
	}
	
	// disable tracking in the list
	CWnd* pHeader = m_lcAttributes.GetDlgItem(0);
	pHeader->EnableWindow(FALSE);

	// grab the current window
	UpdateCurrentWindow();

	// set a 1/2 second timer for updating the current window
	SetTimer(1, 500, NULL);

	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDC_FILTER), "Control Filter");

	// save the original window size
	CRect rWindow;
	GetWindowRect(rWindow);
	m_sizeOriginal = CSize(rWindow.Width(), rWindow.Height());

	// force a resize for the toolbar
	CRect rClient;
	GetClientRect(rClient);
	PostMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(rClient.Width(), rClient.Height()));

	// init the corner state buttons
	OnChangeCorner(ID_TOPLEFT);

	// set the min drop width of the control filter
	m_cbFilter.SetDroppedWidth(50);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMiniSpyDlg::OnAppAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CMiniSpyDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);

	UpdateCurrentWindow();
}

void CMiniSpyDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (m_toolbar.GetSafeHwnd())
		m_toolbar.MoveWindow(0, 1, 24, cy);
	
	// stretch the controls to fit the window
	if (m_lcAttributes.GetSafeHwnd())
	{
		CRect rWindow;

		m_lcAttributes.GetWindowRect(rWindow);
		ScreenToClient(rWindow);
		
		rWindow.left = 26;
		rWindow.right = cx;
		rWindow.bottom = cy;

		m_lcAttributes.MoveWindow(rWindow);
	}

	if (m_cbFilter.GetSafeHwnd())
	{
		CRect rWindow;

		m_cbFilter.GetWindowRect(rWindow);
		ScreenToClient(rWindow);
		
		rWindow.left = 26;
		rWindow.right = cx;

		m_cbFilter.MoveWindow(rWindow);
	}

}

void CMiniSpyDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo(lpMMI);

	lpMMI->ptMinTrackSize.x = 50;
	lpMMI->ptMinTrackSize.y = 100;
}

void CMiniSpyDlg::OnMoving(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnMoving(fwSide, pRect);
	
	UpdateCurrentWindow();
}

void CMiniSpyDlg::UpdateCurrentWindow(BOOL bForce)
{
	if (!m_lcAttributes.GetSafeHwnd())
		return;

	// needs a bit more than just GetCurrentCorner in order to avoid
	// problems with group boxes etc
	CWnd* pWnd = m_bLockUpdates ? m_curWnd.GetWnd() : RealWindowFromPoint(GetCurrentCorner());

	// only update the window its its changed
	if (!bForce && m_curWnd.IsSameAs(pWnd))
		return;

	// else
	if (pWnd)
		pWnd = ::IsWindow(*pWnd) ? pWnd : NULL;

	SetCurrentWindow(pWnd);
}

void CMiniSpyDlg::SetCurrentWindow(CWnd* pWnd)
{
	m_curWnd.SetWnd(pWnd);

	// update the caption
	CString sCaption = GetWindowText(pWnd), sClassName = GetClassName(pWnd);

	if (sCaption.IsEmpty())
		sCaption = sClassName;

	sCaption = pWnd ? "MiniSpy - " + sCaption : "MiniSpy";
	SetWindowText(sCaption);

	// update the attributes
	RefreshAttributes(pWnd);

	// update filter combo
	if (m_cbFilter.FindString(-1, sClassName) != -1)
		m_cbFilter.SelectString(-1, sClassName);
	else
		m_cbFilter.SetCurSel(-1);

	// disable the filter and refresh button if no window is found
	m_cbFilter.EnableWindow(pWnd != NULL);

	// set the enable states of the goto buttons
	m_toolbar.GetToolBarCtrl().EnableButton(ID_GOTOPARENT, (pWnd && pWnd->GetParent()));
	m_toolbar.GetToolBarCtrl().EnableButton(ID_GOTOCHILD, (pWnd && pWnd->GetWindow(GW_CHILD)));
	m_toolbar.GetToolBarCtrl().EnableButton(ID_GOTONEXT, (pWnd && pWnd->GetNextWindow()));
	m_toolbar.GetToolBarCtrl().EnableButton(ID_GOTOPREV, (pWnd && pWnd->GetNextWindow(GW_HWNDPREV)));

	// disable lock update button if the wnd is a menu
	sClassName = GetClassName(pWnd, FALSE);
//	m_toolbar.GetToolBarCtrl().EnableButton(ID_LOCKUPDATES, sClassName != "#32768");
}

void CMiniSpyDlg::RefreshAttributes(CWnd* pWnd)
{
	int nAttribs = sizeof(Attributes) / sizeof(Attribute);

	for (int nAttrib = 0; nAttrib < nAttribs; nAttrib++)
	{
		CString sLabel;
		CRect rWindow, rClient;
		CWnd* pParent;

		if (pWnd)
		{
			int nAttribute = m_lcAttributes.GetItemData(nAttrib);

			switch (nAttribute)
			{
				case ATTRIB_CLASS:
					sLabel = GetClassName(pWnd);
					break;

				case ATTRIB_HANDLE:
					sLabel.Format("0x%08X", pWnd->GetSafeHwnd());
					break;

				case ATTRIB_CAPTION:
					sLabel = GetWindowText(pWnd);
					break;

				case ATTRIB_CLASSSTYLE:
					sLabel = GetClassStyles(pWnd);
					break;

				case ATTRIB_WNDSTYLE:
					sLabel = GetWindowStyles(pWnd);
					break;

				case ATTRIB_WNDPROPS:
					sLabel = GetWindowProperties(pWnd);
					break;

				case ATTRIB_WNDEXSTYLE:
					sLabel = GetWindowExStyles(pWnd);
					break;

				case ATTRIB_CTLSTYLE:
					sLabel = GetControlStyles(pWnd);
					break;

				case ATTRIB_PARENTHANDLE:
					pParent = pWnd->GetParent();

					if (pParent)
						sLabel.Format("0x%08X", pParent->GetSafeHwnd());
					break;

				case ATTRIB_PARENTCAPTION:
					sLabel = GetWindowText(pWnd->GetParent());
					break;

				case ATTRIB_PARENTCLASS:
					sLabel = GetClassName(pWnd->GetParent());
					break;

				case ATTRIB_TOPLEVELPARENT:
					pParent = pWnd->GetTopLevelParent();

					if (pParent && pParent != pWnd)
					{
						CString sText = GetWindowText(pParent);

						if (sText.IsEmpty())
							sLabel.Format("0x%08X", pParent->GetSafeHwnd());
						else
							sLabel.Format("0x%08X (%s)", pParent->GetSafeHwnd(), sText);
					}
					break;

				case ATTRIB_WINDOWRECT:
					pWnd->GetWindowRect(rWindow);
					sLabel.Format("(%d, %d) - (%d, %d), %d x %d", rWindow.left, rWindow.top, rWindow.right, rWindow.bottom, rWindow.Width(), rWindow.Height()); 
					break;

				case ATTRIB_CLIENTRECT: // in window coordinates
					pWnd->GetClientRect(rClient);
					pWnd->ClientToScreen(rClient);
					sLabel.Format("(%d, %d) - (%d, %d), %d x %d", rClient.left, rClient.top, rClient.right, rClient.bottom, rClient.Width(), rClient.Height()); 
					break;

				case ATTRIB_CONTROLID:
					sLabel.Format("0x%08X (%d)", pWnd->GetDlgCtrlID(), pWnd->GetDlgCtrlID());
					break;

				case ATTRIB_HITTEST:
					sLabel = DoHitTest(pWnd);
					break;

				default:;
			}
		}

		CString sExistingLabel = m_lcAttributes.GetItemText(nAttrib, 1);

		if (sLabel != sExistingLabel)
			m_lcAttributes.SetItemText(nAttrib, 1, sLabel);
	}
}

void CMiniSpyDlg::RefreshHitTest(CWnd* pWnd)
{
	if (!pWnd)
		return;

	int nAttribs = sizeof(Attributes) / sizeof(Attribute);

	for (int nAttrib = 0; nAttrib < nAttribs; nAttrib++)
	{
		int nAttribute = m_lcAttributes.GetItemData(nAttrib);
		{
			if (nAttribute == ATTRIB_HITTEST)
			{
				CString sLabel = DoHitTest(pWnd);
				CString sExistingLabel = m_lcAttributes.GetItemText(nAttrib, 1);

				if (sLabel != sExistingLabel)
					m_lcAttributes.SetItemText(nAttrib, 1, sLabel);

				break;
			}
		}
	}
}

CString CMiniSpyDlg::GetClassStyles(CWnd* pWnd)
{
	if (!pWnd)
		return "";

	CString sStyles, sClassName = GetClassName(pWnd, FALSE);

	WNDCLASS wndcls;
	
	if (::GetClassInfo(AfxGetInstanceHandle(), sClassName, &wndcls))
	{
		int nStyles = sizeof(ClassStyles) / sizeof(Style);

		for (int nStyle = 0; nStyle < nStyles; nStyle++)
		{
			DWORD dwStyle = ClassStyles[nStyle].dwStyle;

			if ((wndcls.style & dwStyle) == dwStyle)
			{
				if (!sStyles.IsEmpty())
					sStyles += ", ";

				sStyles += ClassStyles[nStyle].szStyle;
			}
		}
	}

	return sStyles;
}

CString CMiniSpyDlg::GetWindowStyles(CWnd* pWnd)
{
	if (!pWnd)
		return "";

	CString sStyles;
	DWORD dwWndStyle = pWnd->GetStyle();

	int nStyles = sizeof(WindowStyles) / sizeof(Style);
	
	for (int nStyle = 0; nStyle < nStyles; nStyle++)
	{
		DWORD dwStyle = WindowStyles[nStyle].dwStyle;
		
		if ((dwWndStyle & dwStyle) == dwStyle)
		{
			if (!sStyles.IsEmpty())
				sStyles += ", ";
			
			sStyles += WindowStyles[nStyle].szStyle;
		}
	}

	return sStyles;
}

CString CMiniSpyDlg::GetWindowExStyles(CWnd* pWnd)
{
	if (!pWnd)
		return "";

	CString sStyles;
	DWORD dwWndStyle = pWnd->GetExStyle();

	int nStyles = sizeof(WindowExStyles) / sizeof(Style);
	
	for (int nStyle = 0; nStyle < nStyles; nStyle++)
	{
		DWORD dwStyle = WindowExStyles[nStyle].dwStyle;
		
		if ((dwWndStyle & dwStyle) == dwStyle)
		{
			if (!sStyles.IsEmpty())
				sStyles += ", ";
			
			sStyles += WindowExStyles[nStyle].szStyle;
		}
	}

	return sStyles;
}

CString CMiniSpyDlg::GetClassName(CWnd* pWnd, BOOL bDecorative)
{
	if (!pWnd)
		return "";

	CString sClassName;

	::GetClassName(pWnd->GetSafeHwnd(), sClassName.GetBuffer(30), 29);
	sClassName.ReleaseBuffer();

	// special cases
	if (bDecorative)
	{
		if (sClassName == "#32768")
			sClassName = "Menu (#32768)";

		else if (sClassName == "#32769")
			sClassName = "Desktop (#32769)";

		else if (sClassName == "#32770")
			sClassName = "Dialog Box (#32770)";

		else if (sClassName == "#32771")
			sClassName = "Task Switcher (#32771)";

		else if (sClassName == "#32772")
			sClassName = "Icon Title (#32772)";
	}

	return sClassName;
}

CString CMiniSpyDlg::GetControlStyles(CWnd* pWnd, LPCTSTR szClass)
{
	if (!pWnd)
		return "";

	CString sStyles, sClassName(szClass);

	if (!szClass || sClassName.IsEmpty())
		sClassName = GetClassName(pWnd);

	DWORD dwWndStyle = pWnd->GetStyle();

	// find the first entry for this class name
	int nStyle = 0, nStyles = sizeof(ControlStyles) / sizeof(CtlStyle);
	
	while (nStyle < nStyles && sClassName.CompareNoCase(ControlStyles[nStyle].szControlClass))
		nStyle++;

	if (nStyle < nStyles)
	{
		while (nStyle < nStyles && !sClassName.CompareNoCase(ControlStyles[nStyle].szControlClass))
		{
			if (!ControlStyles[nStyle].bExStyle)
			{
				DWORD dwStyle = ControlStyles[nStyle].dwStyle;
				DWORD dwMask = ControlStyles[nStyle].dwMask;
				
				// a bit of mucking about required because some styles are masked
				if (!dwMask)
					dwMask = dwStyle;

				if ((dwWndStyle & dwMask) == dwStyle)
				{
					if (!sStyles.IsEmpty())
						sStyles += ", ";
					
					sStyles += ControlStyles[nStyle].szStyle;
				}
			}
			nStyle++;
		}
	}

	// base class?
	CString sBaseClass = GetBaseClass(sClassName);

	if (!sBaseClass.IsEmpty())
	{
		CString sBaseStyles = GetControlStyles(pWnd, sBaseClass);

		if (!sBaseStyles.IsEmpty())
		{
			if (!sStyles.IsEmpty())
				sStyles += ", ";
					
			sStyles += sBaseStyles;
		}
	}

	// ex styles?
	CString sExStyles = GetControlExStyles(pWnd, sClassName);

	if (!sExStyles.IsEmpty())
	{
		if (!sStyles.IsEmpty())
			sStyles += ", ";
					
		sStyles += sExStyles;
	}

	return sStyles;
}

CString CMiniSpyDlg::GetControlExStyles(CWnd* pWnd, LPCTSTR szClass)
{
	if (!pWnd)
		return "";

	CString sStyles, sClassName(szClass);

	if (!szClass)
		sClassName = GetClassName(pWnd);

	DWORD dwExStyleMsg = GetExStyleMsg(sClassName);

	if (!dwExStyleMsg)
		return "";

	DWORD dwWndExStyle = pWnd->SendMessage(dwExStyleMsg, 0, 0L);

	// find the first entry for this class name
	int nStyle = 0, nStyles = sizeof(ControlStyles) / sizeof(CtlStyle);
	
	while (nStyle < nStyles && sClassName.CompareNoCase(ControlStyles[nStyle].szControlClass))
		nStyle++;

	if (nStyle < nStyles)
	{
		while (nStyle < nStyles && !sClassName.CompareNoCase(ControlStyles[nStyle].szControlClass))
		{
			if (ControlStyles[nStyle].bExStyle)
			{
				DWORD dwExStyle = ControlStyles[nStyle].dwStyle;
				DWORD dwExMask = ControlStyles[nStyle].dwMask;
				
				// a bit of mucking about required because some styles are masked
				if (!dwExMask)
					dwExMask = dwExStyle;

				if ((dwWndExStyle & dwExMask) == dwExStyle)
				{
					if (!sStyles.IsEmpty())
						sStyles += ", ";
					
					sStyles += ControlStyles[nStyle].szStyle;
				}
			}

			nStyle++;
		}
	}

	// base class?
	CString sBaseClass = GetBaseClass(sClassName);

	if (!sBaseClass.IsEmpty())
	{
		CString sBaseStyles = GetControlExStyles(pWnd, sBaseClass);

		if (!sBaseStyles.IsEmpty())
		{
			if (!sStyles.IsEmpty())
				sStyles += ", ";
					
			sStyles += sBaseStyles;
		}
	}

	return sStyles;
}

void CMiniSpyDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1 && !m_cbFilter.GetDroppedState())
		UpdateCurrentWindow();

	if (!m_bLockUpdates)
		RefreshHitTest(CWnd::FromHandle(m_curWnd.hWnd)); // always

	CDialog::OnTimer(nIDEvent);
}

CString CMiniSpyDlg::GetBaseClass(LPCTSTR szClass)
{
	int nControl = sizeof(Controls) / sizeof(Control); 

	while (nControl--)
	{
		if (CString(szClass).CompareNoCase(Controls[nControl].szControlClass) == 0)
			return Controls[nControl].szBaseClass;
	}

	return "";
}

DWORD CMiniSpyDlg::GetExStyleMsg(LPCTSTR szClass)
{
	int nControl = sizeof(Controls) / sizeof(Control); 

	while (nControl--)
	{
		if (CString(szClass).CompareNoCase(Controls[nControl].szControlClass) == 0)
			return Controls[nControl].dwExStyleMsg;
	}

	return 0;
}

void CMiniSpyDlg::OnSelchangeFilter() 
{
	if (m_curWnd.hWnd)
	{
		CString sClassName;
		m_cbFilter.GetLBText(m_cbFilter.GetCurSel(), sClassName);

		// find the control attribute row via its lParam value
		LVFINDINFO lvfi;

		lvfi.flags = LVFI_PARAM;
		lvfi.lParam = ATTRIB_CTLSTYLE;

		int nIndex = m_lcAttributes.FindItem(&lvfi);
		ASSERT (nIndex >= 0);

		// update only the control styles
		CString sLabel = GetControlStyles(CWnd::FromHandle(m_curWnd.hWnd), sClassName);
		CString sExistingLabel = m_lcAttributes.GetItemText(nIndex, 1);

		if (sLabel != sExistingLabel)
			m_lcAttributes.SetItemText(nIndex, 1, sLabel);
	}
}

void CMiniSpyDlg::OnRefresh() 
{
	// refresh all
	UpdateCurrentWindow(TRUE);
}

CString CMiniSpyDlg::GetWindowText(CWnd* pWnd)
{
	// ::GetWindowText does not always seem to work
	CString sText;

	if (pWnd)
	{
		pWnd->SendMessage(WM_GETTEXT, 256, (LPARAM)(LPCTSTR)sText.GetBuffer(257));
		sText.ReleaseBuffer();
	}

	return sText;
}


void CMiniSpyDlg::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	// a bit of trickery else the tooltips appear behind the main window
	// if we are active then remove topmost attribute because we are topmost anyway
	// else set it so that we remain topmost
	if (bActive)
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	else
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	
	CDialog::OnActivateApp(bActive, hTask);
}

BOOL CMiniSpyDlg::PreTranslateMessage(MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);

	if (::TranslateAccelerator(*this, m_hAccelerator, pMsg))
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CMiniSpyDlg::OnRestoresize() 
{
	CRect rWindow;
	GetWindowRect(rWindow);

	rWindow.right = rWindow.left + m_sizeOriginal.cx;
	rWindow.bottom = rWindow.top + m_sizeOriginal.cy;

	MoveWindow(rWindow);
}

void CMiniSpyDlg::OnChangeCorner(UINT nID) 
{
	m_toolbar.GetToolBarCtrl().CheckButton(m_nCorner + ID_TOPLEFT, FALSE);

	m_nCorner = (nID - ID_TOPLEFT);

	m_toolbar.GetToolBarCtrl().CheckButton(m_nCorner + ID_TOPLEFT, TRUE);
	
	UpdateCurrentWindow(TRUE);
}

BOOL CMiniSpyDlg::OnNeedTooltip(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXT);

    // to be thorough we will need to handle UNICODE versions of the message also !!
    TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
 
	UINT nID = pNMHDR->idFrom;

    if (pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool 
        nID = ::GetDlgCtrlID((HWND)nID);
    }

    CString strTipText = GetTip(nID);

    if (!strTipText.IsEmpty()) // will be zero on a separator
    {
        lstrcpyn(pTTT->szText, strTipText, sizeof(pTTT->szText));

        *pResult = 0;

        return TRUE;
    }

    return FALSE;
}

CString CMiniSpyDlg::GetTip(UINT nID)
{
	if (!nID)
		return "";

	CString sPrompt, sTip;
	sPrompt.LoadString(nID);
	
	if (sPrompt.IsEmpty())
		return "";
	
	// tip text starts at '\n' 
	int nStartTip = sPrompt.Find('\n');
	
	if (nStartTip != -1) 
		sPrompt = sPrompt.Right(sPrompt.GetLength() - nStartTip - 1);
	
	// strip '&' and '...' if present
	int nLen = sPrompt.GetLength();
	
	for (int nPos = 0; nPos < nLen; nPos++)
		if (sPrompt[nPos] != '&' && sPrompt[nPos] != '.')
			sTip += sPrompt[nPos];
		
	return sTip;
}

CPoint CMiniSpyDlg::GetCurrentCorner()
{
	CRect rWindow;
	GetWindowRect(rWindow);

	CPoint ptCorner(0, 0);

	switch (m_nCorner)
	{
		case TOPLEFT:
			ptCorner = CPoint(rWindow.left, rWindow.top);
			ptCorner.Offset(-1, -1);
			break;

		case TOPRIGHT:
			ptCorner = CPoint(rWindow.right, rWindow.top);
			ptCorner.Offset(1, -1);
			break;

		case BOTTOMRIGHT:
			ptCorner = CPoint(rWindow.right, rWindow.bottom);
			ptCorner.Offset(1, 1);
			break;

		case BOTTOMLEFT:
			ptCorner = CPoint(rWindow.left, rWindow.bottom);
			ptCorner.Offset(-1, 1);
			break;

		default:
			ASSERT (0);
	}

	return ptCorner;
}

CString CMiniSpyDlg::GetWindowProperties(CWnd* pWnd)
{
	CStringArray aProperties;
	CString sProperties;

	EnumPropsEx(pWnd->GetSafeHwnd(), &PropEnumProcEx, (DWORD)&aProperties);

	int nProps = aProperties.GetSize();

	for (int nProp = 0; nProp < nProps; nProp++)
	{
		if (!sProperties.IsEmpty())
			sProperties += ", ";

		sProperties += aProperties[nProp];
	}

	return sProperties;
}

BOOL CALLBACK CMiniSpyDlg::PropEnumProcEx(HWND /*hwnd*/, LPTSTR lpszString, HANDLE hData, DWORD dwData)
{
	CStringArray* pProperties = (CStringArray*)dwData;

	TCHAR szAtomName[6+256] = _T("Atom: ");

	if (lpszString == (LPTSTR)(ATOM)lpszString)
	{
		GlobalGetAtomName((ATOM)lpszString, &szAtomName[6], 256);
		lpszString = szAtomName;
	}

	CString sProp;
	sProp.Format("%s:0x%08X (%d)", lpszString, hData, hData);
	pProperties->Add(sProp);

	return TRUE;
}

typedef HWND (WINAPI *REALCHILDWINDOWFROMPOINT)(HWND hwndParent, POINT ptParentClientCoords);

CWnd* CMiniSpyDlg::RealWindowFromPoint(CPoint ptHitTest)
{
	CWnd* pWnd = WindowFromPoint(ptHitTest);

	if (pWnd && (pWnd->GetStyle() & WS_CHILD))
	{
		// now check that another control is not being masked by say a group box
		CWnd* pParent = pWnd->GetParent();

		if (pParent)
		{
			// have to call
			HMODULE hUser32 = ::LoadLibrary("User32.dll");

			if (hUser32)
			{
				// note this function is not available under win95 so we also have a fallback
				REALCHILDWINDOWFROMPOINT fnRealWndFromPoint = (REALCHILDWINDOWFROMPOINT)GetProcAddress(hUser32, "RealChildWindowFromPoint");

				if (fnRealWndFromPoint)
				{
					// convert to parent client coords
					pParent->ScreenToClient(&ptHitTest);

					HWND hHit = fnRealWndFromPoint(*pParent, ptHitTest);

					if (hHit)
						pWnd = CWnd::FromHandle(hHit);
				}
				else
				{
					// iterate all the child controls of the parent until we hit one which
					// does not return HTTRANSPARENT or HTNOWHERE to WM_NCHITTEST
					CWnd* pChild = pParent->GetWindow(GW_CHILD);
					ASSERT (pChild);

					while (pChild)
					{
						UINT uHitTest = pChild->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptHitTest.x, ptHitTest.y));

						if ((int)uHitTest > 0)
						{
							pWnd = pChild;
							break;
						}

						pChild = pChild->GetNextWindow();
					}
				}
			}
		}
	}

	return pWnd;
}

CString CMiniSpyDlg::DoHitTest(CWnd* pWnd)
{
	CPoint ptHitTest = GetCurrentCorner();

	DWORD dwHitTest = pWnd->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptHitTest.x, ptHitTest.y));

	int nHitTest = sizeof(HitTests) / sizeof(Style);
	
	while (nHitTest--)
	{
		if (HitTests[nHitTest].dwStyle == dwHitTest)
			return HitTests[nHitTest].szStyle;
	}

	return "";
}

void CMiniSpyDlg::OnGotoChild() 
{
	CWnd* pWnd = m_curWnd.GetWnd();

	if (pWnd)
	{
		CWnd* pChild = pWnd->GetWindow(GW_CHILD);

		if (pChild)
		{
			LockUpdates(TRUE);
			SetCurrentWindow(pChild);
		}
	}
}

void CMiniSpyDlg::OnGotoNextWindow() 
{
	CWnd* pWnd = m_curWnd.GetWnd();

	if (pWnd)
	{
		CWnd* pNext = pWnd->GetNextWindow();

		if (pNext)
		{
			LockUpdates(TRUE);
			SetCurrentWindow(pNext);
		}
	}
}

void CMiniSpyDlg::OnGotoPreviousWindow() 
{
	CWnd* pWnd = m_curWnd.GetWnd();

	if (pWnd)
	{
		CWnd* pPrev = pWnd->GetNextWindow(GW_HWNDPREV);

		if (pPrev)
		{
			LockUpdates(TRUE);
			SetCurrentWindow(pPrev);
		}
	}
}

void CMiniSpyDlg::OnGotoParent() 
{
	CWnd* pWnd = m_curWnd.GetWnd();

	if (pWnd)
	{
		CWnd* pParent = pWnd->GetParent();

		if (pParent)
		{
			LockUpdates(TRUE);
			SetCurrentWindow(pParent);
		}
	}
}

void CMiniSpyDlg::OnLockUpdates() 
{
	LockUpdates(!m_bLockUpdates);
}

void CMiniSpyDlg::LockUpdates(BOOL bLock)
{
	m_bLockUpdates = bLock;

	m_toolbar.GetToolBarCtrl().CheckButton(ID_LOCKUPDATES, bLock);

	if (!bLock)
		UpdateCurrentWindow(TRUE);
}

