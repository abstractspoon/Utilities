// MiniSpy.h : main header file for the MINISPY application
//

#if !defined(AFX_MINISPY_H__B12CCE3C_838C_46B1_BD09_FF05B4E7F05C__INCLUDED_)
#define AFX_MINISPY_H__B12CCE3C_838C_46B1_BD09_FF05B4E7F05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMiniSpyApp:
// See MiniSpy.cpp for the implementation of this class
//

class CMiniSpyApp : public CWinApp
{
public:
	CMiniSpyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiniSpyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMiniSpyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINISPY_H__B12CCE3C_838C_46B1_BD09_FF05B4E7F05C__INCLUDED_)
