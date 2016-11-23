// FindIncludesDlg.h : header file
//

#if !defined(AFX_WINSYMLIBDLG_H__D90EE86E_9406_4539_B792_14E1723E33BD__INCLUDED_)
#define AFX_WINSYMLIBDLG_H__D90EE86E_9406_4539_B792_14E1723E33BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////

static UINT WM_ISWINSYMLIBDLG = RegisterWindowMessage(_T("WM_ISWINSYMLIBDLG"));
const UINT ISWINSYMLIBDLG_ANSWER = 1234567890;

/////////////////////////////////////////////////////////////////////////////

enum
{
	WSL_NEWSYMBOL = 0,
};

/////////////////////////////////////////////////////////////////////////////

const UINT _MAX_FUNC = 250;

struct FINDINCLUDESCOPYDATA
{
	TCHAR szFileName[_MAX_FNAME];
	TCHAR szFileExt[_MAX_EXT];
   TCHAR szFunction[_MAX_FUNC];
};

/////////////////////////////////////////////////////////////////////////////

struct INCLUDEFILEITEM
{
   INCLUDEFILEITEM(const CString& file = _T(""), const CString& id = _T(""), const CString& path = _T("")) 
      : sFile(file), sDoxyID(id), sFullPath(path)
   {
   }

   CString sFile;
   CString sDoxyID;
   CString sFullPath;
};


/////////////////////////////////////////////////////////////////////////////
// CFindIncludesDlg dialog

class CFindIncludesDlg : public CDialog
{
// Construction
public:
	CFindIncludesDlg(LPCTSTR szFileName = NULL, LPCTSTR szFileExt = NULL, LPCTSTR szFunction = NULL, CWnd* pParent = NULL);	// standard constructor
	virtual ~CFindIncludesDlg();

// Dialog Data
	//{{AFX_DATA(CFindIncludesDlg)
	enum { IDD = IDD_WINSYMLIB_DIALOG };
	CComboBox	m_cbXMLPaths;
   CComboBox	m_cbSymbols;
   CComboBox	m_cbSourcePaths;
   CComboBox	m_cbDevEnvPaths;
	CTreeCtrl	m_tcResults;
   CString     m_sFile;
	BOOL	      m_bAutoSearch;
   BOOL        m_bRecursive;
   CString     m_sFunction;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindIncludesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	virtual void OnOK(); //
	virtual void OnCancel() { /* do nothing */ }

   // Implementation
protected:
   HICON m_hIcon;
   CMap<CString, LPCTSTR, CStringArray*, CStringArray*&> m_mapDoxyID2Includes;
   CMap<CString, LPCTSTR, INCLUDEFILEITEM, INCLUDEFILEITEM&> m_mapFile2IncludeItem;

   CString m_sXmlFolder;
   CString m_sSrcPath;
   CString m_sDevEnv;
   CImageList m_ilResults;

	// Generated message map functions
	//{{AFX_MSG(CFindIncludesDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBrowseXMLFolder();
   afx_msg void OnSearch();
   afx_msg void OnClose();
   afx_msg void OnDestroy();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnIgnorelinenumbers();
   afx_msg void OnDblclkResults(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
   afx_msg void OnBnClickedBrowseSource();
   afx_msg void OnBnClickedBrowsedevenv();
   //}}AFX_MSG
   afx_msg LRESULT OnIsFindIncludesDlg(WPARAM wp, LPARAM lp) { return ISWINSYMLIBDLG_ANSWER; }
   afx_msg void OnCbnEditchangeRepopath();
   afx_msg void OnBnClickedRecursive();
   afx_msg void OnCbnSelChangeXmlFolder();
   afx_msg void OnCbnEditChangeXmlFolder();
   DECLARE_MESSAGE_MAP()

protected:
// 	int LoadSymbolLibrary();
	void EmptySymbolMap();
   void AddItemToCombo(LPCTSTR szItem, CComboBox& combo, BOOL bPath);
   void DoSearch();
   void DoSearch(INCLUDEFILEITEM& fi, HTREEITEM htiParent, CMap<CString, LPCTSTR, BOOL, BOOL&>& mapVisited);
   CString GetResultFilePath(HTREEITEM hti);
   int ShowResult(HTREEITEM hti);
   BOOL LoadDoxyIndex();
   CString GetDoxyID(const CString& sInclude, BOOL bWantHeader = FALSE) const;

  static CString& GetCheckPath(LPCTSTR szIniEntry, CString& sPath, LPCTSTR szDefault = NULL);

public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSYMLIBDLG_H__D90EE86E_9406_4539_B792_14E1723E33BD__INCLUDED_)
