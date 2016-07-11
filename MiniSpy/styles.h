#if !defined(AFX_STYLES_H__46AFC4E3_CC43_4E69_B5D3_2B6D1F501D0E__INCLUDED_)
#define AFX_STYLES_H__46AFC4E3_CC43_4E69_B5D3_2B6D1F501D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Style
{
	LPCTSTR szStyle; // style name
	DWORD dwStyle; // style value
};

#define STYLE(s) #s, (DWORD)s

static Style ClassStyles[] = 
{
	{ STYLE(CS_VREDRAW) }, //		0x0001
	{ STYLE(CS_HREDRAW) }, //		0x0002
	{ STYLE(CS_DBLCLKS) }, //		0x0008
	{ STYLE(CS_OWNDC) }, //			0x0020
	{ STYLE(CS_CLASSDC) }, //		0x0040
	{ STYLE(CS_PARENTDC) }, //		0x0080
	{ STYLE(CS_NOCLOSE) }, //		0x0200
	{ STYLE(CS_SAVEBITS) }, //		0x0800
	{ STYLE(CS_BYTEALIGNCLIENT) },//0x1000
	{ STYLE(CS_BYTEALIGNWINDOW) },//0x2000
	{ STYLE(CS_GLOBALCLASS) }, //	0x4000
	{ STYLE(CS_IME) }, //			0x00010000
};

static Style WindowStyles[] = 
{
	{ STYLE(WS_OVERLAPPED) }, //	0x00000000L
	{ STYLE(WS_POPUP) }, //			0x80000000L
	{ STYLE(WS_CHILD) }, //			0x40000000L
	{ STYLE(WS_MINIMIZE) }, //		0x20000000L
	{ STYLE(WS_VISIBLE) }, //		0x10000000L
	{ STYLE(WS_DISABLED) }, //		0x08000000L
	{ STYLE(WS_CLIPSIBLINGS) }, //	0x04000000L
	{ STYLE(WS_CLIPCHILDREN) }, //	0x02000000L
	{ STYLE(WS_MAXIMIZE) }, //		0x01000000L
	{ STYLE(WS_CAPTION) }, //		0x00C00000L
	{ STYLE(WS_BORDER) }, //		0x00800000L
	{ STYLE(WS_DLGFRAME) }, //		0x00400000L
	{ STYLE(WS_VSCROLL) }, //		0x00200000L
	{ STYLE(WS_HSCROLL) }, //		0x00100000L
	{ STYLE(WS_SYSMENU) }, //		0x00080000L
	{ STYLE(WS_THICKFRAME) }, //	0x00040000L
	{ STYLE(WS_GROUP) }, //			0x00020000L
	{ STYLE(WS_TABSTOP) }, //		0x00010000L
	{ STYLE(WS_MINIMIZEBOX) },//	0x00020000L
	{ STYLE(WS_MAXIMIZEBOX) },//	0x00010000L
//	{ STYLE(WS_TILED) }, // duplicate
//	{ STYLE(WS_ICONIC) }, // duplicate
//	{ STYLE(WS_SIZEBOX) }, // duplicate
//	{ STYLE(WS_TILEDWINDOW) }, // duplicate
//	{ STYLE(WS_OVERLAPPEDWINDOW) }, // aggregate style
//	{ STYLE(WS_POPUPWINDOW) }, // aggregate style
//	{ STYLE(WS_CHILDWINDOW) }, // duplicate
};

static Style WindowExStyles[] = 
{
	{ STYLE(WS_EX_DLGMODALFRAME) }, //	0x00000001L
	{ STYLE(WS_EX_NOPARENTNOTIFY) }, //	0x00000004L
	{ STYLE(WS_EX_TOPMOST) }, //		0x00000008L
	{ STYLE(WS_EX_ACCEPTFILES) }, //	0x00000010L
	{ STYLE(WS_EX_TRANSPARENT) }, //	0x00000020L
	{ STYLE(WS_EX_MDICHILD) }, //		0x00000040L
	{ STYLE(WS_EX_TOOLWINDOW) }, //		0x00000080L
	{ STYLE(WS_EX_WINDOWEDGE) }, //		0x00000100L
	{ STYLE(WS_EX_CLIENTEDGE) }, //		0x00000200L
	{ STYLE(WS_EX_CONTEXTHELP) }, //	0x00000400L
	{ STYLE(WS_EX_RIGHT) },	 // 		0x00001000L
	{ STYLE(WS_EX_LEFT) }, //			0x00000000L
	{ STYLE(WS_EX_RTLREADING) }, //		0x00002000L
	{ STYLE(WS_EX_LTRREADING) }, //		0x00000000L
	{ STYLE(WS_EX_LEFTSCROLLBAR) }, //	0x00004000L
	{ STYLE(WS_EX_RIGHTSCROLLBAR) }, // 0x00000000L
	{ STYLE(WS_EX_CONTROLPARENT) }, //	0x00010000L
	{ STYLE(WS_EX_STATICEDGE) }, //		0x00020000L
	{ STYLE(WS_EX_APPWINDOW) }, //		0x00040000L
//	{ STYLE(WS_EX_OVERLAPPEDWINDOW) }, // aggregate style
//	{ STYLE(WS_EX_PALETTEWINDOW) }, // aggregate style
};

