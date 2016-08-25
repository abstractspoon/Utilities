#if !defined(AFX_SELECTFILEDIALOG_H__970F8804_6C82_452F_AD9F_E28123A1D549__INCLUDED_)
#define AFX_SELECTFILEDIALOG_H__970F8804_6C82_452F_AD9F_E28123A1D549__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFileDialog.h : header file
//

#include "..\shared\runtimedlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectFileDlg dialog

class CSelectFileDlg : public CRuntimeDlg
{
// Construction
public:
	CSelectFileDlg(CStringArray& aFiles, CWnd* pParent = NULL);   // standard constructor

	int DoModal();
	CString GetPathName() { return m_sSelection; }

protected:
// Dialog Data
	//{{AFX_DATA(CSelectFileDlg)
	CListBox	m_lbFiles;
	CString	m_sSelection;
	//}}AFX_DATA
	CStringArray m_aFiles;
//	enum { IDD = IDD_SELECTFILE_DIALOG };


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectFileDlg)
	afx_msg void OnSelchangeFilelist();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkFilelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFILEDIALOG_H__970F8804_6C82_452F_AD9F_E28123A1D549__INCLUDED_)
