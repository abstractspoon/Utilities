// ODBCExplorerDlg.h : header file
//

#if !defined(AFX_ODBCEXPLORERDLG_H__2C24BE12_7108_4E98_AA45_F3E3EBBEE15D__INCLUDED_)
#define AFX_ODBCEXPLORERDLG_H__2C24BE12_7108_4E98_AA45_F3E3EBBEE15D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Shared\odbcfieldcombobox.h"
#include "..\Shared\odbctablecombobox.h"

#include <afxdb.h>

/////////////////////////////////////////////////////////////////////////////
// CODBCExplorerDlg dialog

class CODBCExplorerDlg : public CDialog
{
// Construction
public:
	CODBCExplorerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CODBCExplorerDlg)
	enum { IDD = IDD_ODBCEXPLORER_DIALOG };
	COdbcTableComboBox	m_cbTables;
	COdbcFieldComboBox	m_cbFields;
	CListBox	m_lbFields;
	CListCtrl	m_lcColumns;
	CListCtrl	m_lcResults;
	CListBox	m_lbTables;
	CString	m_sDatabase;
	CString	m_sQuery;
	CString	m_sCurTable;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBCExplorerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CDatabase m_db;
	BOOL m_bDefault;

	// Generated message map functions
	//{{AFX_MSG(CODBCExplorerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChooseDatabase();
	afx_msg void OnExecute();
	afx_msg void OnExecuteQuery();
	afx_msg void OnDefaultDatabase();
	afx_msg void OnSelchangeTableList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL DoOpenDatabase(BOOL bDefault);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBCEXPLORERDLG_H__2C24BE12_7108_4E98_AA45_F3E3EBBEE15D__INCLUDED_)
