// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "ProjectZip6Addin.h"
#include "Commands.h"

#include "..\ProjectZip6.h"
#include "..\optionsdlg.h"
#include "..\pzutil.h"

#include <COMDEF.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
}

void CCommands::SetWorkspaceFolder(LPCTSTR szFolder)
{
	m_sWorkspaceFolder = szFolder;
}

/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// save the dsw path here
	BSTR bsPath;

	if (SUCCEEDED(m_pCommands->GetApplicationObject()->get_CurrentDirectory(&bsPath)))  
		m_pCommands->SetWorkspaceFolder((LPCTSTR)_bstr_t(bsPath));

	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pCommands->SetWorkspaceFolder(_T(""));

	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

enum { PZIP_OK, PZIP_CREATEFILE, PZIP_CANCELLED };

STDMETHODIMP CCommands::PZQuickZipWorkspaceCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString sPath = GetWorkspacePath();
	IProjectZip* pPZ = PZGetInterface(sPath);

	if (pPZ)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
		CWaitCursor cursor;

		// get last save path
		sPath.Replace('\\', '_');
		sPath.Replace(':', '_');

		CString sZipPath = AfxGetApp()->GetProfileString(_T("LastSaveAs"), sPath, _T(""));

		pPZ->Zip(sZipPath);
		pPZ->Release();
		
		// if sZipPath has been filled in then save the path mapping to the registry
		if (!sZipPath.IsEmpty())
			AfxGetApp()->WriteProfileString(_T("LastSaveAs"), sPath, sZipPath);

		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	}

	return S_OK;
}

CString CCommands::GetWorkspacePath()
{
	CString sPath;

	// use the workspacefolder to find a dsw
	if (!m_sWorkspaceFolder.IsEmpty())
	{
		CString sSearch(m_sWorkspaceFolder);
		sSearch += _T("\\*.dsw");

		WIN32_FIND_DATA findFileData;
		HANDLE hFind = FindFirstFile(sSearch, &findFileData);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			sPath = m_sWorkspaceFolder + '\\';
			sPath += findFileData.cFileName;
		}
			
		FindClose(hFind);

	}

	if (sPath.IsEmpty())
	{
		CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, 
						_T("Visual Studio 6 Workspaces (*.dsw)|*.dsw||"));

		dialog.m_ofn.lpstrTitle = _T("ProjectZip © AbstractSpoon 2003 - Select Workspace to Zip");

		if (dialog.DoModal() == IDOK)
			sPath = dialog.GetPathName();
	}

	return sPath;
}

STDMETHODIMP CCommands::PZOptionsZipWorkspaceCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString sPath = GetWorkspacePath();
	IProjectZip* pPZ = PZGetInterface(sPath);

	if (pPZ)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

		// get last save path
		sPath.Replace('\\', '_');
		sPath.Replace(':', '_');

		CString sZipPath = AfxGetApp()->GetProfileString(_T("LastSaveAs"), sPath, _T(""));

		pPZ->ShowOptions(AfxGetApp()->LoadIcon(IDI_ICON), sZipPath);
		pPZ->Release();

		// if sZipPath has been filled in then save the path mapping to the registry
		if (!sZipPath.IsEmpty())
			AfxGetApp()->WriteProfileString(_T("LastSaveAs"), sPath, sZipPath);

		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	}

	return S_OK;
}

STDMETHODIMP CCommands::PZQuickZipProjectCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString sPath = GetProjectPath();
	IProjectZip* pPZ = PZGetInterface(sPath);

	if (pPZ)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
		CWaitCursor cursor;

		// get last save path
		sPath.Replace('\\', '_');
		sPath.Replace(':', '_');

		CString sZipPath = AfxGetApp()->GetProfileString(_T("LastSaveAs"), sPath, _T(""));

		pPZ->Zip(sZipPath);
		pPZ->Release();

		// if sZipPath has been filled in then save the path mapping to the registry
		if (!sZipPath.IsEmpty())
			AfxGetApp()->WriteProfileString(_T("LastSaveAs"), sPath, sZipPath);

		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	}

	return S_OK;
}

CString CCommands::GetProjectPath()
{
	CString sPath;
	IGenericProject* pProject = NULL;
	
	if (SUCCEEDED(m_pApplication->get_ActiveProject((IDispatch**)&pProject)))
	{
		BSTR bsName;

		if (SUCCEEDED(pProject->get_FullName(&bsName)))  
			sPath = (LPCTSTR)_bstr_t(bsName);

		pProject->Release();
	}

	if (sPath.IsEmpty())
	{
		CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, 
						_T("Visual Studio 6 Projects (*.dsp)|*.dsp||"));

		dialog.m_ofn.lpstrTitle = _T("ProjectZip © AbstractSpoon 2003 - Select Project to Zip");

		if (dialog.DoModal() == IDOK)
			sPath = dialog.GetPathName();
	}

	return sPath;
}

STDMETHODIMP CCommands::PZOptionsZipProjectCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString sPath = GetProjectPath();
	IProjectZip* pPZ = PZGetInterface(sPath);

	if (pPZ)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
		CWaitCursor cursor;

		// get last save path
		sPath.Replace('\\', '_');
		sPath.Replace(':', '_');

		CString sZipPath = AfxGetApp()->GetProfileString(_T("LastSaveAs"), sPath, _T(""));

		pPZ->ShowOptions(AfxGetApp()->LoadIcon(IDI_ICON), sZipPath);
		pPZ->Release();

		// if sZipPath has been filled in then save the path mapping to the registry
		if (!sZipPath.IsEmpty())
			AfxGetApp()->WriteProfileString(_T("LastSaveAs"), sPath, sZipPath);

		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	}

	return S_OK;
}

STDMETHODIMP CCommands::PZOpenProjectCommandMethod()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	CWaitCursor cursor;

	IGenericProject* pProject = NULL;
	
	if (SUCCEEDED(m_pApplication->get_ActiveProject((IDispatch**)&pProject)))
	{
		m_pApplication->ExecuteCommand(L"WorkspaceClose");
		pProject->Release();
	}

	// see if the user cancelled
	if (SUCCEEDED(m_pApplication->get_ActiveProject((IDispatch**)&pProject)))
	{
		pProject->Release();
		return S_OK;
	}

	OpenProject();

	return S_OK;
}

void CCommands::OpenProject()
{
	CString sProjectFile;

	IProjectZip* pPZ = PZGetInterfaceByType(VC6PROJECT); 

	if (pPZ)
	{
		pPZ->Open(sProjectFile.GetBuffer(MAX_PATH));
		pPZ->Release();

		sProjectFile.ReleaseBuffer();
	}

	// open the file
	if (!sProjectFile.IsEmpty())
	{
		IDocuments* pDocs = NULL; 
				
		if (SUCCEEDED(m_pApplication->get_Documents((IDispatch**)&pDocs)))
		{					
			IGenericDocument* pDoc = NULL; 
			HRESULT hr = pDocs->Open(_bstr_t(sProjectFile), CComVariant("Auto"), _variant_t(false), (IDispatch**)&pDoc);
					
			if (FAILED(hr))
			{
				CString sMessage;
				sMessage.Format(_T("The project '%s' could not be opened."), sProjectFile);
							
				MessageBox(NULL, sMessage, _T("ProjectZip © AbstractSpoon 2003"), MB_OK);
			}
		}
	}
}

