// FindIncludesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindIncludes.h"
#include "FindIncludesDlg.h"

#include "..\..\ToDoList_Core\shared\folderdialog.h"
#include "..\..\ToDoList_Core\shared\FILEMISC.H"
#include "..\..\ToDoList_Core\shared\xmlfile.H"
#include "..\..\ToDoList_Core\shared\treectrlhelper.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CB_MAX_ITEMS 128
const LPCTSTR DEFDEVENV = _T("C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\Common7\\IDE\\devenv.exe");

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesDlg dialog

CFindIncludesDlg::CFindIncludesDlg(LPCTSTR szFileName, LPCTSTR szFileExt, LPCTSTR szFunction, CWnd* pParent /*=NULL*/)
   : CDialog(CFindIncludesDlg::IDD, pParent), m_bRecursive(FALSE), m_bAutoSearch(FALSE), m_sFunction(szFunction)
{
   //{{AFX_DATA_INIT(CFindIncludesDlg)
   //}}AFX_DATA_INIT
   // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   if (FileMisc::MakePath(m_sFile, NULL, NULL, szFileName, szFileExt).IsEmpty())
      m_sFile = AfxGetApp()->GetProfileString(_T("Settings"), _T("LastSymbol"));
   else
      m_bAutoSearch = TRUE;

   if (m_sFunction.IsEmpty())
      m_sFunction = AfxGetApp()->GetProfileString(_T("Settings"), _T("LastFunction"));
   
   GetCheckPath(_T("LastDevEnvPath"), m_sDevEnv, DEFDEVENV);
   GetCheckPath(_T("LastSrcPath"), m_sSrcPath);
   GetCheckPath(_T("LastXMLPath"), m_sXmlFolder);
}

CFindIncludesDlg::~CFindIncludesDlg()
{
   // cleanup map
   CString sKey;
   CStringArray* pIncludes;
   POSITION pos = m_mapDoxyID2Includes.GetStartPosition();

   while (pos)
   {
      m_mapDoxyID2Includes.GetNextAssoc(pos, sKey, pIncludes);
      delete pIncludes;
   }
}


CString& CFindIncludesDlg::GetCheckPath(LPCTSTR szIniEntry, CString& sPath, LPCTSTR szDefault)
{
   sPath = AfxGetApp()->GetProfileString(_T("Settings"), szIniEntry, szDefault);

   if (GetFileAttributes(sPath) == 0xffffffff)
      sPath.Empty();

   return sPath;
}

void CFindIncludesDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CFindIncludesDlg)
   //}}AFX_DATA_MAP
   DDX_Control(pDX, IDC_SYMLIBPATH, m_cbXMLPaths);
   DDX_Control(pDX, IDC_SYMBOL, m_cbSymbols);
   DDX_Control(pDX, IDC_RESULTS, m_tcResults);
   DDX_Control(pDX, IDC_REPOPATH, m_cbSourcePaths);
   DDX_Control(pDX, IDC_DEVENVPATH, m_cbDevEnvPaths);
   DDX_CBString(pDX, IDC_SYMLIBPATH, m_sXmlFolder);
   DDX_CBString(pDX, IDC_SYMBOL, m_sFile);
   DDX_CBString(pDX, IDC_REPOPATH, m_sSrcPath);
   DDX_CBString(pDX, IDC_DEVENVPATH, m_sDevEnv);
   DDX_Check(pDX, IDC_RECURSIVE, m_bRecursive);
   DDX_Text(pDX, IDC_FUNCTIONNAME, m_sFunction);
}

