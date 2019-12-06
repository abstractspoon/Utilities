#if !defined(AFX_OPTIONSDLG_H__7F261724_A688_416E_8997_FB8CF33EA4C9__INCLUDED_)
#define AFX_OPTIONSDLG_H__7F261724_A688_416E_8997_FB8CF33EA4C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

#include "..\..\ToDoList_Dev\Core\shared\runtimedlg.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

enum // options
{
	PZOPT_SHOWSAVEAS			= 0x0001,
	PZOPT_INCLUDEWORKSPACE		= 0x0002,
	PZOPT_INCLUDEOTHERPROJFILES	= 0x0004,
	PZOPT_OPENZIP				= 0x0008,
	PZOPT_PROMPTIFMULTI			= 0x0010,
	PZOPT_PROMPTOVERWRITE		= 0x0020,
	PZOPT_MAKELOWER				= 0x0040,
	PZOPT_BREAKVSSLINK			= 0x0080,
	PZOPT_NOCOMPLETIONMSG		= 0x1000,
};

class COptionsDlg : public CRuntimeDlg
{
// Construction
public:
	COptionsDlg(LPCTSTR szFilePath = NULL, HICON hIcon = NULL, CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();

	int DoModal();
	DWORD GetOptions(); // returns bitflags

protected:
// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	BOOL	m_bShowSaveAs;
	BOOL	m_bIncludeDsw;
	BOOL	m_bOpenZip;
	int		m_nResolveMulti;
	BOOL	m_bPromptOverwrite;
	//}}AFX_DATA
	BOOL	m_bMakeLower;
	CString m_sFilePath;
	HICON m_hIcon;
	BOOL	m_bIncludeOtherProjFiles;
	BOOL	m_bBreakVSSLink;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__7F261724_A688_416E_8997_FB8CF33EA4C9__INCLUDED_)
