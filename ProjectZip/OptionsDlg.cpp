// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsDlg.h"
#include "projectzip6.h"
#include "projectzip7.h"

#include "pzutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

#define IDSAVE					1001
#define IDC_SHOWSAVEAS			1002
#define IDC_INCLUDEDSW			1003
#define IDC_INCLUDEOTHERPROJ	1004
#define IDC_OPENZIP				1005
#define IDC_MAKELOWER			1006
#define IDC_PROMPTOVERWRITE		1007
#define IDC_OPENLIKELY			1008
#define IDC_PROMPTMULTI			1009
#define IDC_BREAKVSSLINK		1010

COptionsDlg::COptionsDlg(LPCTSTR szFilePath, HICON hIcon, CWnd* pParent /*=NULL*/)
	 : CRuntimeDlg(), m_sFilePath(szFilePath), m_hIcon(hIcon)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	//}}AFX_DATA_INIT
	m_bShowSaveAs = AfxGetApp()->GetProfileInt(_T(""), _T("ShowSaveAs"), TRUE);
	m_bIncludeDsw = AfxGetApp()->GetProfileInt(_T(""), _T("IncludeDsw"), TRUE);
	m_bOpenZip = AfxGetApp()->GetProfileInt(_T(""), _T("OpenZip"), FALSE);
	m_bPromptOverwrite = AfxGetApp()->GetProfileInt(_T(""), _T("PromptOverwrite"), TRUE);
	m_nResolveMulti = AfxGetApp()->GetProfileInt(_T(""), _T("ResolveMulti"), 0);
	m_bMakeLower = AfxGetApp()->GetProfileInt(_T(""), _T("MakeLower"), FALSE);
	m_bIncludeOtherProjFiles = AfxGetApp()->GetProfileInt(_T(""), _T("IncludeOtherProjFiles"), FALSE);
	m_bBreakVSSLink = AfxGetApp()->GetProfileInt(_T(""), _T("BreakVSSLink"), TRUE);

	AddRCControl(_T("LTEXT"), _T(""), _T("Zipping"), 0, 0, 7,7,28,10, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("static"), _T(""), SS_ETCHEDHORZ, 0, 37,12,220,1, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Display 'Save As...' dialog"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15,21,240,10, IDC_SHOWSAVEAS);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Make zip filename lowercase"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15,36, 240,10, IDC_MAKELOWER);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Include workspace file if present"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15, 51,240,10, IDC_INCLUDEDSW);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Include other 'non-essential' project files if present"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15, 65,240,10, IDC_INCLUDEOTHERPROJ);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("After zipping, open zip file for verification"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15, 79, 240,10, IDC_OPENZIP);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Break VSS Links"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15, 93, 240,10, IDC_BREAKVSSLINK);
	AddRCControl(_T("LTEXT"), _T(""), _T("Unzipping"), 0, 0, 7,112,36,10, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("static"), _T(""), SS_ETCHEDHORZ, 0, 45,117,212,1, IDC_STATIC);
	AddRCControl(_T("LTEXT"), _T(""), _T("If multiple project files are found in the zip file:"), 0, 0, 15,126,240,8, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Prompt to select"), BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP, 0, 22,138,240,10, IDC_PROMPTMULTI);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Open the most likely candidate"), BS_AUTORADIOBUTTON | WS_TABSTOP, 0, 22,151,240,10, IDC_OPENLIKELY);
	AddRCControl(_T("LTEXT"), _T(""), _T("Miscellaneous"), 0, 0, 7,169,50,10, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("static"), _T(""), SS_ETCHEDHORZ, 0, 58,174,199,1, IDC_STATIC);
	AddRCControl(_T("CONTROL"), _T("Button"), _T("Prompt before overwriting existing files"), BS_AUTOCHECKBOX | WS_TABSTOP, 0, 15,182,240,10, IDC_PROMPTOVERWRITE);
	AddRCControl(_T("CONTROL"), _T("static"), _T(""), SS_ETCHEDHORZ, 0, 7,201,248,1, IDC_STATIC);
	AddRCControl(_T("PUSHBUTTON"), _T(""), _T("Save As Default"), 0, 0, 7,208,64,14, IDSAVE);
	AddRCControl(_T("PUSHBUTTON"), _T(""), _T("Zip"), 0, 0, 149,208,50,14, IDOK);
	AddRCControl(_T("PUSHBUTTON"), _T(""), _T("Close"), 0, 0, 205,208,50,14, IDCANCEL);
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CRuntimeDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_SHOWSAVEAS, m_bShowSaveAs);
	DDX_Check(pDX, IDC_INCLUDEDSW, m_bIncludeDsw);
	DDX_Check(pDX, IDC_OPENZIP, m_bOpenZip);
	DDX_Radio(pDX, IDC_PROMPTMULTI, m_nResolveMulti);
	DDX_Check(pDX, IDC_PROMPTOVERWRITE, m_bPromptOverwrite);
	DDX_Check(pDX, IDC_MAKELOWER, m_bMakeLower);
	DDX_Check(pDX, IDC_INCLUDEOTHERPROJ, m_bIncludeOtherProjFiles);
	DDX_Check(pDX, IDC_INCLUDEOTHERPROJ, m_bIncludeOtherProjFiles);
	DDX_Check(pDX, IDC_BREAKVSSLINK, m_bBreakVSSLink);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CRuntimeDlg)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDSAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