BEGIN_MESSAGE_MAP(CFindIncludesDlg, CDialog)
   //{{AFX_MSG_MAP(CFindIncludesDlg)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BROWSE, OnBrowseXMLFolder)
   ON_BN_CLICKED(IDC_SEARCH, OnSearch)
   ON_WM_CLOSE()
   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_NOTIFY(NM_DBLCLK, IDC_RESULTS, OnDblclkResults)
   ON_WM_COPYDATA()
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(WM_ISWINSYMLIBDLG, OnIsFindIncludesDlg)
   ON_BN_CLICKED(IDC_BROWSEREPO, OnBnClickedBrowseSource)
   ON_BN_CLICKED(IDC_BROWSEDEVENV, OnBnClickedBrowsedevenv)
   ON_CBN_EDITCHANGE(IDC_REPOPATH, OnCbnEditchangeRepopath)
   ON_BN_CLICKED(IDC_RECURSIVE, &CFindIncludesDlg::OnBnClickedRecursive)
   ON_CBN_SELCHANGE(IDC_SYMLIBPATH, &CFindIncludesDlg::OnCbnSelChangeXmlFolder)
   ON_CBN_EDITCHANGE(IDC_SYMLIBPATH, &CFindIncludesDlg::OnCbnEditChangeXmlFolder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindIncludesDlg message handlers

BOOL CFindIncludesDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // Set the icon for this dialog.  The framework does this automatically
   //  when the application's main window is not a dialog
   SetIcon(m_hIcon, TRUE);			// Set big icon
   SetIcon(m_hIcon, FALSE);		// Set small icon

   m_ilResults.Create(16, 16, ILC_COLOR24 | ILC_MASK, 1, 1);
   m_tcResults.SetImageList(&m_ilResults, TVSIL_NORMAL);

   CBitmap bmp;
   bmp.LoadBitmap(IDB_FOLDER);
   m_ilResults.Add(&bmp, 255);
   ASSERT(m_ilResults.GetImageCount() == 3);

   // restore position
   int nTop = AfxGetApp()->GetProfileInt(_T("Settings"), _T("WindowTop"), -1);
   int nLeft = AfxGetApp()->GetProfileInt(_T("Settings"), _T("WindowLeft"), -1);

   if ((nTop > 0) && (nLeft > 0))
   {
      CRect rWindow;
      GetWindowRect(rWindow);

      rWindow.OffsetRect(nLeft - rWindow.left, nTop - rWindow.top);
      MoveWindow(rWindow);
   }
   
   //---------------------------------------------------------------------
   int nCount = AfxGetApp()->GetProfileInt(_T("Settings"), _T("XMLPathCount"), 0);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("XMLPath%d"), nCount);
      sPath = AfxGetApp()->GetProfileString(_T("Settings"), sItem);

      AddItemToCombo(sPath, m_cbXMLPaths, TRUE);
   }

   AddItemToCombo(m_sXmlFolder, m_cbXMLPaths, TRUE);

   //---------------------------------------------------------------------
   nCount = AfxGetApp()->GetProfileInt(_T("Settings"), _T("DevEnvCount"), 0);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("DevEnvPath%d"), nCount);
      sPath = AfxGetApp()->GetProfileString(_T("Settings"), sItem);

      AddItemToCombo(sPath, m_cbDevEnvPaths, TRUE);
   }

   AddItemToCombo(m_sDevEnv, m_cbDevEnvPaths, TRUE);

   //---------------------------------------------------------------------
   nCount = AfxGetApp()->GetProfileInt(_T("Settings"), _T("SrcPathCount"), 0);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("SrcPath%d"), nCount);
      sPath = AfxGetApp()->GetProfileString(_T("Settings"), sItem);

      AddItemToCombo(sPath, m_cbSourcePaths, TRUE);
   }

   AddItemToCombo(m_sSrcPath, m_cbSourcePaths, TRUE);

   //---------------------------------------------------------------------
   nCount = AfxGetApp()->GetProfileInt(_T("Settings"), _T("SymbolCount"), 0);
   nCount = min(CB_MAX_ITEMS, nCount);

   while (nCount--)
   {
      CString sItem, sSymbol;
      sItem.Format(_T("Symbol%d"), nCount);
      sSymbol = AfxGetApp()->GetProfileString(_T("Settings"), sItem);

      AddItemToCombo(sSymbol, m_cbSymbols, FALSE);
   }
   //---------------------------------------------------------------------

   if (m_bAutoSearch && !m_sXmlFolder.IsEmpty() && !m_sFile.IsEmpty())
   {
      m_bAutoSearch = FALSE;
      PostMessage(WM_COMMAND, IDC_SEARCH, 0);
   }

   return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFindIncludesDlg::OnPaint() 
{
   if (IsIconic())
   {
      CPaintDC dc(this); // device context for painting

      SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

      // Center icon in client rectangle
      int cxIcon = GetSystemMetrics(SM_CXICON);
      int cyIcon = GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x = (rect.Width() - cxIcon + 1) / 2;
      int y = (rect.Height() - cyIcon + 1) / 2;

      // Draw the icon
      dc.DrawIcon(x, y, m_hIcon);
   }
   else
   {
      CDialog::OnPaint();
   }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFindIncludesDlg::OnQueryDragIcon()
{
   return (HCURSOR) m_hIcon;
}

void CFindIncludesDlg::OnBrowseXMLFolder() 
{
   // open the file dialog for sym_lib
   CFolderDialog dialog(_T("Browse for XML folder"), m_sXmlFolder, this);

   if (dialog.DoModal() == IDOK)
   {
      m_sXmlFolder = dialog.GetFolderPath();
      FileMisc::TerminatePath(m_sXmlFolder, FALSE);

      AddItemToCombo(m_sXmlFolder, m_cbXMLPaths, TRUE);

      UpdateData(FALSE);
   }
}

void CFindIncludesDlg::OnOK()
{
   OnSearch();
}

void CFindIncludesDlg::AddItemToCombo(LPCTSTR szItem, CComboBox& combo, BOOL bPath)
{
   if (!szItem || !(*szItem) || (bPath && GetFileAttributes(szItem) == 0xffffffff))
      return;

   if (combo.FindStringExact(-1, szItem) == CB_ERR)
      combo.InsertString(0, szItem);
}

void CFindIncludesDlg::OnSearch() 
{
   UpdateData();

   DoSearch();
};

BOOL CFindIncludesDlg::LoadDoxyIndex()
{
   // only load if map is empty
   if (!m_mapFile2IncludeItem.IsEmpty())
      return TRUE;

   FileMisc::SetCwd(m_sXmlFolder);

   CXmlFile file(_T("doxygenindex")/*, CP_UTF8*/);

   if (!file.Load(_T("index.xml")))
   {
      AfxMessageBox(_T("Failed to Load Index"));
      return FALSE;
   }

   m_mapFile2IncludeItem.RemoveAll();

   // build file->DoxyID map
   const CXmlItem* pXIDef = file.GetItem(_T("compound"));

   while (pXIDef)
   {
      if (pXIDef->GetItemValue(_T("kind")) == _T("file"))
      {
         CString sFilename = pXIDef->GetItemValue(_T("name"));

         if (!sFilename.IsEmpty())
         {
            CString sDoxyID = pXIDef->GetItemValue(_T("refid"));

            if (!sDoxyID.IsEmpty())
            {
               INCLUDEFILEITEM fi(sFilename, sDoxyID);

               m_mapFile2IncludeItem[sFilename.MakeLower()] = fi;
            }
         }
      }

      // next
      pXIDef = pXIDef->GetSibling();
   }

   return m_mapFile2IncludeItem.GetCount();
}

void CFindIncludesDlg::DoSearch() 
{
   if (m_sFile.IsEmpty())
      return;

   CWaitCursor cursor;
   LoadDoxyIndex();

   CString sDoxyID = GetDoxyID(m_sFile, TRUE);

   if (sDoxyID.IsEmpty())
      return;

   // check existence of repo and symlib
   if (m_sDevEnv.IsEmpty() || m_sXmlFolder.IsEmpty() || m_sSrcPath.IsEmpty())
   {
      AfxMessageBox(_T("You need to supply paths for Visual Studio, the XML folder and the source folder you are working in."));
      return;
   }

   m_tcResults.DeleteAllItems();
   m_tcResults.UpdateWindow();

   // prevent circular dependencies
   CMap<CString, LPCTSTR, BOOL, BOOL&> mapVisited;
   INCLUDEFILEITEM fi(m_sFile, sDoxyID);

   DoSearch(fi, NULL, mapVisited);

   CTreeCtrlHelper(m_tcResults).ExpandAll();

   // add to combo, or move to top
   int nIndex = m_cbSymbols.FindStringExact(-1, m_sFile);

   if (nIndex != CB_ERR)
      m_cbSymbols.DeleteString(nIndex);

   m_cbSymbols.InsertString(0, m_sFile);
   m_cbSymbols.SelectString(0, m_sFile);
}

void CFindIncludesDlg::DoSearch(INCLUDEFILEITEM& fi, HTREEITEM htiParent, CMap<CString, LPCTSTR, BOOL, BOOL&>& mapVisited) 
{
   ASSERT(!fi.sFile.IsEmpty() && !fi.sDoxyID.IsEmpty());

   // have we been here before?
   if (m_bRecursive)
   {
      BOOL bFound = FALSE;

      if (mapVisited.Lookup(fi.sDoxyID, bFound))
      {
         ASSERT(bFound);
         return;
      }

      mapVisited[fi.sDoxyID] = TRUE;
   }
   
   // get or create the include list
   CStringArray* pIncludes = NULL;
   
   if (!m_mapDoxyID2Includes.Lookup(fi.sDoxyID, pIncludes))
   {
      FileMisc::SetCwd(m_sXmlFolder);

      CXmlFile file(_T("doxygen")/*, CP_UTF8*/);

      if (!file.Load(fi.sDoxyID + _T(".xml")))
         return;

      const CXmlItem* pXIDef = file.GetItem(_T("compounddef"));

      if (pXIDef)
      {
         // fill in the full path name
         if (fi.sFullPath.IsEmpty())
         {
            fi.sFullPath = pXIDef->GetItemValue(_T("location"), _T("file"));
            m_mapFile2IncludeItem[fi.sFile] = fi;
         }

         // get the 'included by' list
         const CXmlItem* pXIInc = pXIDef->GetItem(_T("includedby"));

         if (pXIInc)
         {
            pIncludes = new CStringArray;
            m_mapDoxyID2Includes[fi.sDoxyID] = pIncludes;

            while (pXIInc)
            {
               CString sFile = pXIInc->GetValue();
               ASSERT(!sFile.IsEmpty());

               sFile.Replace('/', '\\');
               pIncludes->Add(sFile);
               
               pXIInc = pXIInc->GetSibling();
            }
         }
      }
   }

   // add results to list
   if (pIncludes)
   {
      int nNumInclude = pIncludes->GetSize();
      CString sCurFolder;
      HTREEITEM htiCurParent = NULL;

      HTREEITEM htiGrandParent = m_tcResults.GetParentItem(htiParent);
      CString sGrandParent = m_tcResults.GetItemText(htiGrandParent);

      for (int nIncl = 0; nIncl < nNumInclude; nIncl++)
      {
         CString sFilename = pIncludes->GetAt(nIncl);
         HTREEITEM hti = NULL;

         CString sFolder = FileMisc::GetFolderFromFilePath(sFilename);
         CString sFile = FileMisc::GetFileNameFromPath(sFilename);
         sFile.Replace('/', '\\');

         CString sExt = FileMisc::GetExtension(sFilename);
         sExt.MakeLower();

         BOOL bHeader = (sExt == _T(".h"));
         BOOL bSource = (sExt == _T(".cpp"));
         int nImage = (bHeader ? 1 : (bSource ? 2 : -1));

         if (!sFolder.IsEmpty())
         {
            // if the folder is the same as grandparent just add direct to grandparent
            if (sFolder != sCurFolder)
            {
               if (sFolder == sGrandParent)
                  htiCurParent = htiGrandParent;
               else
                  htiCurParent = m_tcResults.InsertItem(sFolder, 0, 0, htiParent);

               sCurFolder = sFolder;
            }
            
            hti = m_tcResults.InsertItem(sFile, nImage, nImage, htiCurParent);
         }
         else
         {
            sCurFolder.Empty();
            hti = m_tcResults.InsertItem(sFile, nImage, nImage, htiParent);
         }

         m_tcResults.UpdateWindow();
         
         // children?
         if (m_bRecursive)
         {
            INCLUDEFILEITEM fiRecurse;

            if (m_mapFile2IncludeItem.Lookup(sFile, fiRecurse))
               DoSearch(fiRecurse, hti, mapVisited);
         }
      }
   }
}

void CFindIncludesDlg::OnClose() 
{
#ifdef _DEBUG
      CDialog::OnOK();
#else
   // only close if we are minimized
   if (IsIconic())
   {
      ShowWindow(SW_RESTORE);
      ShowWindow(SW_HIDE);
      CDialog::OnOK();
   }
   else
      ShowWindow(SW_MINIMIZE);
#endif
}

void CFindIncludesDlg::OnDestroy() 
{
   CDialog::OnDestroy();

   // save position
   CRect rWindow;
   GetWindowRect(rWindow);

   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("WindowTop"), rWindow.top);
   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("WindowLeft"), rWindow.left);

   //------------------------------------------------------
   int nCount = min(CB_MAX_ITEMS, m_cbXMLPaths.GetCount());
   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("XMLPathCount"), nCount);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("XMLPath%d"), nCount);
      m_cbXMLPaths.GetLBText(nCount, sPath);
      AfxGetApp()->WriteProfileString(_T("Settings"), sItem, sPath);
   }

   // save last item too
   AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastXMLPath"), m_sXmlFolder);

   //------------------------------------------------------
   nCount = min(CB_MAX_ITEMS, m_cbDevEnvPaths.GetCount());
   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DevEnvCount"), nCount);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("DevEnvPath%d"), nCount);
      m_cbDevEnvPaths.GetLBText(nCount, sPath);
      AfxGetApp()->WriteProfileString(_T("Settings"), sItem, sPath);
   }

   // save last item too
   AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastDevEnvPath"), m_sDevEnv);

   //------------------------------------------------------
   nCount = min(CB_MAX_ITEMS, m_cbSourcePaths.GetCount());
   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SrcPathCount"), nCount);

   while (nCount--)
   {
      CString sItem, sPath;
      sItem.Format(_T("SrcPath%d"), nCount);
      m_cbSourcePaths.GetLBText(nCount, sPath);
      AfxGetApp()->WriteProfileString(_T("Settings"), sItem, sPath);
   }

   // save last item too
   AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastSrcPath"), m_sSrcPath);

   //------------------------------------------------------
   nCount = m_cbSymbols.GetCount();
   AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SymbolCount"), nCount);

   while (nCount--)
   {
      CString sItem, sSymbol;
      sItem.Format(_T("Symbol%d"), nCount);
      m_cbSymbols.GetLBText(nCount, sSymbol);
      AfxGetApp()->WriteProfileString(_T("Settings"), sItem, sSymbol);
   }

   // save last item too
   AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastSymbol"), m_sFile);

   //------------------------------------------------------
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Recursive"), m_bRecursive);
    AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastFunction"), m_sFunction);
}

