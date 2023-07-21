// dllmain.cpp: DllMain 的实现。

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "lwsoft1_i.h"
#include "dllmain.h"
#include "DXBind.h"
#include "Hook.h"


Clwsoft1Module _AtlModule;

DXBind g_bit;

ULONG_PTR  Onproc = 0;

LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg== WH_CBT)
	{
		MessageBox(0,"鼠标消息","123",MB_OK);
		msg = 0;
		hWnd = 0;
	}
	
	
	
	
	
	
	//switch (msg)
	//{
	//case WM_LBUTTONDOWN:
	//{
	//POINT p = { 0 };
	//p.x = GET_X_LPARAM(lParam);
	//p.y = GET_Y_LPARAM(lParam);
	//	break;
	//}
	//case WM_LBUTTONUP:
	//{
	//	POINT p = { 0 };
	//	p.x = GET_X_LPARAM(lParam);
	//	p.y = GET_Y_LPARAM(lParam);
	//	char ch[30] = { 0 };
	//	_itoa((int)hWnd, ch, 10);
	//	MessageBox(0, ch, "001", MB_OK);
	//	break;
	//}
	//case  WM_MOUSEMOVE:
	//{
	//	char ch[30] = { 0 };
	//	_itoa((int)hWnd, ch, 10);
	//	MessageBox(0,ch,"001",MB_OK);
	//  POINT p = { 0 };
	//  p.x = GET_X_LPARAM(lParam);
	//  p.y = GET_Y_LPARAM(lParam);
	//	break;
	//}
	//case  WM_LBUTTONDBLCLK:
	//{
	//	POINT p = { 0 };
	//	p.x = GET_X_LPARAM(lParam);
	//	p.y = GET_Y_LPARAM(lParam);
	//	break;
	//}
	//default:
	//	break;
	//}
	//m_OEDITProc = 0;
	//这里一定要注意，我们只处理我们想要处理的消息，我们不需要处理的消息放给原来的回调函数处理

	return CallWindowProc((WNDPROC)Onproc, hWnd, msg, wParam, lParam);
}
PMSG t_msg = 0;
LPVOID g_peek = 0;

BOOL procmsg()
{
	PMSG p = (PMSG)(*((ULONG_PTR*)t_msg));
	ULONG Id =p->message;

	if (Id>=0x200&&Id<=0x20F)
	{
		//(*(PMSG)(*((ULONG_PTR*)t_msg))).message = 0;
		//(*(PMSG)(*((ULONG_PTR*)t_msg))).lParam = 0;
		memset((PMSG)(*((ULONG_PTR*)t_msg)), 0, sizeof(MSG));
		return TRUE;
	}
	return FALSE;
}

#if _WIN64
void myProc()
{
	
	myProc1(&t_msg, g_peek, procmsg);
	
}
#else
__declspec(naked) void  __stdcall myProc()
{
	__asm {
		mov t_msg, esp
		add t_msg, 4
		CALL procmsg
		cmp eax, 1
		_emit 75h
		_emit 5
		xor eax, eax
		ret 14h
		mov edi, edi
		push ebp
		mov ebp, esp
		jmp g_peek
	}
}
#endif



// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	//if (dwReason== DLL_PROCESS_ATTACH)
	//{
	////	
	//	Onproc = (ULONG_PTR)SetWindowLongPtr(g_bit.GetProcessMainWnd(GetCurrentProcessId()), GWLP_WNDPROC, (LONG_PTR)EditProc);
	//	//char ch[20] = { 0 };
	//	//_itoa((DWORD64)myProc, ch, 16);
	//	//MessageBox(0,ch,"00",MB_OK);
	//	//g_peek = (LPVOID)((DWORD64)PeekMessageA+5);
	//	g_shook.SetHook(g_bit.GetProcessMainWnd(GetCurrentProcessId()));
	//}

	//if (dwReason == DLL_PROCESS_DETACH)
	//{

	//	//SetWindowLongPtr(g_bit.GetProcessMainWnd(GetCurrentProcessId()), GWLP_WNDPROC, (LONG_PTR)Onproc);
	//	g_shook.UnHook();
	//}
	
	

	return _AtlModule.DllMain(dwReason, lpReserved);
}
