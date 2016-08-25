// ProjectZipExt.cpp : Implementation of CProjectZipExt
#include "stdafx.h"
#include "ProjectZipShExt.h"
#include "ProjectZipExt.h"

#include "..\pzutil.h"
#include "..\projectzip6.h"
#include "..\projectzip7.h"

#include <atlconv.h>  // for ATL string conversion macros
#include <afxdlgs.h>  

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExt

HRESULT CProjectZipExt::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID)
{
	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP     hDrop;

	m_sFilePath.Empty();

    // Look for CF_HDROP data in the data object.
    if (FAILED(pDataObj->GetData (&fmt, &stg))) 
	{
        // Nope! Return an "invalid argument" error back to Explorer.
        return E_INVALIDARG;
	}
	
    // Get a pointer to the actual data.
    hDrop = (HDROP) GlobalLock (stg.hGlobal);
	
    // Make sure it worked.
    if (NULL == hDrop)
	{
        return E_INVALIDARG;
	}
	
	UINT uNumFiles = DragQueryFile (hDrop, 0xFFFFFFFF, NULL, 0);
	
    if (1 != uNumFiles)
	{
        GlobalUnlock (stg.hGlobal);
        ReleaseStgMedium (&stg);
        return E_INVALIDARG;
	}
	
	HRESULT hr = S_OK;
	
    // Get the name of the first file and store it in our member variable m_sFilePath.
    if (0 == DragQueryFile (hDrop, 0, m_sFilePath.GetBuffer(MAX_PATH), MAX_PATH))
	{
        hr = E_INVALIDARG;
	}
	
	m_sFilePath.ReleaseBuffer();

    GlobalUnlock (stg.hGlobal);
    ReleaseStgMedium (&stg);

	// check it has the right file extension
	DWORD dwAttrib = GetFileAttributes(m_sFilePath);

	if (dwAttrib == 0xffffffff || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) || PZGetFileType(m_sFilePath) == UNKNOWN)
	{
        hr = E_INVALIDARG;
	}
	
    return hr;
	
}

HRESULT CProjectZipExt::QueryContextMenu (HMENU hmenu, UINT  uMenuIndex, UINT  uidFirstCmd, UINT  uidLastCmd, UINT  uFlags )
{
    // If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
    if ( uFlags & CMF_DEFAULTONLY )
	{
        return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );
	}

	CString sMenuText, sFileName;

	sFileName = m_sFilePath.Mid(m_sFilePath.ReverseFind('\\') + 1);
	sMenuText.Format("ProjectZip '%s'", sFileName);
	
    InsertMenu ( hmenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, sMenuText );
	
    return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 1 );
}


HRESULT CProjectZipExt::GetCommandString(UINT  idCmd, UINT  uFlags, UINT* pwReserved, LPSTR pszName, UINT  cchMax )
{
    USES_CONVERSION;
	
    // Check idCmd, it must be 0 since we have only one menu item.
    if ( 0 != idCmd )
        return E_INVALIDARG;
	
    // If Explorer is asking for a help string, copy our string into the
    // supplied buffer.
    if ( uFlags & GCS_HELPTEXT )
	{
        LPCTSTR szText = _T("Runs ProjectZip on the selected file");
		
        if ( uFlags & GCS_UNICODE )
		{
            // We need to cast pszName to a Unicode string, and then use the
            // Unicode string copy API.
            lstrcpynW ( (LPWSTR) pszName, T2CW(szText), cchMax );
		}
        else
		{
            // Use the ANSI string copy API to return the help string.
            lstrcpynA ( pszName, T2CA(szText), cchMax );
		}
		
        return S_OK;
	}
	
    return E_INVALIDARG;
}

HRESULT CProjectZipExt::InvokeCommand ( LPCMINVOKECOMMANDINFO pCmdInfo )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // If lpVerb really points to a string, ignore this function call and bail out.
    if ( 0 != HIWORD( pCmdInfo->lpVerb ))
        return E_INVALIDARG;

	HRESULT hr = E_INVALIDARG;

    // Get the command index - the only valid one is 0.
    switch ( LOWORD( pCmdInfo->lpVerb ))
        {
        case 0:
            {
				IProjectZip* pPZip = PZGetInterface(m_sFilePath);

				if (pPZip)
				{
					// get last save path
					m_sFilePath.Replace('\\', '_');
					m_sFilePath.Replace(':', '_');

					CString sZipPath = AfxGetApp()->GetProfileString("LastSaveAs", m_sFilePath, "");

					pPZip->ShowOptions(AfxGetApp()->LoadIcon(IDI_ICON), sZipPath);
					hr = S_OK;

					// if sZipPath has been filled in then save the path mapping to the registry
					if (!sZipPath.IsEmpty())
						AfxGetApp()->WriteProfileString("LastSaveAs", m_sFilePath, sZipPath);

					pPZip->Release();
				}
            }
        break;
        }

    return hr;
}