void CFindIncludesDlg::OnSize(UINT nType, int cx, int cy) 
{
   CDialog::OnSize(nType, cx, cy);

   if (m_tcResults.GetSafeHwnd())
   {
      CRect rResults;

      m_tcResults.GetWindowRect(rResults);
      ScreenToClient(rResults);

      rResults.right = cx - 10;
      rResults.bottom = cy - 10;

      m_tcResults.MoveWindow(rResults);
   }
}

void CFindIncludesDlg::OnDblclkResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
   if (m_tcResults.GetSelectedCount() > 0)
   {
      HTREEITEM hti = m_tcResults.GetSelectedItem();

      if (ShowResult(hti) == SE_ERR_NOASSOC)
         AfxMessageBox(_T("The selected file has no associated application"));
   }

   *pResult = 0;
}

CString CFindIncludesDlg::GetResultFilePath(HTREEITEM hti)
{
   if (hti)
   {
      CString sPath = m_tcResults.GetItemText(hti);

      INCLUDEFILEITEM fi;

      if (!m_mapFile2IncludeItem.Lookup(sPath, fi))
      {
         fi.sFile = sPath;
         fi.sDoxyID = GetDoxyID(sPath);

         FileMisc::SetCwd(m_sXmlFolder);

         CXmlFile file(_T("doxygen")/*, CP_UTF8*/);

         if (file.Load(fi.sDoxyID + _T(".xml")))
         {
            const CXmlItem* pXIDef = file.GetItem(_T("compounddef"));

            if (pXIDef)
            {
               fi.sFullPath = pXIDef->GetItemValue(_T("location"), _T("file"));
               ASSERT(!fi.sFullPath.IsEmpty());
            }
         }

         // always add so that we only load the 
         // xml file once for each file
         m_mapFile2IncludeItem[fi.sFile] = fi;
      }

      return fi.sFullPath;
   }

   // else
   return _T("");
}

