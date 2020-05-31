// ProjectZipBase.cpp: implementation of the CProjectZipBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProjectZipBase.h"

#include "optionsdlg.h"
#include "selectfiledlg.h"

#include "..\..\ToDoList_Dev\Core\shared\folderdialog.h"
#include "..\..\ToDoList_Dev\Core\shared\zipper.h"
#include "..\..\ToDoList_Dev\Core\shared\unzipper.h"
#include "..\..\ToDoList_Dev\Core\shared\misc.h"

#include <shlwapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma comment(lib, "shlwapi.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

enum { PZIP_OK, PZIP_CREATEFILE, PZIP_CANCELLED };

CProjectZipBase::CProjectZipBase(LPCTSTR szProjectFilePath, HWND hwndParent)
	 : m_sProjectPath(szProjectFilePath), m_hwndParent(hwndParent)
{
	m_sProjectPath.TrimLeft();
	m_sProjectPath.TrimRight();

	if (GetFileAttributes(m_sProjectPath) == 0xffffffff)
		m_sProjectPath.Empty();
}

CProjectZipBase::~CProjectZipBase()
{

}

BOOL CProjectZipBase::Open(LPTSTR szFilePath, LPTSTR szOutputPath, BOOL bErrorMsgs)
{
	ASSERT (szFilePath);

	if (!szFilePath)
		return -1;

	CString sZipFilePath(szFilePath);
	CString sOutputPath(szOutputPath);
	TCHAR szFileTitle[_MAX_FNAME];

	if (sZipFilePath.IsEmpty())
	{
		CFileDialog dialog(TRUE, _T("zip"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, 
							_T("Zip Files (*.zip)|*.zip||"), ParentWnd());

		dialog.m_ofn.lpstrTitle = _T("ProjectZip © AbstractSpoon 2003 - Open Zip File");

		if (dialog.DoModal() == IDOK)
			sZipFilePath = dialog.GetPathName();
	}

	if (sZipFilePath.IsEmpty())
		return -1; // user must have cancelled

	if (sOutputPath.IsEmpty())
	{
		// ask user where to extract to
		CFolderDialog dialog(_T("Select Folder to Extract To"), NULL, ParentWnd());

		if (dialog.DoModal() == IDOK)
		{
			// append the zip's filetitle
			_tsplitpath(sZipFilePath, NULL, NULL, szFileTitle, NULL);

			sOutputPath.Format(_T("%s\\%s"), dialog.GetFolderPath(), szFileTitle);

			// check before overwriting
			if (HasOption(PZOPT_PROMPTOVERWRITE) && (GetFileAttributes(sOutputPath) != 0xffffffff))
			{
				CString sMessage;
				sMessage.Format(_T("The folder '%s' already exists.\n\nAre you sure that you want to overwrite it and the files it contains?"), 
								sOutputPath);
				
				if (IDNO == MessageBox(m_hwndParent, sMessage, _T("ProjectZip © AbstractSpoon 2003"), MB_YESNO))
					return -1;
			}
		}
	}

	if (sOutputPath.IsEmpty())
		return -1; // user must have cancelled

	// update output paths
	if (szOutputPath)
		lstrcpy(szOutputPath, sOutputPath);

	lstrcpy(szFilePath, sZipFilePath); // this tells the caller what the chosen zip file was if the unzipping fails

	CUnzipper uzip;

	if (uzip.OpenZip(sZipFilePath) && uzip.UnzipTo(sOutputPath))
	{
		CStringArray aWorkspaceFiles, aProjectFiles;

		int nFound = FindProjectFiles(uzip, sOutputPath, aWorkspaceFiles, aProjectFiles);
		CString sProjectFile;

		if (!nFound)
		{
			if (!bErrorMsgs)
				return 0;
			
			CString sMessage;
			sMessage.Format(_T("The file '%s' does not appear to contain a project file.\n\nWould you like to browse the extracted files?"), sZipFilePath);
			
			if (IDNO == MessageBox(m_hwndParent, sMessage, _T("ProjectZip © AbstractSpoon 2003"), MB_YESNO))
				return 0;
			
			// show open dialog
			CFileDialog dialog(TRUE, NULL, sOutputPath + _T("\\."), 0, BuildFilterString(), ParentWnd());
			
			dialog.m_ofn.lpstrTitle = _T("ProjectZip - Open Project File");
			
			if (dialog.DoModal() == IDOK)
				sProjectFile = dialog.GetPathName();
			else
				return -1;
			
		}
		else // open it
		{
			int nNumWorkspace = aWorkspaceFiles.GetSize();
			int nNumProject = aProjectFiles.GetSize();
			
			// try workspace files first
			if (nNumWorkspace)
			{
				if (nNumWorkspace == 1)
					sProjectFile = aWorkspaceFiles[0];
				
				else if (HasOption(PZOPT_PROMPTIFMULTI))
				{
					CSelectFileDlg dialog(aWorkspaceFiles, ParentWnd());
					
					if (dialog.DoModal() == IDOK)
						sProjectFile = dialog.GetPathName();
					else
						return -1;
				}
				else // make a guess
				{
					// see if there's a Workspace sharing the same name as the zip file
					sProjectFile = aWorkspaceFiles[0]; // default if we can't find a match
					
					for (int nFile = 0; nFile < aWorkspaceFiles.GetSize(); nFile++)
					{
						TCHAR szWorkspaceName[_MAX_FNAME];
						_tsplitpath(aWorkspaceFiles[nFile], NULL, NULL, szWorkspaceName, NULL);
						
						if (_tcsicmp(szFileTitle, szWorkspaceName) == 0)
						{
							sProjectFile = aWorkspaceFiles[nFile];
							break;
						}
					}
				}
			}
			else // nNumProject
			{
				if (nNumProject == 1)
					sProjectFile = aProjectFiles[0];
				
				else if (HasOption(PZOPT_PROMPTIFMULTI))
				{
					CSelectFileDlg dialog(aProjectFiles, ParentWnd());
					
					if (dialog.DoModal() == IDOK)
						sProjectFile = dialog.GetPathName();
					else
						return -1;
				}
				else // make a guess
				{
					// see if there's a Project sharing the same name as the zip file
					sProjectFile = aProjectFiles[0]; // default if we can't find a match
					
					for (int nFile = 0; nFile < aProjectFiles.GetSize(); nFile++)
					{
						TCHAR szWorkspaceName[_MAX_FNAME];
						_tsplitpath(aProjectFiles[nFile], NULL, NULL, szWorkspaceName, NULL);
						
						if (_tcsicmp(szFileTitle, szWorkspaceName) == 0)
						{
							sProjectFile = aProjectFiles[nFile];
							break;
						}
					}
				}
			}
		}
		
		if (!sProjectFile.IsEmpty())
		{
			// copy the file path
			lstrcpy(szFilePath, sProjectFile);
			return 1;
		}
	}
	
	return 0;
}

CString CProjectZipBase::BuildFilterString()
{
	CString sUIFilter, sFilter;

	// workspace
	int nExt = m_aWkspExts.GetSize();

	while (nExt--)
	{
		CString sExt = _T("*") + m_aWkspExts[nExt];

		if (!sUIFilter.IsEmpty())
			sUIFilter += _T(", ");

		sUIFilter += sExt;

		if (!sFilter.IsEmpty())
			sFilter += _T(";");

		sFilter += sExt;
	}

	// project
	nExt = m_aProjExts.GetSize();

	while (nExt--)
	{
		CString sExt = _T("*") + m_aProjExts[nExt];

		if (!sUIFilter.IsEmpty())
			sUIFilter += _T(", ");

		sUIFilter += sExt;

		if (!sFilter.IsEmpty())
			sFilter += _T(";");

		sFilter += sExt;
	}

	CString sFullFilter;
	sFullFilter.Format(_T("Project Files (%s)|%s||"), sUIFilter, sFilter);

	return sFullFilter;
}

void CProjectZipBase::ShowOptions(HICON hIcon, CString& sDestPath)
{
	COptionsDlg dialog(m_sProjectPath, hIcon, ParentWnd());

	if (dialog.DoModal() == IDOK && !m_sProjectPath.IsEmpty())
		Zip(sDestPath, dialog.GetOptions());
}

void CProjectZipBase::Release()
{
	delete this;
}

int CProjectZipBase::Zip(CString sFilePath, CString& sZipPath, CStringArray& aFailures)
{
	// get file list
	CStringArray aFiles;

	if (IsWorkspace(sFilePath))
		BuildWorkspaceFileList(sFilePath, aFiles, aFailures);
	else
		BuildProjectFileList(sFilePath, aFiles, aFailures);

	// get zip path
	TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];

	if (sZipPath.IsEmpty())
	{
		_tsplitpath(sFilePath, szDrive, szFolder, szName, NULL);
		_tmakepath(sZipPath.GetBuffer(MAX_PATH), szDrive, szFolder, szName, _T("zip"));
		sZipPath.ReleaseBuffer();
	}

	if (HasOption(PZOPT_SHOWSAVEAS))
	{
		CFileDialog dialog(FALSE, _T("zip"), sZipPath, 0, _T("Zip Files (*.zip)|*.zip||"), ParentWnd());

		dialog.m_ofn.lpstrTitle = _T("ProjectZip © AbstractSpoon 2003 - Save Zip File");

		if (dialog.DoModal() != IDOK)
			return PZIP_CANCELLED;

		sZipPath = dialog.GetPathName();
	}

	// check before overwriting
	if (HasOption(PZOPT_PROMPTOVERWRITE) && (GetFileAttributes(sZipPath) != 0xffffffff))
	{
		CString sMessage;
		sMessage.Format(_T("The file '%s' already exists.\n\nAre you sure that you want to overwrite it?"), sZipPath);

		if (IDNO == MessageBox(m_hwndParent, sMessage, _T("ProjectZip © AbstractSpoon 2003"), MB_YESNO))
			return PZIP_CANCELLED;

		// else delete the file first
		DeleteFile(sZipPath);
	}
	
	CZipper zip;
	CWaitCursor cursor;

	// get file root
	CString sRootPath = GetFileRoot(sFilePath, aFiles);

	if (!zip.OpenZip(sZipPath, sRootPath))
		return PZIP_CREATEFILE;

	// else add the files
	int nFile = aFiles.GetSize();

	while (nFile--)
	{
		CString sFile = aFiles[nFile];

		if (!AddFileToZip(zip, sFile, sRootPath))
			aFailures.Add(sFile);
	}

	zip.CloseZip();

	// renaming the file is the mose reliable way 
	// make it lower case
	if (HasOption(PZOPT_MAKELOWER))
	{
		sZipPath.MakeLower();
		CFile::Rename(sZipPath, sZipPath);
	}

	return PZIP_OK;
}

