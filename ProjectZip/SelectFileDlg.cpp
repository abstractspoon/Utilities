// SelectFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SelectFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectFileDlg dialog

#define IDC_FILELIST                    1005

const LPCTSTR DIALOGITEMS = 
_T("   \
    DEFPUSHBUTTON   \"OK\",1,83,109,50,14 \
    PUSHBUTTON      \"Cancel\",2,140,109,50,14 \
    LTEXT           \"More than one project file was found in the zip file.\n\nPlease select one of the files to open:\", \
                    0xffff,7,7,183,24 \
    LISTBOX         1005,7,35,183,66,LBS_SORT | LBS_NOINTEGRALHEIGHT | \
                    WS_VSCROLL | WS_TABSTOP \
");

CSelectFileDlg::CSelectFileDlg(CStringArray& aFiles, CWnd* pParent /*=NULL*/)
	: CRuntimeDlg()
{
	//{{AFX_DATA_INIT(CSelectFileDlg)
	m_sSelection = _T("");
	//}}AFX_DATA_INIT

	AddRCControls(DIALOGITEMS);

	m_aFiles.Copy(aFiles);
}


void CSelectFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CRuntimeDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectFileDlg)
	DDX_Control(pDX, IDC_FILELIST, m_lbFiles);
	DDX_LBString(pDX, IDC_FILELIST, m_sSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectFileDlg, CRuntimeDlg)
	//{{AFX_MSG_MAP(CSelectFileDlg)
	ON_LBN_SELCHANGE(IDC_FILELIST, OnSelchangeFilelist)
	ON_LBN_DBLCLK(IDC_FILELIST, OnDblclkFilelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectFileDlg message handlers

int CSelectFileDlg::DoModal()
{
	return CRuntimeDlg::DoModal(_T("ProjectZip - Open Project File"));
}

void CSelectFileDlg::OnSelchangeFilelist() 
{
	UpdateData();

	GetDlgItem(IDOK)->EnableWindow(m_lbFiles.GetCurSel() != LB_ERR);
}

BOOL CSelectFileDlg::OnInitDialog() 
{
	CRuntimeDlg::OnInitDialog();
	
	// fill list
	int nFile = m_aFiles.GetSize();

	if (!nFile)
		EndDialog(-1);
	else
	{
		while (nFile--)
			m_lbFiles.AddString(m_aFiles[nFile]);

		m_lbFiles.SetSel(0);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectFileDlg::OnDblclkFilelist() 
{
	UpdateData();

	if (m_lbFiles.GetCurSel() != LB_ERR)
		EndDialog(IDOK);
}
