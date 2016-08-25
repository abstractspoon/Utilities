// GitHubToDokuWikiDlg.h : header file
//

#if !defined(AFX_GITHUBTODOKUWIKIDLG_H__3A605445_9CBA_44BA_9150_CC936C675C5E__INCLUDED_)
#define AFX_GITHUBTODOKUWIKIDLG_H__3A605445_9CBA_44BA_9150_CC936C675C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGitHubToDokuWikiDlg dialog

class CGitHubToDokuWikiDlg : public CDialog
{
// Construction
public:
	CGitHubToDokuWikiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGitHubToDokuWikiDlg)
	enum { IDD = IDD_GITHUBTODOKUWIKI_DIALOG };
	CString	m_sGitHubFolder;
	CString	m_sDokuwikiFolder;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGitHubToDokuWikiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGitHubToDokuWikiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnConvert();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


protected:
	CString GetDestFilePath(const CString& sSrcFile) const;
	void ProcessSrcFile(const CString& sSrcFile) const;
	void ProcessImageLinks(CString& sLine) const;
	void ProcessPageLinks(CString& sLine) const;
	void ProcessHeadings(CString& sLine) const;
	void ProcessHorzLines(CString& sLine) const;
	void ProcessLists(CString& sLine) const;
	void ProcessDivs(CString& sLine) const;
	void ProcessIcons(CString& sLine) const;
	void ProcessBreaks(CString& sLine) const;

	CString FormatLines(const CStringArray& aLines) const;
	CString FormatImage(const CString& sImage) const;
	CString GetEquivHeading(const CString& sGHHeading) const;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GITHUBTODOKUWIKIDLG_H__3A605445_9CBA_44BA_9150_CC936C675C5E__INCLUDED_)
