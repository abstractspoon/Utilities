// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DA60D259_97DD_4032_B081_B59D7C21E47F__INCLUDED_)
#define AFX_MAINFRM_H__DA60D259_97DD_4032_B081_B59D7C21E47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\ToDoList_8.1\Core\Shared\InterSpy.h"
#include <afxtempl.h>

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar m_wndToolBar;
	CTreeCtrl m_tree;
	CMap<HWND, HWND, HTREEITEM, HTREEITEM&> m_mapHwnds;
	CMap<DWORD, DWORD, HTREEITEM, HTREEITEM&> m_mapMsgs;
	CMap<UINT, UINT, BOOL, BOOL&> m_mapMsgExclusions;
	CMap<HWND, HWND, BOOL, BOOL&> m_mapHwndExclusions;
	BOOL m_bPaused;
	DWORD m_dwCount;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnGo();
	afx_msg void OnPause();
	afx_msg void OnClear();
	afx_msg void OnUpdateGo(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnNextMessage();
	afx_msg void OnPrevMessage();
	afx_msg void OnUpdateNextMessage(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrevMessage(CCmdUI* pCmdUI);
	afx_msg void OnClearDisabled();
	afx_msg void OnUpdateClearDisabled(CCmdUI* pCmdUI);
	afx_msg void OnItemEnable();
	afx_msg void OnUpdateItemEnable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnCustomDrawTree(NMHDR* pNotifyStruct, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

protected:
	void AddMsg(IS_COPYDATA* pData);
	BOOL SaveMessagesXml(LPCTSTR szFilePath);
	BOOL SaveMessagesText(LPCTSTR szFilePath);
	CString GetItemText(HTREEITEM hti);

	inline UINT ItemPos(HTREEITEM hti) { return (UINT)LOWORD(m_tree.GetItemData(hti)); }
	inline UINT ItemMsg(HTREEITEM hti) { return (UINT)HIWORD(m_tree.GetItemData(hti)); }

	BOOL IsItemMsg(HTREEITEM hti);
	BOOL IsItemHwnd(HTREEITEM hti);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DA60D259_97DD_4032_B081_B59D7C21E47F__INCLUDED_)
