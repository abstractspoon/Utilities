# Microsoft Developer Studio Project File - Name="ProjectZipShExt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ProjectZipShExt - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZipShExt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZipShExt.mak" CFG="ProjectZipShExt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjectZipShExt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ProjectZipShExt - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ProjectZip/ProjectZipShExt", GKDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProjectZipShExt - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "SUPPORTS_VC7" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\ProjectZipShExt.dll
InputPath=.\Debug\ProjectZipShExt.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ProjectZipShExt - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "SUPPORTS_VC7" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ProjectZipShExt.dll
InputPath=.\ReleaseMinDependency\ProjectZipShExt.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ProjectZipShExt - Win32 Debug"
# Name "ProjectZipShExt - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Shared\DlgUnits.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\driveinfo.cpp
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

SOURCE=..\ProjectZip7.cpp
# End Source File
# Begin Source File

SOURCE=..\ProjectZipBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZipExt.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZipShExt.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZipShExt.def
# End Source File
# Begin Source File

SOURCE=.\ProjectZipShExt.idl
# ADD MTL /tlb ".\ProjectZipShExt.tlb" /h "ProjectZipShExt.h" /iid "ProjectZipShExt_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\ProjectZipShExt.rc
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

SOURCE=..\..\Shared\DlgUnits.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\driveinfo.h
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

SOURCE=..\ProjectZip7.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZipBase.h
# End Source File
# Begin Source File

SOURCE=.\ProjectZipExt.h
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

SOURCE=..\..\Shared\winstyles.h
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

SOURCE=.\ProjectZipExt.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\ZipUnzip\Zlib\ZLIBSTAT.LIB
# End Source File
# End Target
# End Project
