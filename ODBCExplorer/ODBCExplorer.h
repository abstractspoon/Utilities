// ODBCExplorer.h : main header file for the ODBCEXPLORER application
//

#if !defined(AFX_ODBCEXPLORER_H__526C3625_844F_498A_AD5E_2F836CF2A499__INCLUDED_)
#define AFX_ODBCEXPLORER_H__526C3625_844F_498A_AD5E_2F836CF2A499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CODBCExplorerApp:
// See ODBCExplorer.cpp for the implementation of this class
//

class CODBCExplorerApp : public CWinApp
{
public:
	CODBCExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBCExplorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CODBCExplorerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBCEXPLORER_H__526C3625_844F_498A_AD5E_2F836CF2A499__INCLUDED_)
