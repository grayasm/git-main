/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Thu Jul 17 19:43:38 1997
 */
/* Compiler settings for ComDemo.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ComDemo_h__
#define __ComDemo_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAutoIncr_FWD_DEFINED__
#define __IAutoIncr_FWD_DEFINED__
typedef interface IAutoIncr IAutoIncr;
#endif 	/* __IAutoIncr_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAutoIncr_INTERFACE_DEFINED__
#define __IAutoIncr_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAutoIncr
 * at Thu Jul 17 19:43:38 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAutoIncr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IAutoIncr : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SlowCounter( 
            /* [retval][out] */ WORD __RPC_FAR *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FastCounter( 
            /* [retval][out] */ WORD __RPC_FAR *pValue) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutoIncrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAutoIncr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAutoIncr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAutoIncr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAutoIncr __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAutoIncr __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAutoIncr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAutoIncr __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SlowCounter )( 
            IAutoIncr __RPC_FAR * This,
            /* [retval][out] */ WORD __RPC_FAR *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FastCounter )( 
            IAutoIncr __RPC_FAR * This,
            /* [retval][out] */ WORD __RPC_FAR *pValue);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IAutoIncr __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        END_INTERFACE
    } IAutoIncrVtbl;

    interface IAutoIncr
    {
        CONST_VTBL struct IAutoIncrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoIncr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAutoIncr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAutoIncr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAutoIncr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAutoIncr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAutoIncr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAutoIncr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAutoIncr_get_SlowCounter(This,pValue)	\
    (This)->lpVtbl -> get_SlowCounter(This,pValue)

#define IAutoIncr_get_FastCounter(This,pValue)	\
    (This)->lpVtbl -> get_FastCounter(This,pValue)

#define IAutoIncr_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAutoIncr_get_SlowCounter_Proxy( 
    IAutoIncr __RPC_FAR * This,
    /* [retval][out] */ WORD __RPC_FAR *pValue);


void __RPC_STUB IAutoIncr_get_SlowCounter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAutoIncr_get_FastCounter_Proxy( 
    IAutoIncr __RPC_FAR * This,
    /* [retval][out] */ WORD __RPC_FAR *pValue);


void __RPC_STUB IAutoIncr_get_FastCounter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IAutoIncr_get__NewEnum_Proxy( 
    IAutoIncr __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IAutoIncr_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAutoIncr_INTERFACE_DEFINED__ */



#ifndef __COMDEMOLib_LIBRARY_DEFINED__
#define __COMDEMOLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: COMDEMOLib
 * at Thu Jul 17 19:43:38 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_COMDEMOLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CAutoIncr;

class CAutoIncr;
#endif
#endif /* __COMDEMOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
