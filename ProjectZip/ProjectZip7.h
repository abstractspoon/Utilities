// ProjectZip7.h: interface for the CProjectZip7 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTZIP7_H__64187883_1169_44E0_8651_4620B5BFA638__INCLUDED_)
#define AFX_PROJECTZIP7_H__64187883_1169_44E0_8651_4620B5BFA638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectZipBase.h"

class CXmlItem;

class CProjectZip7 : public CProjectZipBase  
{
public:
	CProjectZip7(LPCTSTR szProjectFilePath = NULL, HWND hwndParent = NULL);
	virtual ~CProjectZip7();

	// base class implementations
	virtual int GetProjectFiles(CString sWorkspaceFile, CStringArray& aFiles) const;
	virtual int GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const;
	virtual void RemoveVSSLinks(CStringArray& aFile, BOOL bWorkspace) const {} // not supported

	// helpers
	BOOL GetNextProjectFile(CStdioFile& fileWorkspace, CString& sFilePath) const;
	void ProcessFileGroup(const CXmlItem* pXIGroup, CStringArray& aFiles, BOOL bVccProj) const;

};

#endif // !defined(AFX_PROJECTZIP7_H__64187883_1169_44E0_8651_4620B5BFA638__INCLUDED_)
