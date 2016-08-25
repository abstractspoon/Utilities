// ScrollPrintDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CScrollPrintDlg dialog
class CScrollPrintDlg : public CDialog
{
// Construction
public:
	CScrollPrintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCROLLPRINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CEdit m_edit;
	CTreeCtrl m_tree;
	CListCtrl m_list;
	CImageList m_ilList;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSaveImage();

protected:
//	BOOL CScrollPrintDlg::CopyWindowContents(CWnd* pWnd, CBitmap& bmp);

public:
};
