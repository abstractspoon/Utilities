# Microsoft Developer Studio Project File - Name="ProjectZipExe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ProjectZipExe - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZipExe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjectZipExe.mak" CFG="ProjectZipExe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjectZipExe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProjectZipExe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ProjectZipExe", XKDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProjectZipExe - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "SUPPORTS_VC7" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 "..\shared\unicode_release\shared.lib" /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /out:"Release/ProjectZip.exe"

!ELSEIF  "$(CFG)" == "ProjectZipExe - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_AFXDLL" /D "SUPPORTS_VC7" /D "WIN32" /D "_WINDOWS" /D "SUPPORTS_VC6" /D "UNICODE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 "..\shared\unicode_debug\shared.lib" /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"Debug/ProjectZip.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProjectZipExe - Win32 Release"
# Name "ProjectZipExe - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\ProjectZip\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZip6.cpp
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZip7.cpp
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZipBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZipExe.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectZipExe.rc
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\SelectFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\ProjectZip\IProjectZip.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZip6.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZip7.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\ProjectZipBase.h
# End Source File
# Begin Source File

SOURCE=.\ProjectZipExe.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\PZUtil.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\ProjectZip\SelectFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProjectZipExe.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProjectZipExe.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\projectzipexe.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\todolist.exe.manifest
# End Source File
# End Target
# End Project
