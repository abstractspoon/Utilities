

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Dec 24 17:51:32 2014
 */
/* Compiler settings for ProjectZipShExt.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ProjectZipShExt_h__
#define __ProjectZipShExt_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IProjectZipExt_FWD_DEFINED__
#define __IProjectZipExt_FWD_DEFINED__
typedef interface IProjectZipExt IProjectZipExt;
#endif 	/* __IProjectZipExt_FWD_DEFINED__ */


#ifndef __ProjectZipExt_FWD_DEFINED__
#define __ProjectZipExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProjectZipExt ProjectZipExt;
#else
typedef struct ProjectZipExt ProjectZipExt;
#endif /* __cplusplus */

#endif 	/* __ProjectZipExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProjectZipExt_INTERFACE_DEFINED__
#define __IProjectZipExt_INTERFACE_DEFINED__

/* interface IProjectZipExt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProjectZipExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD3FB6BC-80C8-4E78-AD2F-6DC4262C5437")
    IProjectZipExt : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IProjectZipExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProjectZipExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProjectZipExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProjectZipExt * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProjectZipExt * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProjectZipExt * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProjectZipExt * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProjectZipExt * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IProjectZipExtVtbl;

    interface IProjectZipExt
    {
        CONST_VTBL struct IProjectZipExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProjectZipExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProjectZipExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProjectZipExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProjectZipExt_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProjectZipExt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProjectZipExt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProjectZipExt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProjectZipExt_INTERFACE_DEFINED__ */



#ifndef __PROJECTZIPSHEXTLib_LIBRARY_DEFINED__
#define __PROJECTZIPSHEXTLib_LIBRARY_DEFINED__

/* library PROJECTZIPSHEXTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PROJECTZIPSHEXTLib;

EXTERN_C const CLSID CLSID_ProjectZipExt;

#ifdef __cplusplus

class DECLSPEC_UUID("3E29484C-15C0-4D95-8E69-53AE800CC92A")
ProjectZipExt;
#endif
#endif /* __PROJECTZIPSHEXTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


