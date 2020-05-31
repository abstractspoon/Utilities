// ProjectZip7.cpp: implementation of the CProjectZip7 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProjectZip7.h"

#include "..\..\ToDoList_Dev\Core\Shared\XmlFile.h"
#include "..\..\ToDoList_Dev\Core\Shared\misc.h"
#include "..\..\ToDoList_Dev\Core\Shared\filemisc.h"

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
		{
			if (IsProject(sFile))
				AddFile(sFile, aFiles);
		}
	}
	
	return aFiles.GetSize();
}

int CProjectZip7::GetSourceFiles(CString sProjectFile, CStringArray& aFiles) const
{
	aFiles.RemoveAll();

	CXmlFile file(_T(""));
	
	if (file.Load(sProjectFile, _T("Project"))) // vcxproj/csproj
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
		VERIFY(ValidatePath(sFilePath));

		TRACE (_T("%s\n"), sFilePath);
	}
	
	return !sFilePath.IsEmpty();
}

void CProjectZip7::ProcessFileGroup(const CXmlItem* pXIGroup, CStringArray& aFiles) const
{
	if (pXIGroup->GetName() == _T("ItemGroup")) // vcxproj/csproj
	{
		LPCTSTR FILETYPES[] = 
		{
			_T("ClCompile"),		// vcxproj
			_T("ClInclude"),		// vcxproj
			_T("ResourceCompile"),	// vcxproj
			_T("Image"),			// vcxproj
			_T("Compile"),			// csproj
			_T("EmbeddedResource"),	// csproj
			_T("Content"),			// csproj
			_T("None"),				// vcxproj/csproj
		};
		const int NUM_FILETYPES = (sizeof(FILETYPES) / sizeof(FILETYPES[0]));

		// source files
		int nFileType = NUM_FILETYPES;

		while (nFileType--)
		{
			const CXmlItem* pXISrc = pXIGroup->GetItem(FILETYPES[nFileType]);

			while (pXISrc)
			{
				CString sFilePath(pXISrc->GetItemValue(_T("Include")));

				// cleanup
				if (ValidatePath(sFilePath))
					aFiles.Add(sFilePath);

				// next
				pXISrc = pXISrc->GetSibling();
			}
		}
	}
	else if (pXIGroup->GetName() == _T("Filter")) // vcproj
	{
		const CXmlItem* pXIFile = pXIGroup->GetItem(_T("File"));

		while (pXIFile)
		{
			CString sFilePath(pXIFile->GetItemValue(_T("RelativePath")));

			// cleanup
			if (ValidatePath(sFilePath))
				aFiles.Add(sFilePath);

			// next
			pXIFile = pXIFile->GetSibling();
		}
	}
}

BOOL CProjectZip7::ValidatePath(CString& sFilePath)
{
	sFilePath.Replace('\"', ' ');
	sFilePath.TrimLeft();
	sFilePath.TrimRight();

	return !sFilePath.IsEmpty();
}
