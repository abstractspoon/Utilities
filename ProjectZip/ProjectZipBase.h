// ProjectZipBase.h: interface for the CProjectZipBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTZIPBASE_H__07662E15_E6EC_4401_ADCD_6EC0B286521E__INCLUDED_)
#define AFX_PROJECTZIPBASE_H__07662E15_E6EC_4401_ADCD_6EC0B286521E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IProjectZip.h"

class CZipper;
class CUnzipper;

class CProjectZipBase : public IProjectZip  
{
public:
	CProjectZipBase(LPCTSTR szProjectFilePath = NULL, HWND hwndParent = NULL);
	virtual ~CProjectZipBase();

public: // required baseclass implementations
	void Zip(CString& sDestPath, DWORD dwFlags);
	int Open(LPTSTR szFilePath, LPTSTR szOutputPath = NULL, BOOL bErrorMsgs = TRUE);
	void ShowOptions(HICON hIcon, CString& sDestPath);
	void Release();

	BOOL IsWorkspace(LPCTSTR szFilePath) const;
	BOOL IsProject(LPCTSTR szFilePath) const;
	CString FormatOtherProjFileExtString();
	CString FormatProjectFileExtString();
	CString FormatWorkspaceFileExtString();

protected:
	CString m_sProjectPath;
	HWND m_hwndParent;
	CStringArray m_aProjExts, m_aWkspExts;
	CStringArray m_aOtherProjFileExts;
	DWORD m_dwOptions;

protected:
	int Zip(CString sFilePath, CString& sZipPath, CStringArray& aFailures);

	int BuildProjectFileList(CString sProjectFile, CStringArray& aFiles, CStringArray& aFailures);
	int BuildWorkspaceFileList(CString sWorkspaceFile, CStringArray& aFiles, CStringArray& aFailures);
	void PrepareFilePaths(CString sProjectFile, CStringArray& aFiles, CStringArray& aFailures);
	CString GetFileRoot(CString sProjectFile, const CStringArray& aFiles);
	int FindProjectFiles(CUnzipper& uzip, LPCTSTR szFolder, CStringArray& aDswFiles, CStringArray& aDspFiles);
	int FindProjectFiles(CUnzipper& uzip, LPCTSTR szFolder, CStringArray& aFiles, LPCTSTR szExt);
	inline CWnd* ParentWnd() { return CWnd::FromHandle(m_hwndParent); }
	inline BOOL HasOption(DWORD dwOption) const { return ((m_dwOptions & dwOption) == dwOption); }
	BOOL AddFileToZip(CZipper& zip, LPCTSTR szFile, LPCTSTR szRootPath) const;

	// derived classes must provide implementation
	virtual int GetProjectFiles(CString sWorkspaceFile, CStringArray& aFiles) const = 0;
	virtual int GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const = 0;
	virtual void RemoveVSSLinks(CStringArray& aFile, BOOL bWorkspace) const = 0;
	
	void AddOtherProjFileExtension(LPCTSTR szExt);
	void AddProjectExtension(LPCTSTR szExt);
	void AddWorkspaceExtension(LPCTSTR szExt);
	CString GetExtension(LPCTSTR szFilePath);
	CString BuildFilterString();

	static void AddFile(LPCTSTR szFilePath, CStringArray& aFiles); // checks for duplicates
	static void AddFiles(const CStringArray& aSrcFiles, CStringArray& aDestFiles); // checks for duplicates

};

#endif // !defined(AFX_PROJECTZIPBASE_H__07662E15_E6EC_4401_ADCD_6EC0B286521E__INCLUDED_)