int CFindIncludesDlg::ShowResult(HTREEITEM hti)
{
   CString sFilePath = GetResultFilePath(hti);
   
   if (!sFilePath.IsEmpty())
   {
      ASSERT (GetFileAttributes(sFilePath) != 0xffffffff);

      if (GetFileAttributes(sFilePath) != 0xffffffff)
      {
         CString sEditFile;
         sEditFile.Format(_T("/Edit \"%s\""), sFilePath);

         return (int)ShellExecute(*this, NULL, m_sDevEnv, sEditFile, NULL, SW_SHOWNORMAL);
      }
   }

   // else
   return 32; // pretend all is well
}

BOOL CFindIncludesDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
   switch (pCopyDataStruct->dwData)
   {
   case WSL_NEWSYMBOL:
      {
         ASSERT (pCopyDataStruct->cbData == sizeof (FINDINCLUDESCOPYDATA));

         FINDINCLUDESCOPYDATA* pWSI = (FINDINCLUDESCOPYDATA*)(pCopyDataStruct->lpData);

         // update UI
         FileMisc::MakePath(m_sFile, NULL, NULL, pWSI->szFileName, pWSI->szFileExt);
         m_sFunction = pWSI->szFunction;

         UpdateData(FALSE);
         DoSearch();
      }
      break;
   }

   return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

CString CFindIncludesDlg::GetDoxyID(const CString& sPath, BOOL bWantHeader) const
{
   CString sFilename(FileMisc::GetFileNameFromPath(sPath));
   sFilename.MakeLower();

   if (bWantHeader && !FileMisc::HasExtension(sFilename, _T(".h")))
      FileMisc::ReplaceExtension(sFilename, _T(".h"));

   INCLUDEFILEITEM fi;

   if (m_mapFile2IncludeItem.Lookup(sFilename, fi))
   {
      ASSERT(!fi.sDoxyID.IsEmpty());
      return fi.sDoxyID;
   }
   
   // else
   return _T("");
}

void CFindIncludesDlg::OnBnClickedBrowseSource()
{
   CFolderDialog dialog(_T("Browse for Source folder"), m_sSrcPath, this);

   if (dialog.DoModal() == IDOK)
   {
      m_sSrcPath = dialog.GetFolderPath();
      AddItemToCombo(m_sSrcPath, m_cbSourcePaths, TRUE);

      UpdateData(FALSE);
   }
}

void CFindIncludesDlg::OnBnClickedBrowsedevenv()
{
   CFileDialog dialog(TRUE, NULL, m_sDevEnv, 0, _T("Visual Studio|DevEnv.exe||"), this);

   if (dialog.DoModal() == IDOK)
   {
      m_sDevEnv = dialog.GetPathName();
      AddItemToCombo(m_sDevEnv, m_cbDevEnvPaths, TRUE);

      UpdateData(FALSE);
   }
}

void CFindIncludesDlg::OnCbnEditchangeRepopath()
{
   UpdateData();

   AddItemToCombo(m_sSrcPath, m_cbSourcePaths, TRUE);
}


void CFindIncludesDlg::OnBnClickedRecursive()
{
   UpdateData();

   DoSearch();
}

void CFindIncludesDlg::OnCbnSelChangeXmlFolder()
{
   CString sPrevFolder = m_sXmlFolder;
   int nSel = m_cbXMLPaths.GetCurSel();

   if (nSel != CB_ERR)
   {
      m_cbXMLPaths.GetLBText(nSel, m_sXmlFolder);

      if (m_sXmlFolder.CompareNoCase(sPrevFolder) != 0)
         m_mapFile2IncludeItem.RemoveAll();
   }

}

void CFindIncludesDlg::OnCbnEditChangeXmlFolder()
{
   CString sPrevFolder = m_sXmlFolder;
   UpdateData();

   if (m_sXmlFolder.CompareNoCase(sPrevFolder) != 0)
      m_mapFile2IncludeItem.RemoveAll();
}
