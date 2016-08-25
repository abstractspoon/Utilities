/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jul 03 20:47:40 2014
 */
/* Compiler settings for D:\_code\ProjectZip\ProjectZip6Addin\ProjectZip6Addin.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ProjectZip6AddinTypes_h__
#define __ProjectZip6AddinTypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICommands_FWD_DEFINED__
#define __ICommands_FWD_DEFINED__
typedef interface ICommands ICommands;
#endif 	/* __ICommands_FWD_DEFINED__ */


#ifndef __Commands_FWD_DEFINED__
#define __Commands_FWD_DEFINED__

#ifdef __cplusplus
typedef class Commands Commands;
#else
typedef struct Commands Commands;
#endif /* __cplusplus */

#endif 	/* __Commands_FWD_DEFINED__ */


#ifndef __ApplicationEvents_FWD_DEFINED__
#define __ApplicationEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class ApplicationEvents ApplicationEvents;
#else
typedef struct ApplicationEvents ApplicationEvents;
#endif /* __cplusplus */

#endif 	/* __ApplicationEvents_FWD_DEFINED__ */


#ifndef __DebuggerEvents_FWD_DEFINED__
#define __DebuggerEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class DebuggerEvents DebuggerEvents;
#else
typedef struct DebuggerEvents DebuggerEvents;
#endif /* __cplusplus */

#endif 	/* __DebuggerEvents_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ProjectZip6Addin_LIBRARY_DEFINED__
#define __ProjectZip6Addin_LIBRARY_DEFINED__

/* library ProjectZip6Addin */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_ProjectZip6Addin,0xC1CF4EA8,0x359C,0x4268,0x81,0x34,0x78,0xB9,0x70,0xD8,0x97,0xF9);

#ifndef __ICommands_INTERFACE_DEFINED__
#define __ICommands_INTERFACE_DEFINED__

/* interface ICommands */
/* [object][dual][oleautomation][uuid] */ 


DEFINE_GUID(IID_ICommands,0x5AA89320,0xD982,0x44BF,0xB1,0x17,0x92,0x24,0x1D,0x72,0x9D,0xCB);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AA89320-D982-44BF-B117-92241D729DCB")
    ICommands : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PZQuickZipWorkspaceCommandMethod( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PZOptionsZipWorkspaceCommandMethod( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PZQuickZipProjectCommandMethod( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PZOptionsZipProjectCommandMethod( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PZOpenProjectCommandMethod( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PZQuickZipWorkspaceCommandMethod )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PZOptionsZipWorkspaceCommandMethod )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PZQuickZipProjectCommandMethod )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PZOptionsZipProjectCommandMethod )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PZOpenProjectCommandMethod )( 
            ICommands __RPC_FAR * This);
        
        END_INTERFACE
    } ICommandsVtbl;

    interface ICommands
    {
        CONST_VTBL struct ICommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommands_PZQuickZipWorkspaceCommandMethod(This)	\
    (This)->lpVtbl -> PZQuickZipWorkspaceCommandMethod(This)

#define ICommands_PZOptionsZipWorkspaceCommandMethod(This)	\
    (This)->lpVtbl -> PZOptionsZipWorkspaceCommandMethod(This)

#define ICommands_PZQuickZipProjectCommandMethod(This)	\
    (This)->lpVtbl -> PZQuickZipProjectCommandMethod(This)

#define ICommands_PZOptionsZipProjectCommandMethod(This)	\
    (This)->lpVtbl -> PZOptionsZipProjectCommandMethod(This)

#define ICommands_PZOpenProjectCommandMethod(This)	\
    (This)->lpVtbl -> PZOpenProjectCommandMethod(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_PZQuickZipWorkspaceCommandMethod_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_PZQuickZipWorkspaceCommandMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_PZOptionsZipWorkspaceCommandMethod_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_PZOptionsZipWorkspaceCommandMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_PZQuickZipProjectCommandMethod_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_PZQuickZipProjectCommandMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_PZOptionsZipProjectCommandMethod_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_PZOptionsZipProjectCommandMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_PZOpenProjectCommandMethod_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_PZOpenProjectCommandMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommands_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Commands,0x54822F38,0x4460,0x469A,0x8C,0x77,0x70,0xA8,0xC8,0xB7,0x12,0xB8);

#ifdef __cplusplus

class DECLSPEC_UUID("54822F38-4460-469A-8C77-70A8C8B712B8")
Commands;
#endif

DEFINE_GUID(CLSID_ApplicationEvents,0x1079EEF7,0xE586,0x4D5B,0xBE,0xE7,0xF6,0xA9,0x86,0x9D,0x1D,0x86);

#ifdef __cplusplus

class DECLSPEC_UUID("1079EEF7-E586-4D5B-BEE7-F6A9869D1D86")
ApplicationEvents;
#endif

DEFINE_GUID(CLSID_DebuggerEvents,0x7901974B,0x6CEC,0x415F,0x80,0xA8,0x6B,0x4C,0x32,0x09,0x5F,0x81);

#ifdef __cplusplus

class DECLSPEC_UUID("7901974B-6CEC-415F-80A8-6B4C32095F81")
DebuggerEvents;
#endif
#endif /* __ProjectZip6Addin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
