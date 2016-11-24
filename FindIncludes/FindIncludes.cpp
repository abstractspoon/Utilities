// FindIncludes.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FindIncludes.h"
#include "FindIncludesDlg.h"

#include "..\..\ToDoList_Core\shared\LimitSingleInstance.h"
#include "..\..\ToDoList_Core\shared\EnCommandLineInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLimitSingleInstance g_lsi(_T("{1C399D9E-ABCD-46B0-8828-A222A5123F54}"));
BOOL CALLBACK FindOtherInstance(HWND hwnd, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesApp

BEGIN_MESSAGE_MAP(CFindIncludesApp, CWinApp)
	//{{AFX_MSG_MAP(CFindIncludesApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesApp construction

CFindIncludesApp::CFindIncludesApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFindIncludesApp object

CFindIncludesApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesApp initialization

BOOL CFindIncludesApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	CoInitialize(NULL);

	CEnCommandLineInfo cmd;
	ParseCommandLine(cmd);

	CString sFileName, sFileExt, sFunction;

	cmd.GetOption(_T("s"), sFileName);
	cmd.GetOption(_T("e"), sFileExt);
	cmd.GetOption(_T("f"), sFunction);

	if (g_lsi.IsAnotherInstanceRunning())
	{
		HWND hWnd = NULL;
		EnumWindows(FindOtherInstance, (LPARAM)&hWnd);

		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetForegroundWindow(hWnd);

			// pass on file to open
			if (!sFileName.IsEmpty())
			{
				COPYDATASTRUCT cds = { 0 };
				FINDINCLUDESCOPYDATA wsl = { 0 };

				lstrcpy(wsl.szFileName, sFileName);
				lstrcpy(wsl.szFileExt, sFileExt);
				lstrcpy(wsl.szFunction, sFunction);

				cds.dwData = WSL_NEWSYMBOL;
				cds.cbData = sizeof(FINDINCLUDESCOPYDATA);
				cds.lpData = (LPVOID)&wsl;

				SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&cds);
			}

			return FALSE;
		}
	}

	CFindIncludesDlg dlg(sFileName, sFileExt, sFunction);
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CALLBACK FindOtherInstance(HWND hwnd, LPARAM lParam)
{
	DWORD dwResult = 0;

	if (SendMessageTimeout(hwnd, WM_ISWINSYMLIBDLG, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, &dwResult))
	{
		if (dwResult == ISWINSYMLIBDLG_ANSWER)
		{
			HWND* pWnd = (HWND*)lParam;
			*pWnd = hwnd;
			return FALSE;
		}
	}

	return TRUE;
}

