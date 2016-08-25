// ProjectZipExt.h : Declaration of the CProjectZipExt

#ifndef __PROJECTZIPEXT_H_
#define __PROJECTZIPEXT_H_

#include "resource.h"       // main symbols
#include <shlobj.h>
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExt

class IProjectZip;

class ATL_NO_VTABLE CProjectZipExt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProjectZipExt, &CLSID_ProjectZipExt>,
	public IDispatchImpl<IProjectZipExt, &IID_IProjectZipExt, &LIBID_PROJECTZIPSHEXTLib>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CProjectZipExt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROJECTZIPEXT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProjectZipExt)
	COM_INTERFACE_ENTRY(IProjectZipExt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu) 
END_COM_MAP()

// IProjectZipExt
public:
	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

	// IContextMenu
    STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT);
    STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
    STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);

protected:
	CString m_sFilePath;
};

#endif //__PROJECTZIPEXT_H_
