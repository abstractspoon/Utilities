// EasyFtp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EasyFtp.h"

#include "..\shared\remotefile.h"
#include "..\shared\encommandlineinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyFtpApp

BEGIN_MESSAGE_MAP(CEasyFtpApp, CWinApp)
	//{{AFX_MSG_MAP(CEasyFtpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyFtpApp construction

CEasyFtpApp::CEasyFtpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEasyFtpApp object

CEasyFtpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEasyFtpApp initialization

BOOL CEasyFtpApp::InitInstance()
{
	// Standard initialization
	SetRegistryKey(_T("AbstractSpoon"));

	// parse command line
	CEnCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CString sRemotePath, sLocalPath;
	CString sAgent, sServer, sUsername, sPassword;

// ------------------------------------------------------------------------------
#ifdef GALLOT
	BOOL bUpload = FALSE;
	BOOL bNoLowercase = FALSE;
	BOOL bRepeat = FALSE;
	BOOL bAnonymousLogin = FALSE;
	BOOL bNoConfirmOverwrite = FALSE;

	sRemotePath = "gallery/";
	sServer = "ftp.district-crecy.com";
	cmdInfo.m_strFileName.Empty();
// ------------------------------------------------------------------------------
#else
	BOOL bUpload = cmdInfo.GetOption("up");
	BOOL bNoLowercase = cmdInfo.GetOption("nl");
	BOOL bRepeat = cmdInfo.GetOption("rt");
	BOOL bAnonymousLogin = cmdInfo.GetOption("an");
	BOOL bNoConfirmOverwrite = cmdInfo.GetOption("nc");

	cmdInfo.GetOption("rp", sRemotePath);
	cmdInfo.GetOption("lp", sLocalPath);
	cmdInfo.GetOption("ag", sAgent);
	cmdInfo.GetOption("sv", sServer);
	cmdInfo.GetOption("us", sUsername);
	cmdInfo.GetOption("pw", sPassword);
#endif
// ------------------------------------------------------------------------------

	if (sLocalPath.IsEmpty() && !cmdInfo.m_strFileName.IsEmpty())
	{
		sLocalPath = CEnCommandLineInfo::ResolveShortcut(cmdInfo.m_strFileName);

		if (!sLocalPath.IsEmpty()) // valid existing file
		{
			bUpload = TRUE; // what else could it be?
			bRepeat = FALSE;
		}
	}

	CRemoteFile rf(sAgent, sServer, sUsername, sPassword);

	if (bUpload)
	{
		DWORD dwOptions = RMO_ALLOWDIALOG | RMO_DELETEFAILURES;
		
		if (!bNoLowercase)
			dwOptions |= RMO_LOWERCASEPATHS;

		if (bAnonymousLogin)
			dwOptions |= RMO_ANONYMOUSLOGIN;

		if (!bNoConfirmOverwrite)
			dwOptions |= RMO_CONFIRMOVERWRITE;

		RMERR nErr = RMERR_SUCCESS;

		do
		{
			nErr = rf.SetFile(sLocalPath, sRemotePath, dwOptions);

			switch (nErr)
			{
			case RMERR_SUCCESS:
			case RMERR_USERCANCELLED:
				break;

			default:
				{
					CString sMessage;

					if (sLocalPath.IsEmpty())
						sMessage.Format("Sorry, the requested upload to '%s' could not be completed \nfor the following reason:\n\n%s",
										sServer, rf.GetLastError());
					else
						sMessage.Format("Sorry, the upload of '%s' to '%s' \ncould not be completed for the following reason:\n\n%s",
										sLocalPath, sServer, rf.GetLastError());

					AfxMessageBox(sMessage, MB_OK | MB_ICONEXCLAMATION);
				}
				break;
			}

			sLocalPath.Empty();
			sRemotePath.Empty();
		}
		while (bRepeat && nErr != RMERR_USERCANCELLED);
	}
	else
	{
		DWORD dwOptions = RMO_ALLOWDIALOG | RMO_CREATEDOWNLOADDIR;
		
// ------------------------------------------------------------------------------
#ifdef GALLOT
		dwOptions |= RMO_NOANONYMOUSLOGIN | RMO_NONAVIGATE | RMO_CONFIRMOVERWRITE;
#else
// ------------------------------------------------------------------------------
		if (bAnonymousLogin)
			dwOptions |= RMO_ANONYMOUSLOGIN;

		if (!bNoConfirmOverwrite)
			dwOptions |= RMO_CONFIRMOVERWRITE;
#endif
// ------------------------------------------------------------------------------

		RMERR nErr = RMERR_SUCCESS;

		do
		{
			nErr = rf.GetFile(sRemotePath, sLocalPath, dwOptions);

			switch (nErr)
			{
			case RMERR_SUCCESS:
#ifdef _DEBUG
				ShellExecute(NULL, NULL, sLocalPath, NULL, NULL, SW_SHOWNORMAL);
#endif
				break;
				
			case RMERR_USERCANCELLED:
				break;
				
			default:
				{
					CString sMessage;
					
					if (sRemotePath.IsEmpty())
						sMessage.Format("Sorry, the requested download from '%s' could not be completed \nfor the following reason:\n\n%s",
										sServer, rf.GetLastError());
					else
						sMessage.Format("Sorry, the download of '%s' from '%s' \ncould not be completed for the following reason:\n\n%s",
										sRemotePath, sServer, rf.GetLastError());

					AfxMessageBox(sMessage, MB_OK | MB_ICONEXCLAMATION);
				}
			}

			sLocalPath.Empty();
			sRemotePath.Empty();
		}
		while (bRepeat && nErr != RMERR_USERCANCELLED);
	}

	// done
	return FALSE;
}
