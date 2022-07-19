// InterspyWnd.h : main header file for the INTERSPYWND application
//

#if !defined(AFX_INTERSPYWND_H__E32AED35_1A81_4F87_9B25_373793075DF5__INCLUDED_)
#define AFX_INTERSPYWND_H__E32AED35_1A81_4F87_9B25_373793075DF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterspyWndApp:
// See InterspyWnd.cpp for the implementation of this class
//

class CInterspyWndApp : public CWinApp
{
public:
	CInterspyWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterspyWndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CInterspyWndApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERSPYWND_H__E32AED35_1A81_4F87_9B25_373793075DF5__INCLUDED_)
