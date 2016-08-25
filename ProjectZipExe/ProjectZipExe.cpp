// ProjectZipExe.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ProjectZipExe.h"
#include "shlwapi.h"

#include "..\projectzip\projectzip6.h"
#include "..\projectzip\projectzip7.h"
#include "..\projectzip\optionsdlg.h"
#include "..\projectzip\pzutil.h"
#include "..\shared\encommandlineinfo.h"
#include "..\shared\filemisc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExeApp

BEGIN_MESSAGE_MAP(CProjectZipExeApp, CWinApp)
	//{{AFX_MSG_MAP(CProjectZipExeApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExeApp construction

CProjectZipExeApp::CProjectZipExeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CProjectZipExeApp object

CProjectZipExeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExeApp initialization

BOOL CProjectZipExeApp::InitInstance()
{
	SetRegistryKey(_T("AbstractSpoon"));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	AfxOleInit(); // for initializing COM and handling drag and drop via explorer

	m_pMainWnd = NULL;
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// options
	CEnCommandLineInfo cli;
	ParseCommandLine(cli);

	if (cli.HasOption(_T("O"))) // options only
	{
		COptionsDlg(NULL, hIcon).DoModal();
		return FALSE;
	}
	
	CString sFilePath(cli.m_strFileName);
	
	// commandline options
	DWORD dwOptions = 0;

	if (cli.HasOption(_T("SA")))
		dwOptions |= PZOPT_SHOWSAVEAS;

	if (cli.HasOption(_T("IW")))
		dwOptions |= PZOPT_INCLUDEWORKSPACE;
	
	if (cli.HasOption(_T("OZ")))
		dwOptions |= PZOPT_OPENZIP;
	
	if (cli.HasOption(_T("PO")))
		dwOptions |= PZOPT_PROMPTOVERWRITE;
	
	if (cli.HasOption(_T("PM")))
		dwOptions |= PZOPT_PROMPTIFMULTI;
	
	if (cli.HasOption(_T("ML")))
		dwOptions |= PZOPT_MAKELOWER;
	
	if (cli.HasOption(_T("IO")))
		dwOptions |= PZOPT_INCLUDEOTHERPROJFILES;
	
	if (cli.HasOption(_T("BV")))
		dwOptions |= PZOPT_BREAKVSSLINK;
	
	if (cli.HasOption(_T("NM")))
		dwOptions |= PZOPT_NOCOMPLETIONMSG;

	if (cli.HasOption(_T("U"))) // unzip
	{
		// we have to try both vc6 and vc7 because we don't know which it will be
		IProjectZip* pPZip = PZGetInterfaceByType(VC6PROJECT);

		TCHAR szFilePath[MAX_PATH] = _T(""), szOutputPath[MAX_PATH] = _T("");
		lstrcpy(szFilePath, sFilePath);

		int nRes = pPZip->Open(szFilePath, szOutputPath, FALSE);
		pPZip->Release();

		if (nRes == 0)
		{
			pPZip = PZGetInterfaceByType(VC7PROJECT);

			nRes = pPZip->Open(szFilePath, szOutputPath, FALSE);
			pPZip->Release();
		}

		switch (nRes)
		{
		case 0:
			{
				CString sMessage;
				sMessage.Format(_T("The file '%s'\ndoes not appear to contain a project or workspace file\nfor either Visual Studio 6 or 7 (.NET)."),
								szFilePath);

				MessageBox(NULL, sMessage, _T("ProjectZip © AbstractSpoon 2004"), MB_OK);
			}
			// drop thru

		case 1:
			ShellExecute(NULL, _T("open"), szOutputPath, NULL, NULL, SW_SHOWNORMAL);
			break;
		}
	}
	else // zip
	{
		// if no file has been specified and bUnzip == FALSE and bOptionsOnly == FALSE
		// then display a file open dialog to let the user select
		if (sFilePath.IsEmpty())
		{
			const LPCTSTR FILTER = _T("VC6 Project Files (*.dsp, *.dsw)|*.dsp;*.dsw|VS Project Files (*.sln, *.vcxproj, *.vcproj, *.csproj)|;*.sln;*.vcproj;*.vcxproj;*.csproj||");

			CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, FILTER);

			dialog.m_ofn.lpstrTitle = _T("Select Project to Zip - ProjectZip © AbstractSpoon 2004");
			dialog.m_ofn.nFilterIndex = AfxGetApp()->GetProfileInt(_T(""), _T("LastFilter"), 1);

			if (dialog.DoModal() == IDOK)
			{
				sFilePath = dialog.GetPathName();

				// save filter index
				AfxGetApp()->WriteProfileInt(_T(""), _T("LastFilter"), dialog.m_ofn.nFilterIndex);
			}
		}
		else if (PathIsRelative(sFilePath)) // make it absolute
			FileMisc::MakePath(sFilePath, NULL, FileMisc::GetCwd(), sFilePath);

		IProjectZip* pPZip = PZGetInterface((LPCTSTR)sFilePath);

		if (pPZip)
		{
			// get last save path
			sFilePath.Replace('\\', '_');
			sFilePath.Replace(':', '_');

			CString sZipPath = AfxGetApp()->GetProfileString(_T("LastSaveAs"), sFilePath, _T(""));

			// override from commandline
			if (cli.HasOption(_T("ZP")))
				sZipPath = cli.GetOption(_T("ZP"));

			if (cli.HasOption(_T("Q"))) // quick zip
			{
				pPZip->Zip(sZipPath);

				if (PathIsRelative(sZipPath)) // make it absolute
					FileMisc::MakePath(sZipPath, NULL, FileMisc::GetCwd(), sZipPath);
			}
			else if (sZipPath.IsEmpty() || !dwOptions)
				pPZip->ShowOptions(hIcon, sZipPath);
			else
				pPZip->Zip(sZipPath, dwOptions);

			// if sZipPath has been filled in then save the path mapping to the registry
			if (!sZipPath.IsEmpty())
				AfxGetApp()->WriteProfileString(_T("LastSaveAs"), sFilePath, sZipPath);

			pPZip->Release();
		}
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