int COptionsDlg::DoModal()
{
	CString sCaption(_T("ProjectZip © AbstractSpoon 2004"));

	// add file name to caption
	if (!m_sFilePath.IsEmpty())
	{
		TCHAR szFileName[_MAX_FNAME];
		TCHAR szExt[_MAX_EXT];

		_tsplitpath(m_sFilePath, NULL, NULL, szFileName, szExt);

		sCaption.Format(_T("%s%s - ProjectZip © AbstractSpoon 2004"), szFileName, szExt);
	}

	return CRuntimeDlg::DoModal(sCaption);
}

DWORD COptionsDlg::GetOptions()
{
	DWORD dwOptions = 0;

	if (m_bShowSaveAs)
		dwOptions |= PZOPT_SHOWSAVEAS;

	if (m_bIncludeDsw)
		dwOptions |= PZOPT_INCLUDEWORKSPACE;
	
	if (m_bOpenZip)
		dwOptions |= PZOPT_OPENZIP;
	
	if (m_bPromptOverwrite)
		dwOptions |= PZOPT_PROMPTOVERWRITE;
	
	if (m_nResolveMulti)
		dwOptions |= PZOPT_PROMPTIFMULTI;
	
	if (m_bMakeLower)
		dwOptions |= PZOPT_MAKELOWER;
	
	if (m_bIncludeOtherProjFiles)
		dwOptions |= PZOPT_INCLUDEOTHERPROJFILES;
	
	if (m_bBreakVSSLink)
		dwOptions |= PZOPT_BREAKVSSLINK;

	return dwOptions;
}

void COptionsDlg::OnSave() 
{
	UpdateData();

	AfxGetApp()->WriteProfileInt(_T(""), _T("ShowSaveAs"), m_bShowSaveAs);
	AfxGetApp()->WriteProfileInt(_T(""), _T("IncludeDsw"), m_bIncludeDsw);
	AfxGetApp()->WriteProfileInt(_T(""), _T("OpenZip"), m_bOpenZip);
	AfxGetApp()->WriteProfileInt(_T(""), _T("PromptOverwrite"), m_bPromptOverwrite);
	AfxGetApp()->WriteProfileInt(_T(""), _T("ResolveMulti"), m_nResolveMulti);
	AfxGetApp()->WriteProfileInt(_T(""), _T("MakeLower"), m_bMakeLower);
	AfxGetApp()->WriteProfileInt(_T(""), _T("IncludeOtherProjFiles"), m_bIncludeOtherProjFiles);
	AfxGetApp()->WriteProfileInt(_T(""), _T("BreakVSSLink"), m_bBreakVSSLink);
}

BOOL COptionsDlg::OnInitDialog() 
{
	CRuntimeDlg::OnInitDialog();
	
	if (m_hIcon)
	{
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon
	}

	int nFileType = PZGetFileType(m_sFilePath);
	CProjectZipBase* pPZBase = NULL;

#ifdef SUPPORTS_VC6
	if (nFileType == VC6WORKSPACE || nFileType == VC6PROJECT)
	{
		pPZBase = new CProjectZip6;

		GetDlgItem(IDC_INCLUDEDSW)->EnableWindow(nFileType == VC6PROJECT);
	}
#endif

#ifdef SUPPORTS_VC7
	if (nFileType == VC7WORKSPACE || nFileType == VC7PROJECT)
	{
		pPZBase = new CProjectZip7;

		GetDlgItem(IDC_INCLUDEDSW)->EnableWindow(nFileType == VC7PROJECT);
		GetDlgItem(IDC_BREAKVSSLINK)->EnableWindow(FALSE);

		m_bBreakVSSLink = FALSE;
		UpdateData(FALSE);
	}
#endif

	GetDlgItem(IDOK)->EnableWindow(nFileType != UNKNOWN);

	// modify ctrl text based on file type
	if (pPZBase)
	{
		CString sText, sModText;

		GetDlgItem(IDC_INCLUDEDSW)->GetWindowText(sText);
		sModText.Format(_T("%s (%s)"), sText, pPZBase->FormatWorkspaceFileExtString());
		GetDlgItem(IDC_INCLUDEDSW)->SetWindowText(sModText);

		GetDlgItem(IDC_INCLUDEOTHERPROJ)->GetWindowText(sText);
		sModText.Format(_T("%s (%s)"), sText, pPZBase->FormatOtherProjFileExtString());
		GetDlgItem(IDC_INCLUDEOTHERPROJ)->SetWindowText(sModText);

		delete pPZBase;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

