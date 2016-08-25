// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__F4831A7F_8DB7_4681_BDE9_A07F1FCE2A5D__INCLUDED_)
#define AFX_DSADDIN_H__F4831A7F_8DB7_4681_BDE9_A07F1FCE2A5D__INCLUDED_

#include "commands.h"

// {00B25757-17E0-4384-ABC9-FC189FAD7468}
DEFINE_GUID(CLSID_DSAddIn,
0xb25757, 0x17e0, 0x4384, 0xab, 0xc9, 0xfc, 0x18, 0x9f, 0xad, 0x74, 0x68);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, _T("ProjectZip.DSAddIn.1"),
		_T("PROJECTZIP Developer Studio Add-in"), IDS_PROJECTZIP6ADDIN_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__F4831A7F_8DB7_4681_BDE9_A07F1FCE2A5D__INCLUDED)