BOOL CProjectZipBase::AddFileToZip(CZipper& zip, LPCTSTR szFilePath, LPCTSTR szRootPath) const
{
	if (HasOption(PZOPT_BREAKVSSLINK) && (IsWorkspace(szFilePath) || IsProject(szFilePath)))
	{
		CStdioFile file;
		CStringArray aFileLines;

		if (file.Open(szFilePath, CFile::modeRead))
		{
			// read the file as an array of lines
			CString sLine;

			while (file.ReadString(sLine))
				aFileLines.Add(sLine);

			file.Close();
		}

		RemoveVSSLinks(aFileLines, IsWorkspace(szFilePath));

		if (aFileLines.GetSize())
		{
			CString sFileContents;

			// convert file to byte array
			for (int nLine = 0; nLine < aFileLines.GetSize(); nLine++)
			{
				sFileContents += aFileLines[nLine];
				sFileContents += _T("\r\n");
			}

			// convert to ansi before saving
			int nLen = sFileContents.GetLength();
#ifdef _UNICODE
			Misc::EncodeAsMultiByte(sFileContents);
#endif
			// build relative path
			LPCTSTR szRelPath = (szFilePath + lstrlen(szRootPath));

			return zip.AddFileToZip((unsigned char*)(LPCTSTR)sFileContents, nLen, szRelPath);
		}
		else
			return zip.AddFileToZip(szFilePath);
	}
	else
		return zip.AddFileToZip(szFilePath);
}

