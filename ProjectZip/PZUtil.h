// PZUtil.h: useful global functions.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PZUTIL_H__451E71EA_F3A8_466E_8D2C_5B34E08CD65B__INCLUDED_)
#define AFX_PZUTIL_H__451E71EA_F3A8_466E_8D2C_5B34E08CD65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SUPPORTS_VC6
#include "projectzip6.h"
#endif

#ifdef SUPPORTS_VC7
#include "projectzip7.h"
#endif

class IProjectZip;

enum PZFILETYPE
{
	UNKNOWN = -1,

#ifdef SUPPORTS_VC6
	VC6PROJECT,
	VC6WORKSPACE,
#endif

#ifdef SUPPORTS_VC7
	VC7PROJECT,
	VC7WORKSPACE,
#endif
};

static PZFILETYPE PZGetFileType(const CString& sFilePath)
{
	CStringArray aExts;

#ifdef SUPPORTS_VC6
	CProjectZip6 zip6;

	if (zip6.IsProject(sFilePath))
		return VC6PROJECT;

	else if (zip6.IsWorkspace(sFilePath))
		return VC6WORKSPACE;
#endif

#ifdef SUPPORTS_VC7
	CProjectZip7 zip7;

	if (zip7.IsProject(sFilePath))
		return VC7PROJECT;

	else if (zip7.IsWorkspace(sFilePath))
		return VC7WORKSPACE;
#endif

	return UNKNOWN;
}

static IProjectZip* PZGetInterfaceByType(PZFILETYPE nFileType, LPCTSTR szFilePath = NULL)
{
	switch (nFileType)
	{
#ifdef SUPPORTS_VC6
		case VC6PROJECT:
		case VC6WORKSPACE:
			return new CProjectZip6(szFilePath);
#endif

#ifdef SUPPORTS_VC7
		case VC7PROJECT:
		case VC7WORKSPACE:
			return new CProjectZip7(szFilePath);
#endif
	}

	return NULL;
}

static IProjectZip* PZGetInterface(LPCTSTR szFilePath)
{
	return PZGetInterfaceByType(PZGetFileType(szFilePath), szFilePath);
}

#endif // !defined(AFX_PZUTIL_H__451E71EA_F3A8_466E_8D2C_5B34E08CD65B__INCLUDED_)