static Style HitTests[] = 
{
	{ STYLE(HTERROR) }, //             (-2)
	{ STYLE(HTTRANSPARENT) }, //       (-1)
	{ STYLE(HTNOWHERE) }, //           0
	{ STYLE(HTCLIENT) }, //            1
	{ STYLE(HTCAPTION) }, //           2
	{ STYLE(HTSYSMENU) }, //           3
	{ STYLE(HTGROWBOX) }, //           4
	{ STYLE(HTSIZE) }, //              HTGROWBOX
	{ STYLE(HTMENU) }, //              5
	{ STYLE(HTHSCROLL) }, //           6
	{ STYLE(HTVSCROLL) }, //           7
	{ STYLE(HTMINBUTTON) }, //         8
	{ STYLE(HTMAXBUTTON) }, //         9
	{ STYLE(HTLEFT) }, //              10
	{ STYLE(HTRIGHT) }, //             11
	{ STYLE(HTTOP) }, //               12
	{ STYLE(HTTOPLEFT) }, //           13
	{ STYLE(HTTOPRIGHT) }, //          14
	{ STYLE(HTBOTTOM) }, //            15
	{ STYLE(HTBOTTOMLEFT) }, //        16
	{ STYLE(HTBOTTOMRIGHT) }, //       17
	{ STYLE(HTBORDER) }, //            18
	{ STYLE(HTREDUCE) }, //            HTMINBUTTON
	{ STYLE(HTZOOM) }, //              HTMAXBUTTON
	{ STYLE(HTSIZEFIRST) }, //         HTLEFT
	{ STYLE(HTSIZELAST) }, //          HTBOTTOMRIGHT
	{ STYLE(HTOBJECT) }, //            19
	{ STYLE(HTCLOSE) }, //             20
	{ STYLE(HTHELP) }, //              21
};

// controls
struct Control
{
	LPCTSTR szControlClass; // window class name
	LPCTSTR szBaseClass; // avoids duplicating styles for richedit and comboboxex
	DWORD dwExStyleMsg; // msg to send to control to retrieve Ex styles
};

static Control Controls[] = 
{
	{ "Button", "", 0 }, 
	{ "Static", "", 0 },
	{ "Edit", "", 0 },
	{ "ComboBox", "", 0 },
	{ "ComboLBox", "ListBox", 0 }, // drop list for the combo box
	{ "ListBox", "", 0 },
	{ "Scrollbar", "", 0 },
	{ "toolbarwindow32", "CommonControl", TB_GETEXTENDEDSTYLE }, 
	{ "msctls_updown32", "", 0 },
	{ "msctls_progress32", "", 0 },
	{ "msctls_trackbar32", "", 0 },
	{ "msctls_hotkey32", "", 0 },
	{ "SysListView32", "", LVM_GETEXTENDEDLISTVIEWSTYLE },
	{ "SysTreeView32", "", 0 },
	{ "SysTabControl32", "", TCM_GETEXTENDEDSTYLE },
	{ "SysAnimate32", "", 0 },
	{ "Richedit", "Edit", EM_GETEVENTMASK },	// event mask is like extended styles
	{ "SysDateTimePick32", "", 0 },
	{ "SysMonthCal32", "", 0 },
	{ "SysIPAddress32", "", 0 },
	{ "SysPager32", "", 0 },
	{ "ComboBoxEx32", "ComboBox", CBEM_GETEXTENDEDSTYLE },
	{ "msctls_statusbar32", "CommonControl", 0 },
	{ "ReBarWindow32", "", 0 },
	{ "SysHeader32", "", 0 },
	{ "DialogBox", "", 0 },
	{ "MDIClient", "", 0 },
	{ "tooltips_class32", "", 0 },
};

struct CtlStyle
{
	LPCTSTR szControlClass; // window class name
	LPCTSTR szStyle; // style name
	DWORD dwStyle; // style value
	DWORD dwMask; // required masked
	BOOL bExStyle; // is it an _EX_ style
};

#define NOMASK 0x0L

#ifndef HDS_VERT
#define HDS_VERT 0x0001
#endif

