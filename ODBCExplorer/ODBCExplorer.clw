; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COdbcFieldComboBox
LastTemplate=CComboBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ODBCExplorer.h"

ClassCount=4
Class1=CODBCExplorerApp
Class2=CODBCExplorerDlg

ResourceCount=3
Resource2=IDD_ODBCEXPLORER_DIALOG
Resource1=IDR_MAINFRAME
Class3=COdbcTableComboBox
Class4=COdbcFieldComboBox
Resource3=IDD_ODBCEXPLORER_DIALOG (English (U.S.))

[CLS:CODBCExplorerApp]
Type=0
HeaderFile=ODBCExplorer.h
ImplementationFile=ODBCExplorer.cpp
Filter=N

[CLS:CODBCExplorerDlg]
Type=0
HeaderFile=ODBCExplorerDlg.h
ImplementationFile=ODBCExplorerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TABLE_LIST



[DLG:IDD_ODBCEXPLORER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CODBCExplorerDlg

[DLG:IDD_ODBCEXPLORER_DIALOG (English (U.S.))]
Type=1
Class=CODBCExplorerDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EXECUTE_QUERY,button,1342242816
Control4=IDC_SQL_QUERY,edit,1352728708
Control5=IDC_SQL_RESULTS,SysListView32,1350664197
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHOOSE_DATABASE,button,1342242816
Control8=IDC_DATABASE,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TABLE_LIST,listbox,1352732931
Control13=IDC_DEFAULT_DATABASE,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_SQL_COLUMNS,SysListView32,1350664197
Control16=IDC_STATIC,static,1342308352
Control17=IDC_FIELD_LIST,listbox,1352732931
Control18=IDC_STATIC,static,1342177296
Control19=IDC_TABLE_COMBO,combobox,1344340226
Control20=IDC_FIELD_COMBO,combobox,1344340226

[CLS:COdbcTableComboBox]
Type=0
HeaderFile=..\shared\odbctablecombobox.h
ImplementationFile=..\shared\odbctablecombobox.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC

[CLS:COdbcFieldComboBox]
Type=0
HeaderFile=..\shared\odbcfieldcombobox.h
ImplementationFile=..\shared\odbcfieldcombobox.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC

