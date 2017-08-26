// GitHubToDokuWikiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GitHubToDokuWiki.h"
#include "GitHubToDokuWikiDlg.h"

#include "..\..\ToDoList_Core\Shared\FileMisc.h"
#include "..\..\ToDoList_Core\Shared\Misc.h"
#include "..\..\ToDoList_Core\Shared\EnBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGitHubToDokuWikiDlg dialog

CGitHubToDokuWikiDlg::CGitHubToDokuWikiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGitHubToDokuWikiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGitHubToDokuWikiDlg)
	//}}AFX_DATA_INIT
	m_sGitHubFolder = AfxGetApp()->GetProfileString(_T("Settings"), _T("GitHubFolder"));
	m_sDokuwikiFolder = AfxGetApp()->GetProfileString(_T("Settings"), _T("DokuwikiFolder"));
	m_sSidebarPath = AfxGetApp()->GetProfileString(_T("Settings"), _T("SidebarPath"));

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGitHubToDokuWikiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGitHubToDokuWikiDlg)
	DDX_Text(pDX, IDC_GITHUBFOLDER, m_sGitHubFolder);
	DDX_Text(pDX, IDC_DOKUWKIFOLDER, m_sDokuwikiFolder);
	DDX_Text(pDX, IDC_SIDEBAR, m_sSidebarPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGitHubToDokuWikiDlg, CDialog)
	//{{AFX_MSG_MAP(CGitHubToDokuWikiDlg)
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGitHubToDokuWikiDlg message handlers

BOOL CGitHubToDokuWikiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGitHubToDokuWikiDlg::OnConvert() 
{
	UpdateData();

	CWaitCursor cursor;
	FileMisc::DeleteFolderContents(m_sDokuwikiFolder, FMDF_SUBFOLDERS);

	BuildTitleMap();
	
	CStringArray aFiles;
	int nNumFiles = FileMisc::FindFiles(m_sGitHubFolder, aFiles, TRUE, _T("*.*"));

	for (int nFile = 0; nFile < nNumFiles; nFile++)
	{
		CString sSrcFile = aFiles[nFile];

		if (sSrcFile.Find(_T(".git")) != -1)
			continue;

		ProcessSrcFile(sSrcFile);
	}
}

void CGitHubToDokuWikiDlg::BuildTitleMap()
{
	m_mapTitles.RemoveAll();
	
	CStringArray aLines;
	int nNumLines = FileMisc::LoadFile(m_sSidebarPath, aLines);
		
	for (int nLine = 0; nLine < nNumLines; nLine++)
	{
		const CString& sLine = aLines[nLine];
		
		int nStart = sLine.Find(_T("[["));
		int nEnd = sLine.Find(_T("]]"));

		if ((nStart != -1) && (nEnd != -1))
		{
			CString sLink(sLine.Mid((nStart + 2), (nEnd - (nStart + 2)))), sTitle;
			VERIFY (Misc::Split(sLink, sTitle, '|'));

			m_mapTitles[sLink] = sTitle;
		}
	}
}

CString CGitHubToDokuWikiDlg::GetDestFilePath(const CString& sSrcFile) const
{
	CString sDestFile;
	
	if (Misc::ToLower(FileMisc::GetExtension(sSrcFile)) == _T(".md"))
	{
		FileMisc::MakePath(sDestFile, NULL, m_sDokuwikiFolder, FileMisc::GetFileNameFromPath(sSrcFile, FALSE), _T(".txt"));
	}
	else
	{
		sDestFile = FileMisc::GetRelativePath(sSrcFile, m_sGitHubFolder, FALSE);
		VERIFY(FileMisc::MakeFullPath(sDestFile, m_sDokuwikiFolder));
	}
	
	Misc::MakeLower(sDestFile);
	
	sDestFile.Replace(_T("-page."), _T("-dialog."));
	sDestFile.Replace(_T("-preferences."), _T("-prefs."));

	return sDestFile;
}

void CGitHubToDokuWikiDlg::ProcessSrcFile(const CString& sSrcFile) const
{
	CString sDestFile(GetDestFilePath(sSrcFile));
	VERIFY(FileMisc::CreateFolderFromFilePath(sDestFile));

	if (Misc::ToLower(FileMisc::GetExtension(sSrcFile)) == _T(".md"))
	{
		CStringArray aLines;
		int nNumLines = FileMisc::LoadFile(sSrcFile, aLines);

		for (int nLine = 0; nLine < nNumLines; nLine++)
		{
			CString& sLine = aLines[nLine];

			ProcessHeadings(sLine);
			ProcessImageLinks(sLine);
			ProcessPageLinks(sLine);
			ProcessHorzLines(sLine);
			ProcessLists(sLine);
			ProcessDivs(sLine);
			ProcessIcons(sLine);
			ProcessMonospacing(sLine);
			ProcessTable(sLine);
			ProcessMiscHtml(sLine);
			ProcessForwardSlashes(sLine);
		}

		FixupCmdLineSwitches(aLines);
		AddTitle(sDestFile, aLines);
			
		CString sDestContents = FormatLines(aLines);
		VERIFY(FileMisc::SaveFile(sDestFile, sDestContents, SFEF_UTF8WITHOUTBOM));
	}
	else
	{
		VERIFY(FileMisc::CopyFile(sSrcFile, sDestFile, TRUE));
	}
}

void CGitHubToDokuWikiDlg::AddTitle(const CString& sDestFile, CStringArray& aLines) const
{
	CString sFileName(FileMisc::GetFileNameFromPath(sDestFile, FALSE));
	Misc::MakeLower(sFileName);

	CString sTitle;

	if (m_mapTitles.Lookup(sFileName, sTitle))
	{
		CString sFirstLine(aLines[0]);
		sFirstLine.TrimLeft();
		
		if (sFirstLine.Find(_T("==")) == 0)
			aLines.RemoveAt(0);

		sFirstLine.Format(_T("====== %s ======"), sTitle);

		aLines.InsertAt(0, sFirstLine);
	}
}

void CGitHubToDokuWikiDlg::ProcessImageLinks(CString& sLine) const
{
	// fixup paths
	sLine.Replace(_T("wiki/images/"), _T("images/"));

	// Process Wiki images
	int nStart = sLine.Find(_T("!["));

	while (nStart != -1)
	{
		CString sImage;
		int nMid = sLine.Find(_T("]("), (nStart + 2));

		if (nMid != -1)
		{
			int nEnd = sLine.Find(_T(")"), (nMid + 2));

			if (nEnd != -1)
			{
				sImage = sLine.Mid((nMid + 2), (nEnd - (nMid + 2)));
				sImage = FormatImageLink(sImage);

				if (!sImage.IsEmpty())
					sLine = sLine.Left(nStart) + sImage + sLine.Mid(nEnd + 1);
			}
		}

		if (sImage.IsEmpty())
			nStart = sLine.Find(_T("!["), (nStart + 2));
		else
			nStart = sLine.Find(_T("!["), (nStart + sImage.GetLength()));
	}

	// process HTML images
	// <img alt="Select display language" src="./images/screenshots/langlist.png" align="right" />
	nStart = sLine.Find(_T("<img "));
	
	while (nStart != -1)
	{
		CString sImage;
		int nEnd = sLine.Find(_T("/>"), nStart + 5);

		if (nEnd != -1)
		{
			int nSrc = sLine.Find(_T("src"), nStart + 5);

			if ((nSrc != -1) && (nSrc < nEnd))
			{
				int nQuote = sLine.Find('\"', nSrc);

				if ((nQuote != -1) && (nQuote < nEnd))
				{
					int nQuote2 = sLine.Find('\"', (nQuote + 1));
					
					if ((nQuote2 != -1) && (nQuote2 < nEnd))
					{
						CString sImage = sLine.Mid((nQuote + 1), (nQuote2 - (nQuote + 1)));
						sImage = FormatImageLink(sImage);
						
						if (!sImage.IsEmpty())
							sLine = sLine.Left(nStart) + sImage + sLine.Mid(nEnd + 2);
					}
				}
			}
		}

		nStart = sLine.Find(_T("<img "), 5);
	}

}

CString CGitHubToDokuWikiDlg::FormatImageLink(const CString& sImage) const
{
	CString sText(sImage);
	
	if (CEnBitmap::IsSupportedImageFile(sText))
	{
		Misc::MakeLower(sText);

		sText.TrimLeft(_T("./"));
		sText.Replace('/', ':');
		sText = (_T("{{") + sText + _T("}}"));
	}

	return sText;
}

void CGitHubToDokuWikiDlg::ProcessPageLinks(CString& sLine) const
{
	int nStart = sLine.Find(_T("["));
	
	while (nStart != -1)
	{
		CString sText, sPage;
		int nMid = sLine.Find(_T("]("), (nStart + 1)), nEnd = -1;
		
		if (nMid != -1)
		{
			nEnd = sLine.Find(_T(")"), (nMid + 2));
			
			if (nEnd != -1)
			{
				sText = sLine.Mid((nStart + 1), (nMid - (nStart + 1)));
				sPage = sLine.Mid((nMid + 2), (nEnd - (nMid + 2)));
				Misc::MakeLower(sPage);
			}
		}
		else
		{
			nEnd = sLine.Find(_T("]"), (nStart + 1));
			
			if (nEnd != -1)
			{
				sText = sLine.Mid((nStart + 1), (nEnd - (nStart + 1)));
				sPage = sText;
				Misc::MakeLower(sPage);
			}
		}

		if (nEnd != -1)
		{
			ASSERT(!sText.IsEmpty());

			CString sLink = FormatPageLink(sPage, sText);

			// if this line is also a heading then remove the link
			// and insert it after
			if ((sLine.Find(_T("==")) == 0) && !sPage.IsEmpty())
			{
				sLine = sLine.Left(nStart) + sText + sLine.Mid(nEnd + 1);
				sLine += _T("\r\n");
				sLine += sLink;
			}
			else
			{
				sLine = sLine.Left(nStart) + sLink + sLine.Mid(nEnd + 1);
			}

			nStart = sLine.Find(_T("["), (nStart + sLink.GetLength()));
		}
		else
		{
			nStart = sLine.Find(_T("["), (nStart + 1));
		}
	}

	// process HTML links
	// <a href=”#addingvalues“>Adding Values</a>
	nStart = sLine.Find(_T("<a "));
	
	while (nStart != -1)
	{
		int nEnd = sLine.Find(_T("</a>"), nStart + 3);
		
		if (nEnd != -1)
		{
			int nSrc = sLine.Find(_T("href"), nStart + 3);
			
			if ((nSrc != -1) && (nSrc < nEnd))
			{
				int nQuote = sLine.Find('\"', nSrc);
				
				if ((nQuote != -1) && (nQuote < nEnd))
				{
					int nQuote2 = sLine.Find('\"', (nQuote + 1));
					
					if ((nQuote2 != -1) && (nQuote2 < nEnd))
					{
						CString sPage = sLine.Mid((nQuote + 1), (nQuote2 - (nQuote + 1)));
						Misc::ToLower(sPage);

						int nStartText = sLine.Find(_T(">"), (nQuote2 + 1));

						if ((nStartText != -1) && (nStartText < nEnd))
						{
							CString sText = sLine.Mid((nStartText + 1), (nEnd - (nStartText + 1)));

							if (!sText.IsEmpty())
							{
								CString sLink = FormatPageLink(sPage, sText);

								sLine = sLine.Left(nStart) + sLink + sLine.Mid(nEnd + 4);
							}

						}
						
					}
				}
			}

			nStart = sLine.Find(_T("<a "), nEnd);
		}
		else
		{
			nStart = sLine.Find(_T("<a "), nStart + 3);
		}
	}
}

CString CGitHubToDokuWikiDlg::FormatPageLink(const CString& sPage, const CString& sText) const
{
	CString sLink, sModPage(sPage);

	sModPage.Replace(_T("-page"), _T("-dialog"));
	sModPage.Replace(_T("-preferences"), _T("-prefs"));

	if (sPage.IsEmpty())
	{
		sLink = sText;
	}
	else
	{
		int nHash = sPage.Find('#');
		
		if (nHash != -1)
		{
			CString sHash = Misc::ToLower(sText);
			sHash.Replace(' ', '_');
			
			sModPage = (sModPage.Left(nHash + 1) + sHash);
		}
		
		sModPage.TrimLeft(_T("./"));
		sLink.Format(_T("[[%s|%s]]"), sModPage, sText);
	}

	return sLink;
}

void CGitHubToDokuWikiDlg::ProcessTable(CString& sLine) const
{
	// Header items
	if (sLine.Replace(_T("</b></td></tr>"), _T("^")))
	{
		int a= 5;
	}
	sLine.Replace(_T("<td><b>"), _T("^"));
	
	// Data items
	sLine.Replace(_T("</tr>"), _T("|"));
	sLine.Replace(_T("<td>"), _T("|"));
	
	// Redundant items
	sLine.Replace(_T("<table>"), _T(""));
	sLine.Replace(_T("</table>"), _T(""));
	sLine.Replace(_T("<tr>"), _T(""));
	sLine.Replace(_T("</tr>"), _T(""));
	sLine.Replace(_T("</b></td>"), _T(""));
	sLine.Replace(_T("<td>"), _T(""));
	sLine.Replace(_T("</td>"), _T(""));
	sLine.Replace(_T("<th>"), _T(""));
	sLine.Replace(_T("</th>"), _T(""));
	sLine.Replace(_T("<tbody>"), _T(""));
	sLine.Replace(_T("</tbody>"), _T(""));
}

void CGitHubToDokuWikiDlg::ProcessMiscHtml(CString& sLine) const
{
	sLine.Replace(_T("&lt;"), _T(" <"));
	sLine.Replace(_T("&gt;"), _T("> "));
	sLine.Replace(_T("&nbsp;"), _T(" "));
	sLine.Replace(_T("<b>"), _T("**"));
	sLine.Replace(_T("</b>"), _T("**"));
	sLine.Replace(_T("<br/>"), _T(""));
	sLine.Replace(_T("<br>"), _T(""));
	sLine.Replace(_T("<u>"), _T("__"));
	sLine.Replace(_T("</u>"), _T("__"));
	sLine.Replace(_T(""), _T(""));
	sLine.Replace(_T(""), _T(""));
}

void CGitHubToDokuWikiDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("GitHubFolder"), m_sGitHubFolder);
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("DokuwikiFolder"), m_sDokuwikiFolder);
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("SidebarPath"), m_sSidebarPath);
}

CString CGitHubToDokuWikiDlg::FormatLines(const CStringArray& aLines) const
{
	CString sText;
	int nCount = aLines.GetSize();
	
	for (int nItem = 0; nItem < nCount; nItem++)
	{
		sText += aLines[nItem];
		sText += _T("\r\n");
	}
	
	return sText;
}

void CGitHubToDokuWikiDlg::ProcessHeadings(CString& sLine) const
{
	for (int i = 6; i > 0; i--)
	{
		CString sHeading('#', i);

		if (sLine.Find(sHeading) == 0)
		{
			CString sEquivHeading = GetEquivHeading(sHeading);

			if (sLine.Find(sHeading, sHeading.GetLength()) == -1)
			{
				sLine = (sEquivHeading + sLine.Mid(sHeading.GetLength()) + sEquivHeading);
			}
			else
			{
				sLine.Replace(sHeading, sEquivHeading);
			}
		}
	}
}

CString CGitHubToDokuWikiDlg::GetEquivHeading(const CString& sGHHeading) const
{
	if ((sGHHeading == _T("######")) || (sGHHeading == _T("#####")))
	{
		return _T("==");
	}
	else if (sGHHeading == _T("####"))
	{
		return _T("===");
	}
	else if (sGHHeading == _T("###"))
	{
		return _T("====");
	}
	else if (sGHHeading == _T("##"))
	{
		return _T("=====");
	}
	else if (sGHHeading == _T("#"))
	{
		return _T("======");
	}

	// else 
	return _T("");
}

void CGitHubToDokuWikiDlg::ProcessHorzLines(CString& sLine) const
{
	sLine.Replace(_T("<hr/>"), _T("----"));
	sLine.Replace(_T("<hr>"), _T("----"));
}

void CGitHubToDokuWikiDlg::ProcessLists(CString& sLine) const
{
	CString sTrimmed(sLine);
	sTrimmed.TrimLeft();

	if (sTrimmed.Find(_T("* ")) == 0)
	{
		int nStar = sLine.Find(_T("* "));
		sLine = CString(' ', nStar) + _T("  * ") + sLine.Mid(nStar + 2);
	}
	else if (sTrimmed.Find(_T("- ")) == 0)
	{
		int nDash = sLine.Find(_T("- "));
		sLine = CString(' ', nDash) + _T("  * ") + sLine.Mid(nDash + 2);
	}
	else if (sTrimmed.Find(_T("1. ")) == 0)
	{
		int nNum  = sLine.Find(_T("1. "));
		sLine = CString(' ', nNum) + _T("  - ") + sLine.Mid(nNum + 3);
	}
}

void CGitHubToDokuWikiDlg::ProcessDivs(CString& sLine) const
{
	if (sLine.Find(_T("<div ")) == 0)
		sLine.Empty();
}

void CGitHubToDokuWikiDlg::ProcessIcons(CString& sLine) const
{
	sLine.Replace(_T(":penguin:"), _T(""));
	sLine.Replace(_T(":apple:"), _T(""));
	sLine.Replace(_T(":earth_asia:"), _T(""));
	sLine.Replace(_T(":hammer:"), _T(""));
	sLine.Replace(_T(":hourglass_flowing_sand:"), _T(""));
	sLine.Replace(_T(":eyes:"), _T(""));
	sLine.Replace(_T(":floppy_disk:"), _T(""));
	sLine.Replace(_T(":memo:"), _T(""));
	sLine.Replace(_T(":white_check_mark:"), _T(""));
	sLine.Replace(_T(":calendar:"), _T(""));
	sLine.Replace(_T(":exclamation:"), _T(""));
	sLine.Replace(_T(":warning:"), _T(""));
	sLine.Replace(_T(":newspaper:"), _T(""));
	sLine.Replace(_T(":question:"), _T(""));
	sLine.Replace(_T(":free:"), _T(""));
	sLine.Replace(_T(":house:"), _T(""));
	sLine.Replace(_T(":construction:"), _T("// Work in Progress. //"));
	sLine.Replace(_T(":information_source:"), _T(""));
	sLine.Replace(_T(":new:"), _T(""));
	sLine.Replace(_T(":clock3:"), _T(""));
	sLine.Replace(_T(":heavy_check_mark:"), _T("check box"));
// 	sLine.Replace(_T("::"), _T(""));
// 	sLine.Replace(_T("::"), _T(""));
// 	sLine.Replace(_T("::"), _T(""));
// 	sLine.Replace(_T("::"), _T(""));
// 	sLine.Replace(_T("::"), _T(""));
}

void CGitHubToDokuWikiDlg::ProcessMonospacing(CString& sLine) const
{
	if (sLine.Replace(_T("```"), _T("''")))
	{
		sLine += _T(" \\\\");
	}
}

void CGitHubToDokuWikiDlg::FixupCmdLineSwitches(CStringArray& aLines) const
{
	int nLine = aLines.GetSize();
	
	while (nLine--)
	{
		CString& sLine = aLines[nLine];

		if (sLine.Find(_T("==== -")) == 0)
		{
			Misc::Trim(sLine, _T("===="));

			CString sNextLine;
			Misc::Split(sLine, sNextLine, _T(" = "));

			sLine = (_T("====") + sLine + _T("===="));
			sNextLine = (_T("===") + sNextLine + _T("==="));

			aLines.InsertAt((nLine + 1), sNextLine);
		}
	}
}

void CGitHubToDokuWikiDlg::ProcessForwardSlashes(CString& sLine) const
{
	sLine.Replace(_T("tdl://"), _T("%%tdl://%%"));
	sLine.Replace(_T("file://"), _T("%%file://%%"));
}