int CProjectZipBase::BuildWorkspaceFileList(CString sWorkspaceFile, CStringArray& aFiles, CStringArray& aFailures)
{
	ASSERT (IsWorkspace(sWorkspaceFile));

	if (!IsWorkspace(sWorkspaceFile))
		return 0;

	CWaitCursor cursor; // lengthy operation

	aFiles.RemoveAll();

	// add the workspace before we forget!
	AddFile(sWorkspaceFile, aFiles);

	// parse the Workspace manually building a list of project files
	CStringArray aProjects;

	if (GetProjectFiles(sWorkspaceFile, aProjects))
	{
		// convert to full paths
		PrepareFilePaths(sWorkspaceFile, aProjects, aFailures);

		// now build a master file list of all files
		int nNumProj = aProjects.GetSize();

		for (int nProject = 0; nProject < nNumProj; nProject++)
		{
			CString sProject(aProjects[nProject]);

			if (IsProject(sProject))
			{
				CStringArray aProjFiles;

				BuildProjectFileList(sProject, aProjFiles, aFailures);
				AddFiles(aProjFiles, aFiles);
			}
			else
				AddFile(sProject, aFiles);
		}
	}

	return aFiles.GetSize();
}

int CProjectZipBase::BuildProjectFileList(CString sProjectFile, CStringArray& aFiles, CStringArray& aFailures)
{
	ASSERT (IsProject(sProjectFile));

	if (!IsProject(sProjectFile))
		return 0;

	CWaitCursor cursor; // lengthy operation

	aFiles.RemoveAll();

	// we must use a temp file list to ensure that files having the same name
	// as files in other projects are not omitted by mistake before the
	// full relative path has been established
	CStringArray aTempFileList;

	// and the Workspace if requested
	if (HasOption(PZOPT_INCLUDEWORKSPACE))
	{
		TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
		_tsplitpath(sProjectFile, szDrive, szFolder, szName, NULL);

		int nExt = m_aWkspExts.GetSize();
		
		while (nExt--)
		{
			TCHAR szWorkspace[MAX_PATH];
			_tmakepath(szWorkspace, szDrive, szFolder, szName, m_aWkspExts[nExt]);

			DWORD dwAttrib = GetFileAttributes(szWorkspace);

			if (dwAttrib != 0xffffffff && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
				AddFile(szWorkspace, aTempFileList);
		}
	}

	// and/or other project files if requested
	if (HasOption(PZOPT_INCLUDEOTHERPROJFILES))
	{
		TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
		_tsplitpath(sProjectFile, szDrive, szFolder, szName, NULL);

		int nExt = m_aOtherProjFileExts.GetSize();
		
		while (nExt--)
		{
			TCHAR szProjFile[MAX_PATH];
			_tmakepath(szProjFile, szDrive, szFolder, szName, m_aOtherProjFileExts[nExt]);

			DWORD dwAttrib = GetFileAttributes(szProjFile);

			if (dwAttrib != 0xffffffff && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
				AddFile(szProjFile, aTempFileList);
		}
	}

	GetSourceFiles(sProjectFile, aTempFileList);
	AddFile(sProjectFile, aTempFileList);
	PrepareFilePaths(sProjectFile, aTempFileList, aFailures);

	aFiles.Append(aTempFileList);

	return aTempFileList.GetSize();
}

void CProjectZipBase::AddFile(LPCTSTR szFilePath, CStringArray& aFiles) // checks for duplicates
{
	// check for duplicates
	int nFile = aFiles.GetSize();

	while (nFile--)
	{
		if (aFiles[nFile].CompareNoCase(szFilePath) == 0)
			return;
	}

	aFiles.Add(szFilePath);
}

void CProjectZipBase::AddFiles(const CStringArray& aSrcFiles, CStringArray& aDestFiles)
{
	int nFile = aSrcFiles.GetSize();

	while (nFile--)
		AddFile(aSrcFiles[nFile], aDestFiles);
}

void CProjectZipBase::PrepareFilePaths(CString sProjectFile, CStringArray& aFiles, CStringArray& aFailures)
{
	TCHAR szDrive[_MAX_DRIVE], szFolder[MAX_PATH];
	_tsplitpath(sProjectFile, szDrive, szFolder, NULL, NULL);

	CString sProjFolder(szDrive);
	sProjFolder += szFolder;

	int nFile = aFiles.GetSize();
	aFailures.RemoveAll();

	while (nFile--)
	{
		CString sFile = aFiles[nFile];

		// for leading '\' just add the drive spec
		if (sFile.Find('\\') == 0)
		{
			sFile = szDrive + sFile;
			aFiles.SetAt(nFile, sFile);
		}
		// for '.\' just remove and prepend the project path
		else if (sFile.Find(_T(".\\")) == 0)
		{
			sFile = sProjFolder + sFile.Mid(2);
			aFiles.SetAt(nFile, sFile);
		}
		// for all instances of '..' remove the deepest subfolder from the project path
		// before prepending
		else if (sFile.Find(_T("..\\")) == 0)
		{
			BOOL bDone = FALSE;
			CString sProjTemp(sProjFolder);

			while (!bDone)
			{
				int nDotFind = sFile.Find(_T(".."));

				if (nDotFind == -1)
					bDone = TRUE;
				else
				{
					int nFind = sProjTemp.ReverseFind('\\');

					if (nFind == -1)
						bDone = TRUE;
					else
					{
						CString sSubFolder = sProjTemp.Mid(nFind + 1);
						sProjTemp = sProjTemp.Left(nFind);

						if (sSubFolder.IsEmpty()) // it was a trailing '\\'
							continue;

						// else remove the '..'
						sFile = sFile.Mid(nDotFind + 2);
					}
				}
			}

			sFile = sProjTemp + sFile;

			// if there are any '..' left, it failed
			if (sFile.Find(_T("..")) != -1)
			{
				aFailures.Add(aFiles[nFile]);
				aFiles.RemoveAt(nFile);
			}
			else
				aFiles.SetAt(nFile, sFile);
		}
		// else if its not a full path prepend the project root
		else if (sFile.Find(':') == -1)
		{
			sFile = sProjFolder + sFile;
			aFiles.SetAt(nFile, sFile);
		}
	}
}

CString CProjectZipBase::GetFileRoot(CString sProjectFile, const CStringArray& aFiles)
{
	// iteratively build a path which represents the largest path common to all files
	// ignore files on different drives to the Project
	TCHAR szDrive[_MAX_DRIVE];
	_tsplitpath(sProjectFile, szDrive, NULL, NULL, NULL);
	_tcslwr(szDrive);

	int nFind = sProjectFile.Find('\\');
	BOOL bMismatch = FALSE;
	CString sCommonFolder, sNextTry;

	while (nFind != -1 && !bMismatch)
	{
		sNextTry = sProjectFile.Left(nFind + 1); // includes '\\'
		sNextTry.MakeLower();
	
		// test every file for a match
		int nFile = aFiles.GetSize();

		while (nFile-- && !bMismatch)
		{
			CString sFile = aFiles[nFile];
			sFile.MakeLower();

			// ignore files on different drives to the Project
			if (sFile.Find(szDrive) != 0)
				continue;

			bMismatch = (sFile.Find(sNextTry) == -1);
		}

		if (!bMismatch)
		{
			sCommonFolder = sNextTry; // fits all
			nFind = sProjectFile.Find('\\', nFind + 1);
		}
	}

	return sCommonFolder;
}

int CProjectZipBase::FindProjectFiles(CUnzipper& uzip, LPCTSTR szFolder, CStringArray& aWorkspaceFiles, CStringArray& aProjectFiles)
{
	aWorkspaceFiles.RemoveAll();
	aProjectFiles.RemoveAll();

	int nExt = m_aWkspExts.GetSize();

	while (nExt--)
		FindProjectFiles(uzip, szFolder, aWorkspaceFiles, m_aWkspExts[nExt]);
	
	nExt = m_aProjExts.GetSize();

	FindProjectFiles(uzip, szFolder, aProjectFiles, m_aProjExts[nExt]);

	return (aWorkspaceFiles.GetSize() + aProjectFiles.GetSize());
}

int CProjectZipBase::FindProjectFiles(CUnzipper& uzip, LPCTSTR szFolder, CStringArray& aFiles, LPCTSTR szExt)
{
	if (!szExt || !lstrlen(szExt))
		return 0;

	if (uzip.GotoFirstFile(szExt))
	{
		do
		{
			UZ_FileInfo fi;

			if (uzip.GetFileInfo(fi) && !fi.bFolder)
			{
				TCHAR szFullPath[MAX_PATH];
				_tmakepath(szFullPath, NULL, szFolder, fi.szFileName, NULL);

				aFiles.Add(szFullPath);
			}
		}
		while (uzip.GotoNextFile(szExt));
	}

	return aFiles.GetSize();
}

BOOL CProjectZipBase::IsWorkspace(LPCTSTR szFilePath) const
{
	TCHAR szExt[_MAX_EXT];
	_tsplitpath(szFilePath, NULL, NULL, NULL, szExt);

	int nExt = m_aWkspExts.GetSize();

	while (nExt--)
	{
		if (m_aWkspExts[nExt].CompareNoCase(szExt) == 0)
			return TRUE;
	}

	return FALSE;
}

BOOL CProjectZipBase::IsProject(LPCTSTR szFilePath) const
{
	TCHAR szExt[_MAX_EXT];
	_tsplitpath(szFilePath, NULL, NULL, NULL, szExt);

	int nExt = m_aProjExts.GetSize();

	while (nExt--)
	{
		if (m_aProjExts[nExt].CompareNoCase(szExt) == 0)
			return TRUE;
	}

	return FALSE;
}

void CProjectZipBase::Zip(CString& sDestPath, DWORD dwFlags)
{
	if (dwFlags == (DWORD)-1)
		dwFlags = COptionsDlg().GetOptions();

	m_dwOptions = dwFlags;

	ASSERT (IsProject(m_sProjectPath) || IsWorkspace(m_sProjectPath));

	if (!IsProject(m_sProjectPath) && !IsWorkspace(m_sProjectPath))
		return;

	CString sZipPath = (LPCTSTR)sDestPath; // forces a copy
	CStringArray aFailures;
	CString sMessage;
	
	BOOL bIsProject = IsProject(m_sProjectPath);
	int nRes = Zip(m_sProjectPath, sZipPath, aFailures);
	
	switch (nRes)
	{
	case PZIP_OK:
		if (aFailures.GetSize())
		{
			int nFile = aFailures.GetSize();
			CString sFiles;
			
			while (nFile--)
			{
				sFiles += '\n';
				sFiles += aFailures[nFile];
			}
			
			sMessage.Format(_T("ProjectZip has successfully zipped the %s to '%s', \nbut the following files could not be added:\n%s"), 
							bIsProject ? _T("project") : _T("workspace"), sZipPath, sFiles);
		}
		else if (!HasOption(PZOPT_OPENZIP) && !HasOption(PZOPT_NOCOMPLETIONMSG))
			sMessage.Format(_T("ProjectZip has successfully zipped the %s to '%s'"), 
							bIsProject ? _T("project") : _T("workspace"), sZipPath);
		
		break;
		
	case PZIP_CREATEFILE:
		sMessage.Format(_T("ProjectZip was unable to create the zip file '%s'"), sZipPath);
		break;
		
	case PZIP_CANCELLED:
		break;
	}
	
	if (!sMessage.IsEmpty())
		MessageBox(m_hwndParent, sMessage, _T("ProjectZip © AbstractSpoon 2003"), MB_OK);
	
	// open the zip 
	if (nRes == PZIP_OK)
	{
		sDestPath = sZipPath;

		if (HasOption(PZOPT_OPENZIP))
		{
			ShellExecute(m_hwndParent, NULL, sZipPath, NULL, NULL, SW_SHOW);
		}
	}
}

CString CProjectZipBase::GetExtension(LPCTSTR szFilePath)
{
	TCHAR szExt[_MAX_EXT];

	_tsplitpath(szFilePath, NULL, NULL, NULL, szExt);

	if (szExt[0] == '.')
		return CString(szExt + 1);
	else
		return CString(szExt);
}

void CProjectZipBase::AddOtherProjFileExtension(LPCTSTR szExt)
{
	CString sExt(szExt);

	sExt.TrimLeft();
	sExt.TrimRight();

	if (sExt[0] != '.')
		sExt = "." + sExt;

	m_aOtherProjFileExts.Add(sExt);
}

void CProjectZipBase::AddProjectExtension(LPCTSTR szExt)
{
	CString sExt(szExt);

	sExt.TrimLeft();
	sExt.TrimRight();

	if (sExt[0] != '.')
		sExt = _T(".") + sExt;

	m_aProjExts.Add(sExt);
}

void CProjectZipBase::AddWorkspaceExtension(LPCTSTR szExt)
{
	CString sExt(szExt);

	sExt.TrimLeft();
	sExt.TrimRight();

	if (sExt[0] != '.')
		sExt = _T(".") + sExt;

	m_aWkspExts.Add(sExt);
}

CString CProjectZipBase::FormatOtherProjFileExtString()
{
	CString sExts;

	for (int nExt = 0; nExt < m_aOtherProjFileExts.GetSize(); nExt++)
	{
		if (!sExts.IsEmpty())
			sExts += _T(", ");

		sExts += m_aOtherProjFileExts[nExt];
	}

	return sExts;
}

CString CProjectZipBase::FormatProjectFileExtString()
{
	CString sExts;

	for (int nExt = 0; nExt < m_aProjExts.GetSize(); nExt++)
	{
		if (!sExts.IsEmpty())
			sExts += _T(", ");

		sExts += m_aProjExts[nExt];
	}

	return sExts;
}

CString CProjectZipBase::FormatWorkspaceFileExtString()
{
	CString sExts;

	for (int nExt = 0; nExt < m_aWkspExts.GetSize(); nExt++)
	{
		if (!sExts.IsEmpty())
			sExts += _T(", ");

		sExts += m_aWkspExts[nExt];
	}

	return sExts;
}
