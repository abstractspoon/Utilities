// ProjectZip7.cpp: implementation of the CProjectZip7 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProjectZip7.h"

#include "..\..\ToDoList_Dev\Core\Shared\XmlFile.h"
#include "..\..\ToDoList_Dev\Core\Shared\misc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProjectZip7::CProjectZip7(LPCTSTR szProjectFilePath, HWND hwndParent)
	 : CProjectZipBase(szProjectFilePath, hwndParent)
{
	AddWorkspaceExtension(_T("sln"));
	AddProjectExtension(_T("csproj"));
	AddProjectExtension(_T("vcproj"));
	AddProjectExtension(_T("vcxproj"));
	AddOtherProjFileExtension(_T("suo"));
	AddOtherProjFileExtension(_T("ncb"));
}

CProjectZip7::~CProjectZip7()
{

}

int CProjectZip7::GetProjectFiles(CString sWorkspaceFile, CStringArray& aFiles) const
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

int CProjectZip7::GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const
{
	aFiles.RemoveAll();

	CXmlFile file(_T(""));
	
	if (file.Load(sProjectFile, _T("Project"))) // vcxproj
	{
		const CXmlItem* pXIGroup = file.GetItem(_T("ItemGroup"));

		while (pXIGroup)
		{
			ProcessFileGroup(pXIGroup, aFiles);

			pXIGroup = pXIGroup->GetSibling();
		}
	}
	else if (file.Load(sProjectFile, _T("VisualStudioProject"))) // vcproj
	{
		const CXmlItem* pXIGroup = file.Root()->GetItem(_T("Files"), _T("Filter"));

		while (pXIGroup)
		{
			ProcessFileGroup(pXIGroup, aFiles);
			
			pXIGroup = pXIGroup->GetSibling();
		}
	}
	
	return aFiles.GetSize();
}

BOOL CProjectZip7::GetNextProjectFile(CStdioFile& fileWorkspace, CString& sFilePath) const
{
	CString sLine;
	sFilePath.Empty();
	
	// read to start of next source
	while (fileWorkspace.ReadString(sLine) && sLine.Find(_T("Project(")) == -1);
	
	// split by commas
	CStringArray aParts;

	if (Misc::Split(sLine, aParts, ',') >= 2)
	{
		sFilePath = aParts[1]; // 2nd item
		
		// cleanup
		sFilePath.Replace('\"', ' ');
		sFilePath.TrimLeft();
		sFilePath.TrimRight();
		
		TRACE (_T("%s\n"), sFilePath);
	}
	
	return !sFilePath.IsEmpty();
}

void CProjectZip7::ProcessFileGroup(const CXmlItem* pXIGroup, CStringArray& aFiles) const
{
	if (pXIGroup->GetName() == _T("ItemGroup")) // vcxproj
	{
		// source files
		const CXmlItem* pXISrc = pXIGroup->GetItem(_T("ClCompile"));

		while (pXISrc)
		{
			CString sFilePath(pXISrc->GetItemValue(_T("Include")));

			// cleanup
			sFilePath.Replace('\"', ' ');
			sFilePath.TrimLeft();
			sFilePath.TrimRight();
			
			if (!sFilePath.IsEmpty())
				aFiles.Add(sFilePath);

			// next
			pXISrc = pXISrc->GetSibling();
		}

		// header files
		const CXmlItem* pXIInc = pXIGroup->GetItem(_T("ClInclude"));

		while (pXIInc)
		{
			CString sFilePath(pXIInc->GetItemValue(_T("Include")));

			// cleanup
			sFilePath.Replace('\"', ' ');
			sFilePath.TrimLeft();
			sFilePath.TrimRight();
			
			if (!sFilePath.IsEmpty())
				aFiles.Add(sFilePath);

			// next
			pXIInc = pXIInc->GetSibling();
		}
	}
	else if (pXIGroup->GetName() == _T("Filter")) // vcproj
	{
		const CXmlItem* pXIFile = pXIGroup->GetItem(_T("File"));

		while (pXIFile)
		{
			CString sFilePath(pXIFile->GetItemValue(_T("RelativePath")));

			// cleanup
			sFilePath.Replace('\"', ' ');
			sFilePath.TrimLeft();
			sFilePath.TrimRight();
			
			if (!sFilePath.IsEmpty())
				aFiles.Add(sFilePath);

			// next
			pXIFile = pXIFile->GetSibling();
		}
	}
}
