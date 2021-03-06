

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue May 09 21:31:49 2017
 */
/* Compiler settings for FinancialManagementSystem.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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


#ifndef __FinancialManagementSystem_h_h__
#define __FinancialManagementSystem_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFinancialManagementSystem_FWD_DEFINED__
#define __IFinancialManagementSystem_FWD_DEFINED__
typedef interface IFinancialManagementSystem IFinancialManagementSystem;

#endif 	/* __IFinancialManagementSystem_FWD_DEFINED__ */


#ifndef __CFinancialManagementSystemDoc_FWD_DEFINED__
#define __CFinancialManagementSystemDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFinancialManagementSystemDoc CFinancialManagementSystemDoc;
#else
typedef struct CFinancialManagementSystemDoc CFinancialManagementSystemDoc;
#endif /* __cplusplus */

#endif 	/* __CFinancialManagementSystemDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __FinancialManagementSystem_LIBRARY_DEFINED__
#define __FinancialManagementSystem_LIBRARY_DEFINED__

/* library FinancialManagementSystem */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FinancialManagementSystem;

#ifndef __IFinancialManagementSystem_DISPINTERFACE_DEFINED__
#define __IFinancialManagementSystem_DISPINTERFACE_DEFINED__

/* dispinterface IFinancialManagementSystem */
/* [uuid] */ 


EXTERN_C const IID DIID_IFinancialManagementSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BA18314A-6899-448D-ABEC-485ED137CEA5")
    IFinancialManagementSystem : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IFinancialManagementSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFinancialManagementSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFinancialManagementSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFinancialManagementSystem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFinancialManagementSystem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFinancialManagementSystem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFinancialManagementSystem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFinancialManagementSystem * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IFinancialManagementSystemVtbl;

    interface IFinancialManagementSystem
    {
        CONST_VTBL struct IFinancialManagementSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFinancialManagementSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFinancialManagementSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFinancialManagementSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFinancialManagementSystem_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFinancialManagementSystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFinancialManagementSystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFinancialManagementSystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IFinancialManagementSystem_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CFinancialManagementSystemDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("8A419812-8AD8-4A9B-AB86-751FF8F82A27")
CFinancialManagementSystemDoc;
#endif
#endif /* __FinancialManagementSystem_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