static CtlStyle ControlStyles[] = 
{
	{ "Button", STYLE(BS_PUSHBUTTON), 0x0F, 0 },//		0x00000000L
	{ "Button", STYLE(BS_DEFPUSHBUTTON), 0x0F, 0 },//	0x00000001L
	{ "Button", STYLE(BS_CHECKBOX), 0x0F, 0 },//		0x00000002L
	{ "Button", STYLE(BS_AUTOCHECKBOX), 0x0F, 0 },//	0x00000003L
	{ "Button", STYLE(BS_RADIOBUTTON), 0x0F, 0 },//		0x00000004L
	{ "Button", STYLE(BS_3STATE), 0x0F, 0 },//			0x00000005L
	{ "Button", STYLE(BS_AUTO3STATE), 0x0F, 0 },//		0x00000006L
	{ "Button", STYLE(BS_GROUPBOX), 0x0F, 0 },//		0x00000007L
	{ "Button", STYLE(BS_USERBUTTON), 0x0F, 0 },//		0x00000008L
	{ "Button", STYLE(BS_AUTORADIOBUTTON), 0x0F, 0 },//	0x00000009L
	{ "Button", STYLE(BS_OWNERDRAW), 0x0F, 0 },//		0x0000000BL
	{ "Button", STYLE(BS_LEFTTEXT), NOMASK, 0 },//		0x00000020L
	{ "Button", STYLE(BS_TEXT), NOMASK, 0 }, //			0x00000000L
	{ "Button", STYLE(BS_ICON), NOMASK, 0 }, //			0x00000040L
	{ "Button", STYLE(BS_BITMAP), NOMASK, 0 },//		0x00000080L
	{ "Button", STYLE(BS_LEFT), NOMASK, 0 }, //			0x00000100L
	{ "Button", STYLE(BS_RIGHT), NOMASK, 0 },//			0x00000200L
	{ "Button", STYLE(BS_CENTER), NOMASK, 0 },//		0x00000300L
	{ "Button", STYLE(BS_TOP), NOMASK, 0 }, //			0x00000400L
	{ "Button", STYLE(BS_BOTTOM), NOMASK, 0 },//		0x00000800L
	{ "Button", STYLE(BS_VCENTER), NOMASK, 0 },//		0x00000C00L
	{ "Button", STYLE(BS_PUSHLIKE), NOMASK, 0 },//		0x00001000L
	{ "Button", STYLE(BS_MULTILINE), NOMASK, 0 },//		0x00002000L
	{ "Button", STYLE(BS_NOTIFY), NOMASK, 0 }, //		0x00004000L
	{ "Button", STYLE(BS_FLAT), NOMASK, 0 }, //			0x00008000L
	{ "Button", STYLE(BS_RIGHTBUTTON), NOMASK, 0 }, //	BS_LEFTTEXT

	{ "Static", STYLE(SS_LEFT), 0x1FL, 0 },//             0x00000000L
	{ "Static", STYLE(SS_CENTER), 0x1FL, 0 },//           0x00000001L
	{ "Static", STYLE(SS_RIGHT), 0x1FL, 0 },//            0x00000002L
	{ "Static", STYLE(SS_ICON), 0x1FL, 0 },//             0x00000003L
	{ "Static", STYLE(SS_BLACKRECT), 0x1FL, 0 },//        0x00000004L
	{ "Static", STYLE(SS_GRAYRECT), 0x1FL, 0 },//         0x00000005L
	{ "Static", STYLE(SS_WHITERECT), 0x1FL, 0 },//        0x00000006L
	{ "Static", STYLE(SS_BLACKFRAME), 0x1FL, 0 },//       0x00000007L
	{ "Static", STYLE(SS_GRAYFRAME), 0x1FL, 0 },//        0x00000008L
	{ "Static", STYLE(SS_WHITEFRAME), 0x1FL, 0 },//       0x00000009L
	{ "Static", STYLE(SS_USERITEM), 0x1FL, 0 },//         0x0000000AL
	{ "Static", STYLE(SS_SIMPLE), 0x1FL, 0 },//           0x0000000BL
	{ "Static", STYLE(SS_LEFTNOWORDWRAP), 0x1FL, 0 },//   0x0000000CL
	{ "Static", STYLE(SS_OWNERDRAW), 0x1FL, 0 },//        0x0000000DL
	{ "Static", STYLE(SS_BITMAP), 0x1FL, 0 },//           0x0000000EL
	{ "Static", STYLE(SS_ENHMETAFILE), 0x1FL, 0 },//      0x0000000FL
	{ "Static", STYLE(SS_ETCHEDHORZ), 0x1FL, 0 },//       0x00000010L
	{ "Static", STYLE(SS_ETCHEDVERT), 0x1FL, 0 },//       0x00000011L
	{ "Static", STYLE(SS_ETCHEDFRAME), 0x1FL, 0 },//      0x00000012L
	{ "Static", STYLE(SS_NOPREFIX), NOMASK, 0 },//        0x00000080L
	{ "Static", STYLE(SS_NOTIFY), NOMASK, 0 },//          0x00000100L
	{ "Static", STYLE(SS_CENTERIMAGE), NOMASK, 0 },//     0x00000200L
	{ "Static", STYLE(SS_RIGHTJUST), NOMASK, 0 },//       0x00000400L
	{ "Static", STYLE(SS_REALSIZEIMAGE), NOMASK, 0 },//   0x00000800L
	{ "Static", STYLE(SS_SUNKEN), NOMASK, 0 },//          0x00001000L
	{ "Static", STYLE(SS_ENDELLIPSIS), 0xC000L, 0 },//    0x00004000L
	{ "Static", STYLE(SS_PATHELLIPSIS), 0xC000L, 0 },//   0x00008000L
	{ "Static", STYLE(SS_WORDELLIPSIS), 0xC000L, 0 },//   0x0000C000L

	{ "Edit", STYLE(ES_LEFT), 0x2L, 0 },//                0x0000L
	{ "Edit", STYLE(ES_CENTER), 0x2L, 0 },//              0x0001L
	{ "Edit", STYLE(ES_RIGHT), 0x2L, 0 },//               0x0002L
	{ "Edit", STYLE(ES_MULTILINE), NOMASK, 0 },//         0x0004L
	{ "Edit", STYLE(ES_UPPERCASE), NOMASK, 0 },//         0x0008L
	{ "Edit", STYLE(ES_LOWERCASE), NOMASK, 0 },//         0x0010L
	{ "Edit", STYLE(ES_PASSWORD), NOMASK, 0 },//          0x0020L
	{ "Edit", STYLE(ES_AUTOVSCROLL), NOMASK, 0 },//       0x0040L
	{ "Edit", STYLE(ES_AUTOHSCROLL), NOMASK, 0 },//       0x0080L
	{ "Edit", STYLE(ES_NOHIDESEL), NOMASK, 0 },//         0x0100L
	{ "Edit", STYLE(ES_OEMCONVERT), NOMASK, 0 },//        0x0400L
	{ "Edit", STYLE(ES_READONLY), NOMASK, 0 },//          0x0800L
	{ "Edit", STYLE(ES_WANTRETURN), NOMASK, 0 },//        0x1000L
	{ "Edit", STYLE(ES_NUMBER), NOMASK, 0 },//            0x2000L

	{ "ComboBox", STYLE(CBS_SIMPLE), 0xFL, 0 },//               0x0001L
	{ "ComboBox", STYLE(CBS_DROPDOWN), 0xFL, 0 },//             0x0002L
	{ "ComboBox", STYLE(CBS_DROPDOWNLIST), 0xFL, 0 },//         0x0003L
	{ "ComboBox", STYLE(CBS_OWNERDRAWFIXED), NOMASK, 0 },//     0x0010L
	{ "ComboBox", STYLE(CBS_OWNERDRAWVARIABLE), NOMASK, 0 },//  0x0020L
	{ "ComboBox", STYLE(CBS_AUTOHSCROLL), NOMASK, 0 },//        0x0040L
	{ "ComboBox", STYLE(CBS_OEMCONVERT), NOMASK, 0 },//         0x0080L
	{ "ComboBox", STYLE(CBS_SORT), NOMASK, 0 },//               0x0100L
	{ "ComboBox", STYLE(CBS_HASSTRINGS), NOMASK, 0 },//         0x0200L
	{ "ComboBox", STYLE(CBS_NOINTEGRALHEIGHT), NOMASK, 0 },//   0x0400L
	{ "ComboBox", STYLE(CBS_DISABLENOSCROLL), NOMASK, 0 },//    0x0800L
	{ "ComboBox", STYLE(CBS_UPPERCASE), NOMASK, 0 },//          0x2000L
	{ "ComboBox", STYLE(CBS_LOWERCASE), NOMASK, 0 },//          0x4000L

	{ "ListBox", STYLE(LBS_NOTIFY), NOMASK, 0 },//             0x0001L
	{ "ListBox", STYLE(LBS_SORT), NOMASK, 0 },//               0x0002L
	{ "ListBox", STYLE(LBS_NOREDRAW), NOMASK, 0 },//           0x0004L
	{ "ListBox", STYLE(LBS_MULTIPLESEL), NOMASK, 0 },//        0x0008L
	{ "ListBox", STYLE(LBS_OWNERDRAWFIXED), NOMASK, 0 },//     0x0010L
	{ "ListBox", STYLE(LBS_OWNERDRAWVARIABLE), NOMASK, 0 },//  0x0020L
	{ "ListBox", STYLE(LBS_HASSTRINGS), NOMASK, 0 },//         0x0040L
	{ "ListBox", STYLE(LBS_USETABSTOPS), NOMASK, 0 },//        0x0080L
	{ "ListBox", STYLE(LBS_NOINTEGRALHEIGHT), NOMASK, 0 },//   0x0100L
	{ "ListBox", STYLE(LBS_MULTICOLUMN), NOMASK, 0 },//        0x0200L
	{ "ListBox", STYLE(LBS_WANTKEYBOARDINPUT), NOMASK, 0 },//  0x0400L
	{ "ListBox", STYLE(LBS_EXTENDEDSEL), NOMASK, 0 },//        0x0800L
	{ "ListBox", STYLE(LBS_DISABLENOSCROLL), NOMASK, 0 },//    0x1000L
	{ "ListBox", STYLE(LBS_NODATA), NOMASK, 0 },//             0x2000L
	{ "ListBox", STYLE(LBS_NOSEL), NOMASK, 0 },//              0x4000L
	{ "ListBox", STYLE(LBS_STANDARD), NOMASK, 0 },//           (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)

	{ "Scrollbar", STYLE(SBS_HORZ), 0x1L, 0 },//                       0x0000L
	{ "Scrollbar", STYLE(SBS_VERT), 0x1L, 0 },//                       0x0001L
	{ "Scrollbar", STYLE(SBS_TOPALIGN), NOMASK, 0 },//                 0x0002L
	{ "Scrollbar", STYLE(SBS_LEFTALIGN), NOMASK, 0 },//                0x0002L
	{ "Scrollbar", STYLE(SBS_BOTTOMALIGN), NOMASK, 0 },//              0x0004L
	{ "Scrollbar", STYLE(SBS_RIGHTALIGN), NOMASK, 0 },//               0x0004L
	{ "Scrollbar", STYLE(SBS_SIZEBOXTOPLEFTALIGN), NOMASK, 0 },//      0x0002L
	{ "Scrollbar", STYLE(SBS_SIZEBOXBOTTOMRIGHTALIGN), NOMASK, 0 },//  0x0004L
	{ "Scrollbar", STYLE(SBS_SIZEBOX), NOMASK, 0 },//                  0x0008L
	{ "Scrollbar", STYLE(SBS_SIZEGRIP), NOMASK, 0 },//                 0x0010L

/*	{ "toolbarwindow32", STYLE(TBSTYLE_BUTTON), 0x1L, 0 },//             0x0000
	{ "toolbarwindow32", STYLE(TBSTYLE_SEP), 0x1L, 0 },//                0x0001
	{ "toolbarwindow32", STYLE(TBSTYLE_CHECK), NOMASK, 0 },//            0x0002
	{ "toolbarwindow32", STYLE(TBSTYLE_GROUP), NOMASK, 0 },//            0x0004
	{ "toolbarwindow32", STYLE(TBSTYLE_CHECKGROUP), NOMASK, 0 },//       (TBSTYLE_GROUP | TBSTYLE_CHECK)
	{ "toolbarwindow32", STYLE(TBSTYLE_DROPDOWN), NOMASK, 0 },//         0x0008
*/	{ "toolbarwindow32", STYLE(TBSTYLE_AUTOSIZE), NOMASK, 0 },//         0x0010 // automatically calculate the cx of the button
	{ "toolbarwindow32", STYLE(TBSTYLE_NOPREFIX), NOMASK, 0 },//         0x0020 // if this button should not have accel prefix
	{ "toolbarwindow32", STYLE(TBSTYLE_TOOLTIPS), NOMASK, 0 },//         0x0100
	{ "toolbarwindow32", STYLE(TBSTYLE_WRAPABLE), NOMASK, 0 },//         0x0200
	{ "toolbarwindow32", STYLE(TBSTYLE_ALTDRAG), NOMASK, 0 },//          0x0400
	{ "toolbarwindow32", STYLE(TBSTYLE_FLAT), NOMASK, 0 },//             0x0800
	{ "toolbarwindow32", STYLE(TBSTYLE_LIST), NOMASK, 0 },//             0x1000
	{ "toolbarwindow32", STYLE(TBSTYLE_CUSTOMERASE), NOMASK, 0 },//      0x2000
	{ "toolbarwindow32", STYLE(TBSTYLE_REGISTERDROP), NOMASK, 0 },//     0x4000
	{ "toolbarwindow32", STYLE(TBSTYLE_TRANSPARENT), NOMASK, 0 },//      0x8000
	{ "toolbarwindow32", STYLE(TBSTYLE_EX_DRAWDDARROWS), NOMASK, 1 },//  0x00000001

	{ "CommonControl", STYLE(CCS_TOP), NOMASK, 0 },//                 0x00000001L
	{ "CommonControl", STYLE(CCS_NOMOVEY), NOMASK, 0 },//             0x00000002L
	{ "CommonControl", STYLE(CCS_BOTTOM), NOMASK, 0 },//              0x00000003L
	{ "CommonControl", STYLE(CCS_NORESIZE), NOMASK, 0 },//            0x00000004L
	{ "CommonControl", STYLE(CCS_NOPARENTALIGN), NOMASK, 0 },//       0x00000008L
	{ "CommonControl", STYLE(CCS_ADJUSTABLE), NOMASK, 0 },//          0x00000020L
	{ "CommonControl", STYLE(CCS_NODIVIDER), NOMASK, 0 },//           0x00000040L
	{ "CommonControl", STYLE(CCS_VERT), NOMASK, 0 },//                0x00000080L

	{ "msctls_updown32", STYLE(UDS_WRAP), NOMASK, 0 },//                 0x0001
	{ "msctls_updown32", STYLE(UDS_SETBUDDYINT), NOMASK, 0 },//          0x0002
	{ "msctls_updown32", STYLE(UDS_ALIGNRIGHT), NOMASK, 0 },//           0x0004
	{ "msctls_updown32", STYLE(UDS_ALIGNLEFT), NOMASK, 0 },//            0x0008
	{ "msctls_updown32", STYLE(UDS_AUTOBUDDY), NOMASK, 0 },//            0x0010
	{ "msctls_updown32", STYLE(UDS_ARROWKEYS), NOMASK, 0 },//            0x0020
	{ "msctls_updown32", STYLE(UDS_HORZ), NOMASK, 0 },//                 0x0040
	{ "msctls_updown32", STYLE(UDS_NOTHOUSANDS), NOMASK, 0 },//          0x0080
	{ "msctls_updown32", STYLE(UDS_HOTTRACK), NOMASK, 0 },//             0x0100

	{ "msctls_progress32", STYLE(PBS_SMOOTH), NOMASK, 0 },//               0x01
	{ "msctls_progress32", STYLE(PBS_VERTICAL), NOMASK, 0 },//             0x04

	{ "msctls_trackbar32", STYLE(TBS_AUTOTICKS), NOMASK, 0 },//            0x0001
	{ "msctls_trackbar32", STYLE(TBS_VERT), NOMASK, 0 },//                 0x0002
	{ "msctls_trackbar32", STYLE(TBS_HORZ), NOMASK, 0 },//                 0x0000
	{ "msctls_trackbar32", STYLE(TBS_TOP), NOMASK, 0 },//                  0x0004
	{ "msctls_trackbar32", STYLE(TBS_BOTTOM), NOMASK, 0 },//               0x0000
	{ "msctls_trackbar32", STYLE(TBS_LEFT), NOMASK, 0 },//                 0x0004
	{ "msctls_trackbar32", STYLE(TBS_RIGHT), NOMASK, 0 },//                0x0000
	{ "msctls_trackbar32", STYLE(TBS_BOTH), NOMASK, 0 },//                 0x0008
	{ "msctls_trackbar32", STYLE(TBS_NOTICKS), NOMASK, 0 },//              0x0010
	{ "msctls_trackbar32", STYLE(TBS_ENABLESELRANGE), NOMASK, 0 },//       0x0020
	{ "msctls_trackbar32", STYLE(TBS_FIXEDLENGTH), NOMASK, 0 },//          0x0040
	{ "msctls_trackbar32", STYLE(TBS_NOTHUMB), NOMASK, 0 },//              0x0080
	{ "msctls_trackbar32", STYLE(TBS_TOOLTIPS), NOMASK, 0 },//             0x0100

//	{ "msctls_hotkey32", // has no styles

	{ "SysListView32", STYLE(LVS_ICON), LVS_TYPEMASK, 0 },//           0x0000
	{ "SysListView32", STYLE(LVS_REPORT), LVS_TYPEMASK, 0 },//         0x0001
	{ "SysListView32", STYLE(LVS_SMALLICON), LVS_TYPEMASK, 0 },//      0x0002
	{ "SysListView32", STYLE(LVS_LIST), LVS_TYPEMASK, 0 },//           0x0003
//	{ "SysListView32", STYLE(LVS_TYPEMASK), NOMASK, 0 },//             0x0003
	{ "SysListView32", STYLE(LVS_SINGLESEL), NOMASK, 0 },//            0x0004
	{ "SysListView32", STYLE(LVS_SHOWSELALWAYS), NOMASK, 0 },//        0x0008
	{ "SysListView32", STYLE(LVS_SORTASCENDING), NOMASK, 0 },//        0x0010
	{ "SysListView32", STYLE(LVS_SORTDESCENDING), NOMASK, 0 },//       0x0020
	{ "SysListView32", STYLE(LVS_SHAREIMAGELISTS), NOMASK, 0 },//      0x0040
	{ "SysListView32", STYLE(LVS_NOLABELWRAP), NOMASK, 0 },//          0x0080
	{ "SysListView32", STYLE(LVS_AUTOARRANGE), NOMASK, 0 },//          0x0100
	{ "SysListView32", STYLE(LVS_EDITLABELS), NOMASK, 0 },//           0x0200
	{ "SysListView32", STYLE(LVS_OWNERDATA), NOMASK, 0 },//            0x1000
	{ "SysListView32", STYLE(LVS_NOSCROLL), NOMASK, 0 },//             0x2000
//	{ "SysListView32", STYLE(LVS_TYPESTYLEMASK), NOMASK, 0 },//        0xfc00
	{ "SysListView32", STYLE(LVS_ALIGNTOP), LVS_ALIGNMASK, 0 },//      0x0000
	{ "SysListView32", STYLE(LVS_ALIGNLEFT), LVS_ALIGNMASK, 0 },//     0x0800
//	{ "SysListView32", STYLE(LVS_ALIGNMASK), NOMASK, 0 },//            0x0c00
	{ "SysListView32", STYLE(LVS_OWNERDRAWFIXED), NOMASK, 0 },//       0x0400
	{ "SysListView32", STYLE(LVS_NOCOLUMNHEADER), NOMASK, 0 },//       0x4000
	{ "SysListView32", STYLE(LVS_NOSORTHEADER), NOMASK, 0 },//         0x8000
	{ "SysListView32", STYLE(LVS_EX_GRIDLINES), NOMASK, 1 },//        0x00000001
	{ "SysListView32", STYLE(LVS_EX_SUBITEMIMAGES), NOMASK, 1 },//    0x00000002
	{ "SysListView32", STYLE(LVS_EX_CHECKBOXES), NOMASK, 1 },//       0x00000004
	{ "SysListView32", STYLE(LVS_EX_TRACKSELECT), NOMASK, 1 },//      0x00000008
	{ "SysListView32", STYLE(LVS_EX_HEADERDRAGDROP), NOMASK, 1 },//   0x00000010
	{ "SysListView32", STYLE(LVS_EX_FULLROWSELECT), NOMASK, 1 },//    0x00000020 // applies to report mode only
	{ "SysListView32", STYLE(LVS_EX_ONECLICKACTIVATE), NOMASK, 1 },// 0x00000040
	{ "SysListView32", STYLE(LVS_EX_TWOCLICKACTIVATE), NOMASK, 1 },// 0x00000080
	{ "SysListView32", STYLE(LVS_EX_FLATSB), NOMASK, 1 },//           0x00000100
	{ "SysListView32", STYLE(LVS_EX_REGIONAL), NOMASK, 1 },//         0x00000200
	{ "SysListView32", STYLE(LVS_EX_INFOTIP), NOMASK, 1 },//          0x00000400 // listview does InfoTips for you
	{ "SysListView32", STYLE(LVS_EX_UNDERLINEHOT), NOMASK, 1 },//     0x00000800
	{ "SysListView32", STYLE(LVS_EX_UNDERLINECOLD), NOMASK, 1 },//    0x00001000
	{ "SysListView32", STYLE(LVS_EX_MULTIWORKAREAS), NOMASK, 1 },//   0x00002000

	{ "SysTreeView32", STYLE(TVS_HASBUTTONS), NOMASK, 0 },//           0x0001
	{ "SysTreeView32", STYLE(TVS_HASLINES), NOMASK, 0 },//             0x0002
	{ "SysTreeView32", STYLE(TVS_LINESATROOT), NOMASK, 0 },//          0x0004
	{ "SysTreeView32", STYLE(TVS_EDITLABELS), NOMASK, 0 },//           0x0008
	{ "SysTreeView32", STYLE(TVS_DISABLEDRAGDROP), NOMASK, 0 },//      0x0010
	{ "SysTreeView32", STYLE(TVS_SHOWSELALWAYS), NOMASK, 0 },//        0x0020
	{ "SysTreeView32", STYLE(TVS_RTLREADING), NOMASK, 0 },//           0x0040
	{ "SysTreeView32", STYLE(TVS_NOTOOLTIPS), NOMASK, 0 },//           0x0080
	{ "SysTreeView32", STYLE(TVS_CHECKBOXES), NOMASK, 0 },//           0x0100
	{ "SysTreeView32", STYLE(TVS_TRACKSELECT), NOMASK, 0 },//          0x0200
	{ "SysTreeView32", STYLE(TVS_SINGLEEXPAND), NOMASK, 0 },//         0x0400
	{ "SysTreeView32", STYLE(TVS_INFOTIP), NOMASK, 0 },//              0x0800
	{ "SysTreeView32", STYLE(TVS_FULLROWSELECT), NOMASK, 0 },//        0x1000
	{ "SysTreeView32", STYLE(TVS_NOSCROLL), NOMASK, 0 },//             0x2000
	{ "SysTreeView32", STYLE(TVS_NONEVENHEIGHT), NOMASK, 0 },//        0x4000

	{ "SysTabControl32", STYLE(TCS_SCROLLOPPOSITE), NOMASK, 0 },//       0x0001   // assumes multiline tab
	{ "SysTabControl32", STYLE(TCS_BOTTOM), NOMASK, 0 },//               0x0002
	{ "SysTabControl32", STYLE(TCS_RIGHT), NOMASK, 0 },//                0x0002
	{ "SysTabControl32", STYLE(TCS_MULTISELECT), NOMASK, 0 },//          0x0004  // allow multi-select in button mode
	{ "SysTabControl32", STYLE(TCS_FLATBUTTONS), NOMASK, 0 },//          0x0008
	{ "SysTabControl32", STYLE(TCS_FORCEICONLEFT), NOMASK, 0 },//        0x0010
	{ "SysTabControl32", STYLE(TCS_FORCELABELLEFT), NOMASK, 0 },//       0x0020
	{ "SysTabControl32", STYLE(TCS_HOTTRACK), NOMASK, 0 },//             0x0040
	{ "SysTabControl32", STYLE(TCS_VERTICAL), NOMASK, 0 },//             0x0080
	{ "SysTabControl32", STYLE(TCS_TABS), NOMASK, 0 },//                 0x0000
	{ "SysTabControl32", STYLE(TCS_BUTTONS), NOMASK, 0 },//              0x0100
	{ "SysTabControl32", STYLE(TCS_SINGLELINE), NOMASK, 0 },//           0x0000
	{ "SysTabControl32", STYLE(TCS_MULTILINE), NOMASK, 0 },//            0x0200
	{ "SysTabControl32", STYLE(TCS_RIGHTJUSTIFY), NOMASK, 0 },//         0x0000
	{ "SysTabControl32", STYLE(TCS_FIXEDWIDTH), NOMASK, 0 },//           0x0400
	{ "SysTabControl32", STYLE(TCS_RAGGEDRIGHT), NOMASK, 0 },//          0x0800
	{ "SysTabControl32", STYLE(TCS_FOCUSONBUTTONDOWN), NOMASK, 0 },//    0x1000
	{ "SysTabControl32", STYLE(TCS_OWNERDRAWFIXED), NOMASK, 0 },//       0x2000
	{ "SysTabControl32", STYLE(TCS_TOOLTIPS), NOMASK, 0 },//             0x4000
	{ "SysTabControl32", STYLE(TCS_FOCUSNEVER), NOMASK, 0 },//           0x8000
	{ "SysTabControl32", STYLE(TCS_EX_FLATSEPARATORS), NOMASK, 1 },//   0x00000001
	{ "SysTabControl32", STYLE(TCS_EX_REGISTERDROP), NOMASK, 1 },//     0x00000002

	{ "SysAnimate32", STYLE(ACS_CENTER), NOMASK, 0 },//               0x0001
	{ "SysAnimate32", STYLE(ACS_TRANSPARENT), NOMASK, 0 },//          0x0002
	{ "SysAnimate32", STYLE(ACS_AUTOPLAY), NOMASK, 0 },//             0x0004
	{ "SysAnimate32", STYLE(ACS_TIMER), NOMASK, 0 },//                0x0008  // don't use threads... use timers

	// uses styles from EDIT control
	{ "Richedit", STYLE(ES_SAVESEL), NOMASK, 0 },//				0x00008000
	{ "Richedit", STYLE(ES_SUNKEN), NOMASK, 0 },//				0x00004000
	{ "Richedit", STYLE(ES_DISABLENOSCROLL), NOMASK, 0 },//		0x00002000
	{ "Richedit", STYLE(ES_SELECTIONBAR), NOMASK, 0 },//		0x01000000
	{ "Richedit", STYLE(ES_NOOLEDRAGDROP), NOMASK, 0 },//		0x00000008
	// event mask is like extended styles
	{ "Richedit", STYLE(ENM_NONE), 0x1L, 1 },//				0x00000000
	{ "Richedit", STYLE(ENM_CHANGE), NOMASK, 1 },//				0x00000001
	{ "Richedit", STYLE(ENM_UPDATE), NOMASK, 1 },//				0x00000002
	{ "Richedit", STYLE(ENM_SCROLL), NOMASK, 1 },//				0x00000004
	{ "Richedit", STYLE(ENM_KEYEVENTS), NOMASK, 1 },//			0x00010000
	{ "Richedit", STYLE(ENM_MOUSEEVENTS), NOMASK, 1 },//		0x00020000
	{ "Richedit", STYLE(ENM_REQUESTRESIZE), NOMASK, 1 },//		0x00040000
	{ "Richedit", STYLE(ENM_SELCHANGE), NOMASK, 1 },//			0x00080000
	{ "Richedit", STYLE(ENM_DROPFILES), NOMASK, 1 },//			0x00100000
	{ "Richedit", STYLE(ENM_PROTECTED), NOMASK, 1 },//			0x00200000
	{ "Richedit", STYLE(ENM_CORRECTTEXT), NOMASK, 1 },//		0x00400000		/* PenWin specific */
	{ "Richedit", STYLE(ENM_SCROLLEVENTS), NOMASK, 1 },//		0x00000008
	{ "Richedit", STYLE(ENM_DRAGDROPDONE), NOMASK, 1 },//		0x00000010
	{ "Richedit", STYLE(ENM_IMECHANGE), NOMASK, 1 },//			0x00800000		/* unused by RE2.0 */
	{ "Richedit", STYLE(ENM_LANGCHANGE), NOMASK, 1 },//			0x01000000
	{ "Richedit", STYLE(ENM_OBJECTPOSITIONS), NOMASK, 1 },//	0x02000000
	{ "Richedit", STYLE(ENM_LINK), NOMASK, 1 },//				0x04000000

	{ "SysDateTimePick32", STYLE(DTS_UPDOWN), NOMASK, 0 },//           0x0001 // use UPDOWN instead of MONTHCAL
	{ "SysDateTimePick32", STYLE(DTS_SHOWNONE), NOMASK, 0 },//         0x0002 // allow a NONE selection
	{ "SysDateTimePick32", STYLE(DTS_SHORTDATEFORMAT), 0x4L, 0 },//    0x0000 // use the short date format (app must forward WM_WININICHANGE messages)
	{ "SysDateTimePick32", STYLE(DTS_LONGDATEFORMAT), 0x4L, 0 },//     0x0004 // use the long date format (app must forward WM_WININICHANGE messages)
	{ "SysDateTimePick32", STYLE(DTS_TIMEFORMAT), NOMASK, 0 },//       0x0009 // use the time format (app must forward WM_WININICHANGE messages)
	{ "SysDateTimePick32", STYLE(DTS_APPCANPARSE), NOMASK, 0 },//      0x0010 // allow user entered strings (app MUST respond to DTN_USERSTRING)
	{ "SysDateTimePick32", STYLE(DTS_RIGHTALIGN), NOMASK, 0 },//       0x0020 // right-align popup instead of left-align it

	{ "SysMonthCal32", STYLE(MCS_DAYSTATE), NOMASK, 0 },//         0x0001
	{ "SysMonthCal32", STYLE(MCS_MULTISELECT), NOMASK, 0 },//      0x0002
	{ "SysMonthCal32", STYLE(MCS_WEEKNUMBERS), NOMASK, 0 },//      0x0004
	{ "SysMonthCal32", STYLE(MCS_NOTODAYCIRCLE), NOMASK, 0 },//    0x0008
	{ "SysMonthCal32", STYLE(MCS_NOTODAY), NOMASK, 0 },//          0x0010

//	{ "SysIPAddress32", // no styles

	{ "SysPager32", STYLE(PGS_VERT), 0x1L, 0 },//                   0x00000000
	{ "SysPager32", STYLE(PGS_HORZ ), 0x1L, 0 },//                  0x00000001
	{ "SysPager32", STYLE(PGS_AUTOSCROLL), NOMASK, 0 },//           0x00000002
	{ "SysPager32", STYLE(PGS_DRAGNDROP), NOMASK, 0 },//            0x00000004

	// uses styles from combo box
	{ "ComboBoxEx32", STYLE(CBES_EX_NOEDITIMAGE), NOMASK, 1 },//          0x00000001
	{ "ComboBoxEx32", STYLE(CBES_EX_NOEDITIMAGEINDENT), NOMASK, 1 },//    0x00000002
	{ "ComboBoxEx32", STYLE(CBES_EX_PATHWORDBREAKPROC), NOMASK, 1 },//    0x00000004
	{ "ComboBoxEx32", STYLE(CBES_EX_NOSIZELIMIT), NOMASK, 1 },//          0x00000008
	{ "ComboBoxEx32", STYLE(CBES_EX_CASESENSITIVE), NOMASK, 1 },//        0x00000010

	{ "msctls_statusbar32", STYLE(SBARS_SIZEGRIP), NOMASK, 0 },//         0x0100

	{ "ReBarWindow32", STYLE(RBBS_BREAK), NOMASK, 0 },//           0x00000001  // break to new line
	{ "ReBarWindow32", STYLE(RBBS_FIXEDSIZE), NOMASK, 0 },//       0x00000002  // band can't be sized
	{ "ReBarWindow32", STYLE(RBBS_CHILDEDGE), NOMASK, 0 },//       0x00000004  // edge around top & bottom of child window
	{ "ReBarWindow32", STYLE(RBBS_HIDDEN), NOMASK, 0 },//          0x00000008  // don't show
	{ "ReBarWindow32", STYLE(RBBS_NOVERT), NOMASK, 0 },//          0x00000010  // don't show when vertical
	{ "ReBarWindow32", STYLE(RBBS_FIXEDBMP), NOMASK, 0 },//        0x00000020  // bitmap doesn't move during band resize
	{ "ReBarWindow32", STYLE(RBBS_VARIABLEHEIGHT), NOMASK, 0 },//  0x00000040  // allow autosizing of this child vertically
	{ "ReBarWindow32", STYLE(RBBS_GRIPPERALWAYS), NOMASK, 0 },//   0x00000080  // always show the gripper
	{ "ReBarWindow32", STYLE(RBBS_NOGRIPPER), NOMASK, 0 },//       0x00000100  // never show the gripper

	{ "SysHeader32", STYLE(HDS_HORZ), 0x1L, 0 },//                   0x0000
	{ "SysHeader32", STYLE(HDS_VERT), 0x1L, 0 },//                   0x0001
	{ "SysHeader32", STYLE(HDS_BUTTONS), NOMASK, 0 },//              0x0002
	{ "SysHeader32", STYLE(HDS_HOTTRACK), NOMASK, 0 },//             0x0004
	{ "SysHeader32", STYLE(HDS_HIDDEN), NOMASK, 0 },//               0x0008
	{ "SysHeader32", STYLE(HDS_DRAGDROP), NOMASK, 0 },//             0x0040
	{ "SysHeader32", STYLE(HDS_FULLDRAG), NOMASK, 0 },//             0x0080
	{ "SysHeader32", STYLE(HDS_BUTTONS), NOMASK, 0 },//              0x0002

	{ "DialogBox", STYLE(DS_ABSALIGN), NOMASK, 0 },//          0x01L
	{ "DialogBox", STYLE(DS_SYSMODAL), NOMASK, 0 },//          0x02L
	{ "DialogBox", STYLE(DS_LOCALEDIT), NOMASK, 0 },//         0x20L   /* Edit items get Local storage. */
	{ "DialogBox", STYLE(DS_SETFONT), NOMASK, 0 },//           0x40L   /* User specified font for Dlg controls */
	{ "DialogBox", STYLE(DS_MODALFRAME), NOMASK, 0 },//        0x80L   /* Can be combined with WS_CAPTION  */
	{ "DialogBox", STYLE(DS_NOIDLEMSG), NOMASK, 0 },//         0x100L  /* WM_ENTERIDLE message will not be sent */
	{ "DialogBox", STYLE(DS_SETFOREGROUND), NOMASK, 0 },//     0x200L  /* not in win3.1 */
	{ "DialogBox", STYLE(DS_3DLOOK), NOMASK, 0 },//            0x0004L
	{ "DialogBox", STYLE(DS_FIXEDSYS), NOMASK, 0 },//          0x0008L
	{ "DialogBox", STYLE(DS_NOFAILCREATE), NOMASK, 0 },//      0x0010L
	{ "DialogBox", STYLE(DS_CONTROL), NOMASK, 0 },//           0x0400L
	{ "DialogBox", STYLE(DS_CENTER), NOMASK, 0 },//            0x0800L
	{ "DialogBox", STYLE(DS_CENTERMOUSE), NOMASK, 0 },//       0x1000L
	{ "DialogBox", STYLE(DS_CONTEXTHELP), NOMASK, 0 },//       0x2000L

//	{ "MDIClient", // no styles

#ifndef TTS_NOANIMATE

	#define TTS_NOANIMATE           0x10
	#define TTS_NOFADE              0x20
	#define TTS_BALLOON             0x40

#endif

	{ "tooltips_class32", STYLE(TTS_ALWAYSTIP), NOMASK, 0 }, //	0x01
	{ "tooltips_class32", STYLE(TTS_NOPREFIX), NOMASK, 0 }, //	0x02
	{ "tooltips_class32", STYLE(TTS_NOANIMATE), NOMASK, 0 }, //	0x10
	{ "tooltips_class32", STYLE(TTS_NOFADE), NOMASK, 0 }, //	0x20
	{ "tooltips_class32", STYLE(TTS_BALLOON), NOMASK, 0 }, //	0x40

};
#endif