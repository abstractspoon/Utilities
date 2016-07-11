// MiniSpyDlg.h : header file
//

#if !defined(AFX_MINISPYDLG_H__46AFC4E3_CC43_4E69_B5D3_2B6D1F501D0E__INCLUDED_)
#define AFX_MINISPYDLG_H__46AFC4E3_CC43_4E69_B5D3_2B6D1F501D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMiniSpyDlg dialog

struct CurrentWnd
{
	HWND hWnd;
	CString sCaption;
	DWORD dwStyle;
	DWORD dwExStyle;
	CRect rWindow;
	CRect rClient;

	BOOL IsSameAs(CWnd* pWnd)
	{
		if (pWnd && !::IsWindow(*pWnd))
			pWnd = NULL;

		if (!pWnd && !hWnd)
			return TRUE;

		else if (!pWnd && hWnd)
			return FALSE;

		else if (pWnd && !hWnd)
			return FALSE;

		else if (pWnd->GetSafeHwnd() != hWnd)
			return FALSE;

		else if (pWnd->GetStyle() != dwStyle)
			return FALSE;

		else if (pWnd->GetExStyle() != dwExStyle)
			return FALSE;

		CString sWndCaption;
		pWnd->GetWindowText(sWndCaption);

		if (sWndCaption != sCaption)
			return FALSE;

		CRect rWndWindow, rWndClient;

		pWnd->GetWindowRect(rWndWindow);

		if (rWndWindow != rWindow)
			return FALSE;

		pWnd->GetClientRect(rWndClient);

		if (rWndClient != rClient)
			return FALSE;

		return TRUE;
	}

	void SetWnd(CWnd* pWnd)
	{
		hWnd = pWnd ? pWnd->GetSafeHwnd() : NULL;
		dwStyle = pWnd ? pWnd->GetStyle() : 0;
		dwExStyle = pWnd ? pWnd->GetExStyle() : 0;

		pWnd ? pWnd->GetWindowText(sCaption) : sCaption.Empty();
		pWnd ? pWnd->GetWindowRect(rWindow) : rWindow.SetRectEmpty();
		pWnd ? pWnd->GetClientRect(rClient) : rClient.SetRectEmpty();
	}

	CWnd* GetWnd()
	{
		return CWnd::FromHandle(hWnd);
	}
};

class CMiniSpyDlg : public CDialog
{
// Construction
public:
	CMiniSpyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMiniSpyDlg)
	enum { IDD = IDD_MINISPY_DIALOG };
	CComboBox	m_cbFilter;
	CListCtrl	m_lcAttributes;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiniSpyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CurrentWnd m_curWnd;
	CToolTipCtrl m_tooltip;
	CSize m_sizeOriginal;
	CToolBar m_toolbar;
	int m_nCorner;
	BOOL m_bLockUpdates;
	HACCEL m_hAccelerator;

	// Generated message map functions
	//{{AFX_MSG(CMiniSpyDlg)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeFilter();
	afx_msg void OnRefresh();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnRestoresize();
	afx_msg void OnChangeCorner(UINT nID);
	afx_msg void OnAppAbout();
	afx_msg void OnGotoChild();
	afx_msg void OnGotoNextWindow();
	afx_msg void OnGotoParent();
	afx_msg void OnLockUpdates();
	afx_msg void OnGotoPreviousWindow();
	//}}AFX_MSG
	BOOL OnNeedTooltip(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

protected:
	void UpdateCurrentWindow(BOOL bForce = FALSE);
	void SetCurrentWindow(CWnd* pWnd = NULL);
	void RefreshAttributes(CWnd* pWnd = NULL);
	CString GetClassStyles(CWnd* pWnd);
	CString GetWindowStyles(CWnd* pWnd);
	CString GetWindowProperties(CWnd* pWnd);
	CString GetWindowExStyles(CWnd* pWnd);
	CString GetControlStyles(CWnd* pWnd, LPCTSTR szClass = NULL);
	CString GetControlExStyles(CWnd* pWnd, LPCTSTR szClass = NULL);
	CString GetBaseClass(LPCTSTR szClass);
	DWORD GetExStyleMsg(LPCTSTR szClass);
	CString GetWindowText(CWnd* pWnd);
	CString GetTip(UINT nID);
	CPoint GetCurrentCorner();
	CString DoHitTest(CWnd* pWnd);
	void RefreshHitTest(CWnd* pWnd);
	void LockUpdates(BOOL bLock = TRUE);

	static CString GetClassName(CWnd* pWnd, BOOL bDecorative = TRUE);
	static BOOL CALLBACK PropEnumProcEx(HWND hwnd, LPTSTR lpszString, HANDLE hData, DWORD dwData);
	static CWnd* RealWindowFromPoint(CPoint ptHitTest);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINISPYDLG_H__46AFC4E3_CC43_4E69_B5D3_2B6D1F501D0E__INCLUDED_)
