// ProjectZipExe.h : main header file for the PROJECTZIPEXE application
//

#if !defined(AFX_PROJECTZIPEXE_H__081FC52C_DF8B_4528_A0DE_FA48A25A02F1__INCLUDED_)
#define AFX_PROJECTZIPEXE_H__081FC52C_DF8B_4528_A0DE_FA48A25A02F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProjectZipExeApp:
// See ProjectZipExe.cpp for the implementation of this class
//

class CProjectZipExeApp : public CWinApp
{
public:
	CProjectZipExeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectZipExeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProjectZipExeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTZIPEXE_H__081FC52C_DF8B_4528_A0DE_FA48A25A02F1__INCLUDED_)
