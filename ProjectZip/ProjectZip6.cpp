// ProjectZip6.cpp: implementation of the CProjectZip6 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProjectZip6.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

enum { PZIP_OK, PZIP_CREATEFILE, PZIP_CANCELLED };

CProjectZip6::CProjectZip6(LPCTSTR szProjectFilePath, HWND hwndParent)
	 : CProjectZipBase(szProjectFilePath, hwndParent)
{
	AddWorkspaceExtension(_T("dsw"));
	AddProjectExtension(_T("dsp"));
	AddOtherProjFileExtension(_T("clw"));
	AddOtherProjFileExtension(_T("ncb"));
	AddOtherProjFileExtension(_T("opt"));
}

CProjectZip6::~CProjectZip6()
{

}

int CProjectZip6::GetProjectFiles(CString sWorkspaceFile, CStringArray& aFiles) const
{
	aFiles.RemoveAll();
	CStdioFile file;

	if (file.Open(sWorkspaceFile, CFile::modeRead | CFile::typeText))
	{
		// find the first source file
		CString sFile;
		
		while (GetNextProjectFile(file, sFile))
			AddFile(sFile, aFiles);
	}

	return aFiles.GetSize();
}

int CProjectZip6::GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const
{
	aFiles.RemoveAll();
	CStdioFile file;

	if (file.Open(sProjectFile, CFile::modeRead | CFile::typeText))
	{
		// find the first source file
		CString sFile;
		
		while (GetNextFile(file, sFile))
			AddFile(sFile, aFiles);
	}
	
	return aFiles.GetSize();
}

BOOL CProjectZip6::GetNextFile(CStdioFile& fileProject, CString& sFilePath) const
{
	CString sLine;
	sFilePath.Empty();

	// read to start of next source
	while (fileProject.ReadString(sLine) && sLine.Find(_T("# Begin Source File")) == -1);

	// then read to actual file
	while (fileProject.ReadString(sLine) && sLine.Find(_T("SOURCE=")) == -1);

	// extract path to right of 'SOURCE='
	int nFind = sLine.Find(_T("SOURCE="));

	if (nFind != -1)
	{
		sFilePath = sLine.Mid(nFind + lstrlen(_T("SOURCE=")));

		// cleanup
		sFilePath.Replace('\"', ' ');
		sFilePath.TrimLeft();
		sFilePath.TrimRight();

		TRACE (_T("%s\n"), sFilePath);
	}

	return !sFilePath.IsEmpty();
}

BOOL CProjectZip6::GetNextProjectFile(CStdioFile& fileWorkspace, CString& sFilePath) const
{
	CString sLine;
	sFilePath.Empty();

	// read to start of next source
	while (fileWorkspace.ReadString(sLine) && sLine.Find(_T("Project:")) == -1);

	// extract path to right of '"='
	int nFind = sLine.Find(_T("\"="));

	if (nFind != -1)
	{
		sFilePath = sLine.Mid(nFind + lstrlen(_T("\"=")));

		nFind = sFilePath.Find(_T("- Package Owner"));

		if (nFind != -1)
			sFilePath = sFilePath.Left(nFind - 1);

		// cleanup
		sFilePath.Replace('\"', ' ');
		sFilePath.TrimLeft();
		sFilePath.TrimRight();

		TRACE (_T("%s\n"), sFilePath);
	}

	return !sFilePath.IsEmpty();
}

void CProjectZip6::RemoveVSSLinks(CStringArray& aFile, BOOL bWorkspace) const
{
	int nLine = aFile.GetSize();

	while (nLine--)
	{
		CString sLine = aFile[nLine];
		
		if (bWorkspace)
		{
			if (sLine.Find(_T("end source code control")) >= 0)
			{
				do
				{
					sLine = aFile[nLine];
					aFile.RemoveAt(nLine);

					if (sLine.Find(_T("begin source code control")) >= 0)
						break;
				}
				while (nLine--);
			}
		}
		else // proejct file
		{
			if (sLine.Find(_T("# PROP Scc_")) >= 0)
				aFile.RemoveAt(nLine);
		}
	}
}
