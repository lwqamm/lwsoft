

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for lwsoft1.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __lwsoft1_i_h__
#define __lwsoft1_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IlwObject_FWD_DEFINED__
#define __IlwObject_FWD_DEFINED__
typedef interface IlwObject IlwObject;

#endif 	/* __IlwObject_FWD_DEFINED__ */


#ifndef __lwObject_FWD_DEFINED__
#define __lwObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class lwObject lwObject;
#else
typedef struct lwObject lwObject;
#endif /* __cplusplus */

#endif 	/* __lwObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IlwObject_INTERFACE_DEFINED__
#define __IlwObject_INTERFACE_DEFINED__

/* interface IlwObject */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IlwObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8c063e60-c117-4f11-9a0d-a025c0f96475")
    IlwObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BindWindow( 
            LONG hwnd,
            LONG KeyMouse,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowState( 
            long hwnd,
            long flag,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowTransparent( 
            long hwnd,
            long trans,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowText( 
            long hwnd,
            BSTR title,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowSize( 
            long hwnd,
            long width,
            long hight,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetClientSize( 
            long hwnd,
            long width,
            long height,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveWindow( 
            LONG hwnd,
            LONG x,
            LONG y,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenToClient( 
            LONG hwnd,
            LONG *x,
            LONG *y,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendPaste( 
            LONG hwnd,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClipboard( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetClipboard( 
            BSTR values,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendString( 
            long hwnd,
            BSTR str,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendString2( 
            LONG hwnd,
            BSTR str,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowTitle( 
            LONG hwnd,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowThreadProcessId( 
            long hWnd,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowProcessId( 
            long hwnd,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowProcessPath( 
            LONG hwnd,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowRect( 
            long hwnd,
            LONG *x1,
            LONG *y1,
            LONG *x2,
            LONG *y2,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowClass( 
            long hwnd,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowState( 
            LONG hwnd,
            LONG flag,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSpecialWindow( 
            LONG flag,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindow( 
            long hwnd,
            long flag,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMousePointWindow( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPointWindow( 
            long x,
            long y,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetForegroundWindow( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetForegroundFocus( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClientSize( 
            long hwnd,
            LONG *w,
            LONG *h,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClientRect( 
            LONG hwnd,
            LONG *x1,
            LONG *y1,
            LONG *x2,
            LONG *y2,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindWindowEx( 
            LONG parent,
            BSTR class_name,
            BSTR title,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindWindow( 
            BSTR class_name,
            BSTR title,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumWindowByProcess( 
            BSTR process_name,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumWindowByProcessId( 
            long pid,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumProcess( 
            BSTR name,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumWindow( 
            LONG parent,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPath( 
            BSTR path,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindColor( 
            LONG x1,
            LONG y1,
            LONG w1,
            LONG h1,
            BSTR color,
            double sim,
            LONG *longX,
            LONG *longY,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ver( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetColor( 
            long x,
            long y,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetColorNum( 
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color,
            double sim,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CmpColor( 
            long x,
            long y,
            BSTR color,
            double sim,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Capture( 
            long x,
            long y,
            long w,
            long h,
            BSTR file,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindColorBlock( 
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color,
            double sim,
            long count,
            long width,
            long height,
            LONG *intX,
            LONG *intY,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindPic( 
            LONG x_1,
            LONG y_1,
            LONG w_1,
            LONG h_1,
            BSTR pic_name,
            BSTR delta_color,
            double sim,
            LONG *longX,
            LONG *longY,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindPicEx( 
            LONG x_1,
            LONG y_1,
            LONG w_1,
            LONG h_1,
            BSTR pic_name,
            BSTR delta_color,
            double sim,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bmp32To24( 
            BSTR Filepath,
            BSTR FilepathBak,
            LONG ret,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsDisplayDead( 
            long x,
            long y,
            long w,
            long h,
            long t,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckFontSmooth( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableFontSmooth( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableFontSmooth( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckUAC( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUAC( 
            ULONG enable,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delay( 
            long mis,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delays( 
            long mis_min,
            long mis_max,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExitOs( 
            long type,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableScreenSave( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisablePowerSave( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnablePowerSaveh( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableCloseDisplayAndSleep( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDir( 
            long type,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCpuType( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCpuUsage( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDiskSerial( 
            long index,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplayInfo( 
            BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDPI( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunApp( 
            BSTR path,
            long type,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHDiskCode( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCpuCode( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMainBoardInfoByCmd( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMachineCode( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMachineCodeNoMac( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNetTime( 
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNetTimeByIp( 
            BSTR ip,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOsBuildNumber( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOsType( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTime( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Is64Bit( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsSurrpotVt( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScreenDepth( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScreenDepth( 
            long dmBitsPerPel,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScreenHeight( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScreenWidth( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScreen( 
            long width,
            long height,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastError( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDict( 
            BSTR file,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindStr( 
            long x1,
            long y1,
            long w,
            long h,
            BSTR str1,
            BSTR color_format1,
            double sim,
            LONG *intX,
            LONG *intY,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindStrEx( 
            long x1,
            long y1,
            long w,
            long h,
            BSTR str,
            BSTR color_format,
            double sim,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ocr( 
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color_format,
            double sim,
            /* [retval][out] */ BSTR *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            long x,
            long y,
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LeftClick( 
            /* [retval][out] */ LONG *nret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnBindWindow( 
            /* [retval][out] */ LONG *nret) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IlwObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IlwObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IlwObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IlwObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IlwObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IlwObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IlwObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IlwObject * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BindWindow )( 
            IlwObject * This,
            LONG hwnd,
            LONG KeyMouse,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowState )( 
            IlwObject * This,
            long hwnd,
            long flag,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowTransparent )( 
            IlwObject * This,
            long hwnd,
            long trans,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowText )( 
            IlwObject * This,
            long hwnd,
            BSTR title,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowSize )( 
            IlwObject * This,
            long hwnd,
            long width,
            long hight,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetClientSize )( 
            IlwObject * This,
            long hwnd,
            long width,
            long height,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveWindow )( 
            IlwObject * This,
            LONG hwnd,
            LONG x,
            LONG y,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenToClient )( 
            IlwObject * This,
            LONG hwnd,
            LONG *x,
            LONG *y,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendPaste )( 
            IlwObject * This,
            LONG hwnd,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClipboard )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetClipboard )( 
            IlwObject * This,
            BSTR values,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendString )( 
            IlwObject * This,
            long hwnd,
            BSTR str,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendString2 )( 
            IlwObject * This,
            LONG hwnd,
            BSTR str,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowTitle )( 
            IlwObject * This,
            LONG hwnd,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowThreadProcessId )( 
            IlwObject * This,
            long hWnd,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowProcessId )( 
            IlwObject * This,
            long hwnd,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowProcessPath )( 
            IlwObject * This,
            LONG hwnd,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowRect )( 
            IlwObject * This,
            long hwnd,
            LONG *x1,
            LONG *y1,
            LONG *x2,
            LONG *y2,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowClass )( 
            IlwObject * This,
            long hwnd,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowState )( 
            IlwObject * This,
            LONG hwnd,
            LONG flag,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSpecialWindow )( 
            IlwObject * This,
            LONG flag,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IlwObject * This,
            long hwnd,
            long flag,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMousePointWindow )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPointWindow )( 
            IlwObject * This,
            long x,
            long y,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetForegroundWindow )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetForegroundFocus )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClientSize )( 
            IlwObject * This,
            long hwnd,
            LONG *w,
            LONG *h,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClientRect )( 
            IlwObject * This,
            LONG hwnd,
            LONG *x1,
            LONG *y1,
            LONG *x2,
            LONG *y2,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindWindowEx )( 
            IlwObject * This,
            LONG parent,
            BSTR class_name,
            BSTR title,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindWindow )( 
            IlwObject * This,
            BSTR class_name,
            BSTR title,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumWindowByProcess )( 
            IlwObject * This,
            BSTR process_name,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumWindowByProcessId )( 
            IlwObject * This,
            long pid,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumProcess )( 
            IlwObject * This,
            BSTR name,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumWindow )( 
            IlwObject * This,
            LONG parent,
            BSTR title,
            BSTR class_name,
            LONG filter,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPath )( 
            IlwObject * This,
            BSTR path,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindColor )( 
            IlwObject * This,
            LONG x1,
            LONG y1,
            LONG w1,
            LONG h1,
            BSTR color,
            double sim,
            LONG *longX,
            LONG *longY,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ver )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetColor )( 
            IlwObject * This,
            long x,
            long y,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetColorNum )( 
            IlwObject * This,
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color,
            double sim,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CmpColor )( 
            IlwObject * This,
            long x,
            long y,
            BSTR color,
            double sim,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Capture )( 
            IlwObject * This,
            long x,
            long y,
            long w,
            long h,
            BSTR file,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindColorBlock )( 
            IlwObject * This,
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color,
            double sim,
            long count,
            long width,
            long height,
            LONG *intX,
            LONG *intY,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindPic )( 
            IlwObject * This,
            LONG x_1,
            LONG y_1,
            LONG w_1,
            LONG h_1,
            BSTR pic_name,
            BSTR delta_color,
            double sim,
            LONG *longX,
            LONG *longY,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindPicEx )( 
            IlwObject * This,
            LONG x_1,
            LONG y_1,
            LONG w_1,
            LONG h_1,
            BSTR pic_name,
            BSTR delta_color,
            double sim,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bmp32To24 )( 
            IlwObject * This,
            BSTR Filepath,
            BSTR FilepathBak,
            LONG ret,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsDisplayDead )( 
            IlwObject * This,
            long x,
            long y,
            long w,
            long h,
            long t,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckFontSmooth )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableFontSmooth )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableFontSmooth )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckUAC )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUAC )( 
            IlwObject * This,
            ULONG enable,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delay )( 
            IlwObject * This,
            long mis,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delays )( 
            IlwObject * This,
            long mis_min,
            long mis_max,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExitOs )( 
            IlwObject * This,
            long type,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableScreenSave )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisablePowerSave )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnablePowerSaveh )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableCloseDisplayAndSleep )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDir )( 
            IlwObject * This,
            long type,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCpuType )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCpuUsage )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDiskSerial )( 
            IlwObject * This,
            long index,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplayInfo )( 
            IlwObject * This,
            BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDPI )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunApp )( 
            IlwObject * This,
            BSTR path,
            long type,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHDiskCode )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCpuCode )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMainBoardInfoByCmd )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMachineCode )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMachineCodeNoMac )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNetTime )( 
            IlwObject * This,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNetTimeByIp )( 
            IlwObject * This,
            BSTR ip,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOsBuildNumber )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOsType )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Is64Bit )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsSurrpotVt )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScreenDepth )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScreenDepth )( 
            IlwObject * This,
            long dmBitsPerPel,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScreenHeight )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScreenWidth )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScreen )( 
            IlwObject * This,
            long width,
            long height,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDict )( 
            IlwObject * This,
            BSTR file,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindStr )( 
            IlwObject * This,
            long x1,
            long y1,
            long w,
            long h,
            BSTR str1,
            BSTR color_format1,
            double sim,
            LONG *intX,
            LONG *intY,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindStrEx )( 
            IlwObject * This,
            long x1,
            long y1,
            long w,
            long h,
            BSTR str,
            BSTR color_format,
            double sim,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ocr )( 
            IlwObject * This,
            long x_1,
            long y_1,
            long w_1,
            long h_1,
            BSTR color_format,
            double sim,
            /* [retval][out] */ BSTR *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IlwObject * This,
            long x,
            long y,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LeftClick )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnBindWindow )( 
            IlwObject * This,
            /* [retval][out] */ LONG *nret);
        
        END_INTERFACE
    } IlwObjectVtbl;

    interface IlwObject
    {
        CONST_VTBL struct IlwObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IlwObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IlwObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IlwObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IlwObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IlwObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IlwObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IlwObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IlwObject_BindWindow(This,hwnd,KeyMouse,nret)	\
    ( (This)->lpVtbl -> BindWindow(This,hwnd,KeyMouse,nret) ) 

#define IlwObject_SetWindowState(This,hwnd,flag,nret)	\
    ( (This)->lpVtbl -> SetWindowState(This,hwnd,flag,nret) ) 

#define IlwObject_SetWindowTransparent(This,hwnd,trans,nret)	\
    ( (This)->lpVtbl -> SetWindowTransparent(This,hwnd,trans,nret) ) 

#define IlwObject_SetWindowText(This,hwnd,title,nret)	\
    ( (This)->lpVtbl -> SetWindowText(This,hwnd,title,nret) ) 

#define IlwObject_SetWindowSize(This,hwnd,width,hight,nret)	\
    ( (This)->lpVtbl -> SetWindowSize(This,hwnd,width,hight,nret) ) 

#define IlwObject_SetClientSize(This,hwnd,width,height,nret)	\
    ( (This)->lpVtbl -> SetClientSize(This,hwnd,width,height,nret) ) 

#define IlwObject_MoveWindow(This,hwnd,x,y,nret)	\
    ( (This)->lpVtbl -> MoveWindow(This,hwnd,x,y,nret) ) 

#define IlwObject_ScreenToClient(This,hwnd,x,y,nret)	\
    ( (This)->lpVtbl -> ScreenToClient(This,hwnd,x,y,nret) ) 

#define IlwObject_SendPaste(This,hwnd,nret)	\
    ( (This)->lpVtbl -> SendPaste(This,hwnd,nret) ) 

#define IlwObject_GetClipboard(This,nret)	\
    ( (This)->lpVtbl -> GetClipboard(This,nret) ) 

#define IlwObject_SetClipboard(This,values,nret)	\
    ( (This)->lpVtbl -> SetClipboard(This,values,nret) ) 

#define IlwObject_SendString(This,hwnd,str,nret)	\
    ( (This)->lpVtbl -> SendString(This,hwnd,str,nret) ) 

#define IlwObject_SendString2(This,hwnd,str,nret)	\
    ( (This)->lpVtbl -> SendString2(This,hwnd,str,nret) ) 

#define IlwObject_GetWindowTitle(This,hwnd,nret)	\
    ( (This)->lpVtbl -> GetWindowTitle(This,hwnd,nret) ) 

#define IlwObject_GetWindowThreadProcessId(This,hWnd,nret)	\
    ( (This)->lpVtbl -> GetWindowThreadProcessId(This,hWnd,nret) ) 

#define IlwObject_GetWindowProcessId(This,hwnd,nret)	\
    ( (This)->lpVtbl -> GetWindowProcessId(This,hwnd,nret) ) 

#define IlwObject_GetWindowProcessPath(This,hwnd,nret)	\
    ( (This)->lpVtbl -> GetWindowProcessPath(This,hwnd,nret) ) 

#define IlwObject_GetWindowRect(This,hwnd,x1,y1,x2,y2,nret)	\
    ( (This)->lpVtbl -> GetWindowRect(This,hwnd,x1,y1,x2,y2,nret) ) 

#define IlwObject_GetWindowClass(This,hwnd,nret)	\
    ( (This)->lpVtbl -> GetWindowClass(This,hwnd,nret) ) 

#define IlwObject_GetWindowState(This,hwnd,flag,nret)	\
    ( (This)->lpVtbl -> GetWindowState(This,hwnd,flag,nret) ) 

#define IlwObject_GetSpecialWindow(This,flag,nret)	\
    ( (This)->lpVtbl -> GetSpecialWindow(This,flag,nret) ) 

#define IlwObject_GetWindow(This,hwnd,flag,nret)	\
    ( (This)->lpVtbl -> GetWindow(This,hwnd,flag,nret) ) 

#define IlwObject_GetMousePointWindow(This,nret)	\
    ( (This)->lpVtbl -> GetMousePointWindow(This,nret) ) 

#define IlwObject_GetPointWindow(This,x,y,nret)	\
    ( (This)->lpVtbl -> GetPointWindow(This,x,y,nret) ) 

#define IlwObject_GetForegroundWindow(This,nret)	\
    ( (This)->lpVtbl -> GetForegroundWindow(This,nret) ) 

#define IlwObject_GetForegroundFocus(This,nret)	\
    ( (This)->lpVtbl -> GetForegroundFocus(This,nret) ) 

#define IlwObject_GetClientSize(This,hwnd,w,h,nret)	\
    ( (This)->lpVtbl -> GetClientSize(This,hwnd,w,h,nret) ) 

#define IlwObject_GetClientRect(This,hwnd,x1,y1,x2,y2,nret)	\
    ( (This)->lpVtbl -> GetClientRect(This,hwnd,x1,y1,x2,y2,nret) ) 

#define IlwObject_FindWindowEx(This,parent,class_name,title,nret)	\
    ( (This)->lpVtbl -> FindWindowEx(This,parent,class_name,title,nret) ) 

#define IlwObject_FindWindow(This,class_name,title,nret)	\
    ( (This)->lpVtbl -> FindWindow(This,class_name,title,nret) ) 

#define IlwObject_EnumWindowByProcess(This,process_name,title,class_name,filter,nret)	\
    ( (This)->lpVtbl -> EnumWindowByProcess(This,process_name,title,class_name,filter,nret) ) 

#define IlwObject_EnumWindowByProcessId(This,pid,title,class_name,filter,nret)	\
    ( (This)->lpVtbl -> EnumWindowByProcessId(This,pid,title,class_name,filter,nret) ) 

#define IlwObject_EnumProcess(This,name,nret)	\
    ( (This)->lpVtbl -> EnumProcess(This,name,nret) ) 

#define IlwObject_EnumWindow(This,parent,title,class_name,filter,nret)	\
    ( (This)->lpVtbl -> EnumWindow(This,parent,title,class_name,filter,nret) ) 

#define IlwObject_SetPath(This,path,nret)	\
    ( (This)->lpVtbl -> SetPath(This,path,nret) ) 

#define IlwObject_FindColor(This,x1,y1,w1,h1,color,sim,longX,longY,nret)	\
    ( (This)->lpVtbl -> FindColor(This,x1,y1,w1,h1,color,sim,longX,longY,nret) ) 

#define IlwObject_Ver(This,nret)	\
    ( (This)->lpVtbl -> Ver(This,nret) ) 

#define IlwObject_GetColor(This,x,y,nret)	\
    ( (This)->lpVtbl -> GetColor(This,x,y,nret) ) 

#define IlwObject_GetColorNum(This,x_1,y_1,w_1,h_1,color,sim,nret)	\
    ( (This)->lpVtbl -> GetColorNum(This,x_1,y_1,w_1,h_1,color,sim,nret) ) 

#define IlwObject_CmpColor(This,x,y,color,sim,nret)	\
    ( (This)->lpVtbl -> CmpColor(This,x,y,color,sim,nret) ) 

#define IlwObject_Capture(This,x,y,w,h,file,nret)	\
    ( (This)->lpVtbl -> Capture(This,x,y,w,h,file,nret) ) 

#define IlwObject_FindColorBlock(This,x_1,y_1,w_1,h_1,color,sim,count,width,height,intX,intY,nret)	\
    ( (This)->lpVtbl -> FindColorBlock(This,x_1,y_1,w_1,h_1,color,sim,count,width,height,intX,intY,nret) ) 

#define IlwObject_FindPic(This,x_1,y_1,w_1,h_1,pic_name,delta_color,sim,longX,longY,nret)	\
    ( (This)->lpVtbl -> FindPic(This,x_1,y_1,w_1,h_1,pic_name,delta_color,sim,longX,longY,nret) ) 

#define IlwObject_FindPicEx(This,x_1,y_1,w_1,h_1,pic_name,delta_color,sim,nret)	\
    ( (This)->lpVtbl -> FindPicEx(This,x_1,y_1,w_1,h_1,pic_name,delta_color,sim,nret) ) 

#define IlwObject_Bmp32To24(This,Filepath,FilepathBak,ret,nret)	\
    ( (This)->lpVtbl -> Bmp32To24(This,Filepath,FilepathBak,ret,nret) ) 

#define IlwObject_IsDisplayDead(This,x,y,w,h,t,nret)	\
    ( (This)->lpVtbl -> IsDisplayDead(This,x,y,w,h,t,nret) ) 

#define IlwObject_CheckFontSmooth(This,nret)	\
    ( (This)->lpVtbl -> CheckFontSmooth(This,nret) ) 

#define IlwObject_DisableFontSmooth(This,nret)	\
    ( (This)->lpVtbl -> DisableFontSmooth(This,nret) ) 

#define IlwObject_EnableFontSmooth(This,nret)	\
    ( (This)->lpVtbl -> EnableFontSmooth(This,nret) ) 

#define IlwObject_CheckUAC(This,nret)	\
    ( (This)->lpVtbl -> CheckUAC(This,nret) ) 

#define IlwObject_SetUAC(This,enable,nret)	\
    ( (This)->lpVtbl -> SetUAC(This,enable,nret) ) 

#define IlwObject_Delay(This,mis,nret)	\
    ( (This)->lpVtbl -> Delay(This,mis,nret) ) 

#define IlwObject_Delays(This,mis_min,mis_max,nret)	\
    ( (This)->lpVtbl -> Delays(This,mis_min,mis_max,nret) ) 

#define IlwObject_ExitOs(This,type,nret)	\
    ( (This)->lpVtbl -> ExitOs(This,type,nret) ) 

#define IlwObject_DisableScreenSave(This,nret)	\
    ( (This)->lpVtbl -> DisableScreenSave(This,nret) ) 

#define IlwObject_DisablePowerSave(This,nret)	\
    ( (This)->lpVtbl -> DisablePowerSave(This,nret) ) 

#define IlwObject_EnablePowerSaveh(This,nret)	\
    ( (This)->lpVtbl -> EnablePowerSaveh(This,nret) ) 

#define IlwObject_DisableCloseDisplayAndSleep(This,nret)	\
    ( (This)->lpVtbl -> DisableCloseDisplayAndSleep(This,nret) ) 

#define IlwObject_GetDir(This,type,nret)	\
    ( (This)->lpVtbl -> GetDir(This,type,nret) ) 

#define IlwObject_GetCpuType(This,nret)	\
    ( (This)->lpVtbl -> GetCpuType(This,nret) ) 

#define IlwObject_GetCpuUsage(This,nret)	\
    ( (This)->lpVtbl -> GetCpuUsage(This,nret) ) 

#define IlwObject_GetDiskSerial(This,index,nret)	\
    ( (This)->lpVtbl -> GetDiskSerial(This,index,nret) ) 

#define IlwObject_GetDisplayInfo(This,nret)	\
    ( (This)->lpVtbl -> GetDisplayInfo(This,nret) ) 

#define IlwObject_GetDPI(This,nret)	\
    ( (This)->lpVtbl -> GetDPI(This,nret) ) 

#define IlwObject_RunApp(This,path,type,nret)	\
    ( (This)->lpVtbl -> RunApp(This,path,type,nret) ) 

#define IlwObject_GetHDiskCode(This,nret)	\
    ( (This)->lpVtbl -> GetHDiskCode(This,nret) ) 

#define IlwObject_GetCpuCode(This,nret)	\
    ( (This)->lpVtbl -> GetCpuCode(This,nret) ) 

#define IlwObject_GetMainBoardInfoByCmd(This,nret)	\
    ( (This)->lpVtbl -> GetMainBoardInfoByCmd(This,nret) ) 

#define IlwObject_GetMachineCode(This,nret)	\
    ( (This)->lpVtbl -> GetMachineCode(This,nret) ) 

#define IlwObject_GetMachineCodeNoMac(This,nret)	\
    ( (This)->lpVtbl -> GetMachineCodeNoMac(This,nret) ) 

#define IlwObject_GetNetTime(This,nret)	\
    ( (This)->lpVtbl -> GetNetTime(This,nret) ) 

#define IlwObject_GetNetTimeByIp(This,ip,nret)	\
    ( (This)->lpVtbl -> GetNetTimeByIp(This,ip,nret) ) 

#define IlwObject_GetOsBuildNumber(This,nret)	\
    ( (This)->lpVtbl -> GetOsBuildNumber(This,nret) ) 

#define IlwObject_GetOsType(This,nret)	\
    ( (This)->lpVtbl -> GetOsType(This,nret) ) 

#define IlwObject_GetTime(This,nret)	\
    ( (This)->lpVtbl -> GetTime(This,nret) ) 

#define IlwObject_Is64Bit(This,nret)	\
    ( (This)->lpVtbl -> Is64Bit(This,nret) ) 

#define IlwObject_IsSurrpotVt(This,nret)	\
    ( (This)->lpVtbl -> IsSurrpotVt(This,nret) ) 

#define IlwObject_GetScreenDepth(This,nret)	\
    ( (This)->lpVtbl -> GetScreenDepth(This,nret) ) 

#define IlwObject_SetScreenDepth(This,dmBitsPerPel,nret)	\
    ( (This)->lpVtbl -> SetScreenDepth(This,dmBitsPerPel,nret) ) 

#define IlwObject_GetScreenHeight(This,nret)	\
    ( (This)->lpVtbl -> GetScreenHeight(This,nret) ) 

#define IlwObject_GetScreenWidth(This,nret)	\
    ( (This)->lpVtbl -> GetScreenWidth(This,nret) ) 

#define IlwObject_SetScreen(This,width,height,nret)	\
    ( (This)->lpVtbl -> SetScreen(This,width,height,nret) ) 

#define IlwObject_GetLastError(This,nret)	\
    ( (This)->lpVtbl -> GetLastError(This,nret) ) 

#define IlwObject_SetDict(This,file,nret)	\
    ( (This)->lpVtbl -> SetDict(This,file,nret) ) 

#define IlwObject_FindStr(This,x1,y1,w,h,str1,color_format1,sim,intX,intY,nret)	\
    ( (This)->lpVtbl -> FindStr(This,x1,y1,w,h,str1,color_format1,sim,intX,intY,nret) ) 

#define IlwObject_FindStrEx(This,x1,y1,w,h,str,color_format,sim,nret)	\
    ( (This)->lpVtbl -> FindStrEx(This,x1,y1,w,h,str,color_format,sim,nret) ) 

#define IlwObject_Ocr(This,x_1,y_1,w_1,h_1,color_format,sim,nret)	\
    ( (This)->lpVtbl -> Ocr(This,x_1,y_1,w_1,h_1,color_format,sim,nret) ) 

#define IlwObject_MoveTo(This,x,y,nret)	\
    ( (This)->lpVtbl -> MoveTo(This,x,y,nret) ) 

#define IlwObject_LeftClick(This,nret)	\
    ( (This)->lpVtbl -> LeftClick(This,nret) ) 

#define IlwObject_UnBindWindow(This,nret)	\
    ( (This)->lpVtbl -> UnBindWindow(This,nret) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IlwObject_INTERFACE_DEFINED__ */



#ifndef __lwsoft1Lib_LIBRARY_DEFINED__
#define __lwsoft1Lib_LIBRARY_DEFINED__

/* library lwsoft1Lib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_lwsoft1Lib;

EXTERN_C const CLSID CLSID_lwObject;

#ifdef __cplusplus

class DECLSPEC_UUID("fc598ba8-6f6a-464e-b1db-06d60265f708")
lwObject;
#endif
#endif /* __lwsoft1Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


