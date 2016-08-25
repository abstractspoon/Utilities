// ODBCExplorerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ODBCExplorer.h"
#include "ODBCExplorerDlg.h"

#include "..\shared\misc.h"

#include "..\shared\OdbcTables.h"
#include "..\shared\OdbcFields.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBCExplorerDlg dialog

CODBCExplorerDlg::CODBCExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CODBCExplorerDlg::IDD, pParent), m_bDefault(FALSE)
{
	//{{AFX_DATA_INIT(CODBCExplorerDlg)
	m_sDatabase = _T("");
	m_sQuery = _T("");
	m_sCurTable = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CODBCExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CODBCExplorerDlg)
	DDX_Control(pDX, IDC_TABLE_COMBO, m_cbTables);
	DDX_Control(pDX, IDC_FIELD_COMBO, m_cbFields);
	DDX_Control(pDX, IDC_FIELD_LIST, m_lbFields);
	DDX_Control(pDX, IDC_SQL_COLUMNS, m_lcColumns);
	DDX_Control(pDX, IDC_SQL_RESULTS, m_lcResults);
	DDX_Control(pDX, IDC_TABLE_LIST, m_lbTables);
	DDX_Text(pDX, IDC_DATABASE, m_sDatabase);
	DDX_Text(pDX, IDC_SQL_QUERY, m_sQuery);
	DDX_LBString(pDX, IDC_TABLE_LIST, m_sCurTable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CODBCExplorerDlg, CDialog)
	//{{AFX_MSG_MAP(CODBCExplorerDlg)
	ON_BN_CLICKED(IDC_CHOOSE_DATABASE, OnChooseDatabase)
	ON_BN_CLICKED(IDC_EXECUTE_QUERY, OnExecuteQuery)
	ON_BN_CLICKED(IDC_DEFAULT_DATABASE, OnDefaultDatabase)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_TABLE_LIST, OnSelchangeTableList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODBCExplorerDlg message handlers

BOOL CODBCExplorerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_lcColumns.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lcResults.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// set up Column header
	m_lcColumns.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_lcColumns.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 100);
	m_lcColumns.InsertColumn(2, _T("Precision"), LVCFMT_LEFT, 100);
	m_lcColumns.InsertColumn(3, _T("Scale"), LVCFMT_LEFT, 100);
	m_lcColumns.InsertColumn(4, _T("Nullable"), LVCFMT_LEFT, 100);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CODBCExplorerDlg::OnChooseDatabase() 
{
	VERIFY(DoOpenDatabase(FALSE));
}

BOOL CODBCExplorerDlg::DoOpenDatabase(BOOL bDefault)
{
	m_db.Close();

	CString sConnect;

	if (bDefault)
	{
		sConnect = _T("ODBC;DSN=ToDoList;DBQ=D:\\downloads\\tdl1.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;");
		m_sQuery = _T("SELECT * FROM Tasks");
	}

	m_lbTables.ResetContent();
	m_lcResults.DeleteAllItems();

	if (m_db.Open(sConnect))
	{
		m_cbTables.Initialize(&m_db);
		m_cbFields.Initialize(&m_db);
		
		m_sDatabase = m_db.GetDatabaseName();
		UpdateData(FALSE);

		CStringArray aTables;

		if (COdbcTables::GetTableNames(m_db, aTables))
		{
			int i = aTables.GetSize();
		
			while (i--)
				m_lbTables.AddString(aTables[i]);
		}

		if (m_lbTables.GetCount())
		{
			m_lbTables.SetCurSel(0);
			OnSelchangeTableList();
		}

		// do some table mappings
		CMapStringToString mapCategoryTable;
		VERIFY(CRecordsetEx::BuildFieldMapping(m_db, _T("Categories"), _T("Category_ID"), _T("CATEGORY"), mapCategoryTable));
		
		CMapIDToString mapCategoryTable2;
		VERIFY(CRecordsetEx::BuildFieldMapping(m_db, _T("Categories"), _T("Category_ID"), _T("Category"), mapCategoryTable2));
		
		return TRUE;
	}
	
	// else
	m_sDatabase.Empty();
	UpdateData(FALSE);

	return FALSE;
}


void CODBCExplorerDlg::OnExecuteQuery() 
{
	// get latest query
	UpdateData();

	CRecordsetEx results(&m_db);

	// remove results
	m_lcResults.DeleteAllItems();
	m_lcColumns.DeleteAllItems();
	
	// remove columns
	while (m_lcResults.DeleteColumn(0));

	if (results.Open(CRecordset::forwardOnly, m_sQuery) && !results.IsBOF())
	{
		// populate with result column info
		for (int i = 0; i < results.GetODBCFieldCount(); i++)
		{
			CODBCFieldInfo fi;
			results.GetODBCFieldInfo(i, fi);

			int nItem = m_lcColumns.InsertItem(m_lcColumns.GetItemCount(), fi.m_strName);
			
			m_lcColumns.SetItemText(nItem, 1, CRecordsetEx::GetSQLDataType(fi.m_nSQLType));
			m_lcColumns.SetItemText(nItem, 2, Misc::Format(fi.m_nPrecision));
			m_lcColumns.SetItemText(nItem, 3, Misc::Format(fi.m_nScale));
			m_lcColumns.SetItemText(nItem, 4, Misc::Format(fi.m_nNullability));
		}
		
		{
			// populate the result-data columns
			for (int i = 0; i < results.GetODBCFieldCount(); i++)
			{
				CODBCFieldInfo fi;
				results.GetODBCFieldInfo(i, fi);

				m_lcResults.InsertColumn(i, fi.m_strName, LVCFMT_LEFT, 100);
			}

			// populate with result data
			while(!results.IsEOF())
			{
				int nItem;

				for (int i = 0; i < results.GetODBCFieldCount(); i++)
				{
					CString sResult;

					if (results.GetFieldType(i) == SQL_TIMESTAMP)
					{
						COleDateTime date;

						if (results.GetFieldValue(i, date))
							sResult = date.Format();
					}
					else
						sResult = results.GetFieldValue(i);

					if (i == 0)
						nItem = m_lcResults.InsertItem(m_lcResults.GetItemCount(), sResult);
					else
						m_lcResults.SetItemText(nItem, i, sResult);
				}

				results.MoveNext();			
			}
		}
	}
}

void CODBCExplorerDlg::OnDefaultDatabase() 
{
	m_bDefault = DoOpenDatabase(TRUE);
	ASSERT(m_bDefault);
}

void CODBCExplorerDlg::OnSelchangeTableList() 
{
	UpdateData();

	m_lbFields.ResetContent();

	CStringArray aFields;

	if (COdbcFields::GetFieldNames(m_db, m_sCurTable, aFields))
	{
		int i = aFields.GetSize();
		
		while (i--)
			m_lbFields.AddString(aFields[i]);
	}

	m_cbFields.SetTable(m_sCurTable);
}

