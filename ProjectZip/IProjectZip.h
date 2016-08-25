// IProjectZip.h: interface the IProjectZip class.
//
/////////////////////////////////////////////////////////////////////////////////

#if !defined(I_PROJECTZIP_H__44685C9C_5C8F_47A0_A32D_F7BDC81D1D64__INCLUDED_)
#define I_PROJECTZIP_H__44685C9C_5C8F_47A0_A32D_F7BDC81D1D64__INCLUDED_

class IProjectZip  
{
public:
	virtual void Zip(CString& sDestPath, DWORD dwOptions = (DWORD)-1) = 0; // if not provided then sDestPath is filled in

	virtual void ShowOptions(HICON hIcon, CString& sDestPath) = 0; // if not provided then sDestPath is filled in

	// 1 ==  success, 0 == failed, -1 == cancelled
	// if szProjectFilePath is not empty it is assumed to point to a valid zip file
	// if szOutputPath is not empty it is assumed to point to a valid ouput folder
	virtual int Open(LPTSTR szFilePath, LPTSTR szOutputPath = NULL, BOOL bErrorMsgs = TRUE) = 0; // buffer must be MAX_PATH in length

	virtual void Release() = 0;
};

#endif
