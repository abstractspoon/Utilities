# Microsoft Developer Studio Project File - Name="ProjectZip6Addin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ProjectZip6Addin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZip6Addin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZip6Addin.mak" CFG="ProjectZip6Addin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjectZip6Addin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ProjectZip6Addin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ProjectZip6Addin", GXBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProjectZip6Addin - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBC"

!ELSEIF  "$(CFG)" == "ProjectZip6Addin - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_USRDLL" /D "_WINDLL" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBC" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProjectZip6Addin - Win32 Release"
# Name "ProjectZip6Addin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\DlgUnits.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DSAddIn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\ProjectZip6.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZip6Addin.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZip6Addin.def
# End Source File
# Begin Source File

SOURCE=.\ProjectZip6Addin.odl
# ADD MTL /h "ProjectZip6AddinTypes.h"
# End Source File
# Begin Source File

SOURCE=.\ProjectZip6Addin.rc
# End Source File
# Begin Source File

SOURCE=..\ProjectZipBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RCCtrlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RichEditHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RuntimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\SelectFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Unzipper.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Shared\WinClasses.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zipper.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Commands.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\DlgUnits.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\DSAddIn.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\IOAPI.H
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\IOWIN32.H
# End Source File
# Begin Source File

SOURCE=..\IProjectZip.h
# End Source File
# Begin Source File

SOURCE=..\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip6.h
# End Source File
# Begin Source File

SOURCE=.\ProjectZip6Addin.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZipBase.h
# End Source File
# Begin Source File

SOURCE=..\PZUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RCCtrlParser.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RichEditHelper.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\RuntimeDlg.h
# End Source File
# Begin Source File

SOURCE=..\SelectFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\3rdParty\TOM.h
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\UNZIP.H
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Unzipper.h
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\ZCONF.H
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\ZIP.H
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zipper.h
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\ZLIB.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\ICON.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ProjectZip6Addin.rc2
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\TBarLrge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TBarMedm.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\ZLIBSTAT.LIB
# End Source File
# End Target
# End Project
