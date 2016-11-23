// FindIncludes.h : main header file for the WINSYMLIB application
//

#if !defined(AFX_WINSYMLIB_H__05D64898_DE39_4F25_89CD_6BDA358E8F34__INCLUDED_)
#define AFX_WINSYMLIB_H__05D64898_DE39_4F25_89CD_6BDA358E8F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesApp:
// See FindIncludes.cpp for the implementation of this class
//

class CFindIncludesApp : public CWinApp
{
public:
	CFindIncludesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindIncludesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFindIncludesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSYMLIB_H__05D64898_DE39_4F25_89CD_6BDA358E8F34__INCLUDED_)
