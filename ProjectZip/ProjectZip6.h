// ProjectZip6.h: interface for the CProjectZip6 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTZIP6_H__C91A30DE_526E_47AC_9DFC_1453629B3DA2__INCLUDED_)
#define AFX_PROJECTZIP6_H__C91A30DE_526E_47AC_9DFC_1453629B3DA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "projectzipbase.h"

class CProjectZip6 : public CProjectZipBase  
{
public:
	CProjectZip6(LPCTSTR szProjectFilePath = NULL, HWND hwndParent = NULL);
	virtual ~CProjectZip6();

	// base class implementations
	virtual int GetProjectFiles(CString sWorkspaceFile, CStringArray& aFiles) const;
	virtual int GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const;
	virtual void RemoveVSSLinks(CStringArray& aFile, BOOL bWorkspace) const;

	// helpers
	BOOL GetNextFile(CStdioFile& fileProject, CString& sFilePath) const;
	BOOL GetNextProjectFile(CStdioFile& fileWorkspace, CString& sFilePath) const;
};

#endif // !defined(AFX_PROJECTZIP6_H__C91A30DE_526E_47AC_9DFC_1453629B3DA2__INCLUDED_)
