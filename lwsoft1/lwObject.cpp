// lwObject.cpp: ClwObject 的实现

#include "pch.h"
#include "lwObject.h"
#include "LwMutexlock.h"
#include <intrin.h>

#include <comdef.h>
#include <comutil.h>

#pragma comment(lib, "comsupp.lib") 
//SendString互斥2
TsMutex gDXSendString2Mutex(LW_SENDSTRING2EVEN);//
//EnumWindowByProcess互斥						
TsMutex gDXEnumWindowByProcessMutex(LW_ENUMWINDOWBYPROCESSEVEN);
//EnumWindowByProcessId互斥
TsMutex gDXEnumWindowByProcessIdMutex(LW_ENUMWINDOWBYPROCESSEVENID);
//SendStringIme互斥
TsMutex gDXSendStringImeMutex(LW_SENDSTRINGIMEEVEN);\
//Ocr互斥						
TsMutex gDXOcrMutex(LW_OCREVEN);
//FindStr互斥						
TsMutex gDXFindStrMutex(LW_FINDSTREVEN);
//FindPic互斥		  
TsMutex gDXFindPicMutex(LW_FINDPICEVEN);
// ClwObject
#pragma warning(disable:4996)
STDMETHODIMP_(HRESULT __stdcall) ClwObject::BindWindow(LONG hwnd, LONG KeyMouse, LONG* nret)
{
	*nret = gDxObj.Bind(hwnd, KeyMouse);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::UnBindWindow( LONG* nret)
{
	*nret = gDxObj.UnBindWindow();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetWindowState(long hwnd, long flag, LONG* nret)
{
	*nret = gDxObj.SetWindowState(hwnd, flag);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetWindowTransparent(long hwnd, long trans, LONG* nret)
{
	*nret = gDxObj.SetWindowTransparent(hwnd, trans);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetWindowText(long hwnd, BSTR title, LONG* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	}
	char* title1 = _com_util::ConvertBSTRToString(title);
	*nret = ::SetWindowText((HWND)hwnd, title1);
delete[] title1;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetWindowSize(long hwnd, long width, long hight, LONG* nret)
{
	*nret = gDxObj.SetWindowSize(hwnd, width, hight, 1);
	return S_OK;
}

long ClwObject::SetClientSize(long hwnd, long width, long height, LONG* nret)
{
	*nret = gDxObj.SetWindowSize(hwnd, width, height);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::MoveWindow(LONG hwnd, LONG x, LONG y, LONG* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	}
	RECT winrect;
	::GetWindowRect((HWND)hwnd, &winrect);
	int width = winrect.right - winrect.left;
	int hight = winrect.bottom - winrect.top;

		*nret = ::MoveWindow((HWND)hwnd, x, y, width, hight, false);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::ScreenToClient(LONG hwnd, LONG* x, LONG* y, LONG* nret)
{
	// TODO: 在此添加实现代码

	POINT point; 
	point.x = *(int*)*x;
	point.y = *(int*)*y;
	long ret = ::ScreenToClient((HWND)hwnd, &point);
	*nret = ret;
	*(int*)*x = point.x;
	*(int*)*y = point.y;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SendPaste(LONG hwnd, LONG* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	} 
	*nret = gDxObj.SendPaste(hwnd);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetClipboard( BSTR* nret)
{
	char* t_ch = 0;
	gDxObj.GetClipboard((LPCSTR*)&t_ch);
	CComBSTR newbstr;
	newbstr.Append(t_ch);
	newbstr.CopyTo(nret);
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetClipboard(BSTR values, LONG* nret)
{
	if ((DWORD64)values < +0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	char* t_ch=_com_util::ConvertBSTRToString(values);

	*nret = gDxObj.SetClipboard(t_ch);
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SendString(long hwnd, BSTR str, LONG* nret)
{
	if ((DWORD64)str<+0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	char* t_ch = _com_util::ConvertBSTRToString(str);
	*nret = gDxObj.SendString(hwnd, t_ch);
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SendString2(LONG hwnd, BSTR str, LONG* nret)
{
	// TODO: 在此添加实现代码
	if (!hwnd|| (DWORD64)str<=0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXSendString2Mutex);

	char* t_ch = _com_util::ConvertBSTRToString(str);

	int len = strlen(t_ch);
	PUCHAR p = (PUCHAR)t_ch;
	long nretl = 0;
	for (int i = 0; i < len; i++)
	{
		 ::PostMessageA((HWND)hwnd, WM_CHAR, (WPARAM)p[i], 0);
		 nretl = 1;
		Sleep(1);
	}
	
	*nret = nretl;
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowTitle(LONG hwnd, BSTR* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	}
	int len = ::GetWindowTextLengthA((HWND)hwnd)+2;
	char* t_ch = new char[len + 1];
	memset(t_ch,0,len+1);
	int ret=::GetWindowText((HWND)hwnd, t_ch, len);

	CComBSTR newbstr;
	newbstr.Append(t_ch);
	newbstr.CopyTo(nret);
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowThreadProcessId(long hWnd, LONG* nret)
{
	DWORD  pid = gDxObj.GetWindowProcessId(hWnd);
	if (!pid)
	{
		*nret = 0;
		return S_OK;
	}


	*nret = ::GetWindowThreadProcessId((HWND)hWnd, &pid);
	return S_OK;
}

long ClwObject::GetWindowProcessId(long hwnd, LONG* nret)
{
	*nret = gDxObj.GetWindowProcessId(hwnd);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowProcessPath(LONG hwnd, BSTR* nret)
{
	char* t_ch = 0;
	gDxObj.GetWindowProcessPath(hwnd,(LPCSTR*)&t_ch);
	if (!t_ch)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(t_ch);
	newbstr.CopyTo(nret);
	delete[] t_ch;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowRect(long hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2, LONG* nret)
{
	RECT rct = {0};
	int ret=::GetWindowRect((HWND)hwnd, &rct);
	*(int*)x1 = rct.left;
	*(int*)y1 = rct.top;
	*(int*)x2 = rct.right;
	*(int*)y2 = rct.bottom;


	*nret = ret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowClass(long hwnd, BSTR* nret)
{
	if (!hwnd)
	{
		*nret = 0;
		return S_OK;
	}
	char* chr = new char[MAX_PATH];
	memset(chr, 0, MAX_PATH);
	int len = ::GetClassName((HWND)hwnd, chr, MAX_PATH);
		if (!len)
		{
			delete[] chr;
			*nret = 0;
			return S_OK;
		}
	CComBSTR newbstr;
	newbstr.Append(chr);
	newbstr.CopyTo(nret);
	delete[] chr;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindowState(LONG hwnd, LONG flag, LONG* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	}

	*nret = gDxObj.GetWindowState(hwnd, flag);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetSpecialWindow(LONG flag, LONG* nret)
{
	long rethwnd = 0;
	switch (flag)
	{
	case 0:
	{
		rethwnd = (LONG)GetDesktopWindow();
		break;
	}
	case 1:
	{
		rethwnd = (LONG)::FindWindowW(L"Shell_TrayWnd", NULL);
		break;
	}
	default:
		break;
	}


	*nret = rethwnd;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetWindow(long hwnd, long flag, LONG* nret)
{
	if (hwnd<=110)
	{
		*nret = 0;
		return S_OK;
	}
	HWND wnd = (HWND)hwnd;
	if (IsWindow(wnd) == false)
		return 0;

	switch (flag)
	{
	case 0:     //获取父窗口
	{
		*nret = (LONG)::GetParent(wnd);
		return S_OK;
	}
	case 1:     //获取第一个儿子窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_CHILD);
		return S_OK;
	}
	case 2:     //获取First 窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_HWNDFIRST);
		return S_OK;
	}
	case 3:    //获取Last窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_HWNDLAST);
		return S_OK;
	}
	case 4:    //获取下一个窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_HWNDNEXT);
		return S_OK;
	}
	case 5:   //获取上一个窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_HWNDPREV);
		return S_OK;
	} 
	case 6:   //获取拥有者窗口
	{
		*nret = (LONG)::GetWindow(wnd, GW_OWNER);
		return S_OK;
	}
	case 7:  //获取顶层窗口
	{	
	*nret = (long)::GetForegroundWindow();
	return S_OK;
	}
	default:
		break;
	}

	return 0;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetMousePointWindow(LONG* nret)
{
	*nret = gDxObj.GetMousePointWindow();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetPointWindow(long x, long y, LONG* nret)
{
	*nret = gDxObj.GetMousePointWindow(x, y);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetForegroundWindow(LONG* nret)
{
	*nret = (LONG)::GetForegroundWindow();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetForegroundFocus(LONG* nret)
{
	*nret = (LONG)::GetFocus();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetForegroundFocus(long hwnd, LONG* nret)
{
	*nret = (long)::SetFocus((HWND)hwnd);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetClientSize(long hwnd, LONG* w, LONG* h, LONG* nret)
{
	if ((DWORD64)w<=0x10000|| (DWORD64)h<=0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	bool bret = false;
	RECT clientrect;
	if (IsWindow((HWND)hwnd))
	{
		::GetClientRect((HWND)hwnd, &clientrect);
		*(long*)w = clientrect.right - clientrect.left;
		*(long*)h = clientrect.bottom - clientrect.top;
		bret = true;
	}

	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetClientRect(LONG hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2, LONG* nret)
{
	if ((DWORD64)x1<=0x10000|| (DWORD64)y1<=0x10000|| (DWORD64)x2<=0x10000|| (DWORD64)y2<=0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	bool bret = false;
	RECT clientrect;
	if (IsWindow((HWND)hwnd))
	{
		::GetClientRect((HWND)hwnd, &clientrect);
		POINT point;
		point.x = clientrect.left;
		point.y = clientrect.top;
		::ClientToScreen((HWND)hwnd, &point);
		*(long*)x1 = point.x;
		*(long*)y1 = point.y;
		point.x = clientrect.right;
		point.y = clientrect.bottom;
		::ClientToScreen((HWND)hwnd, &point);
		*(long*)x2 = point.x;
		*(long*)y2 = point.y;
		bret = true;
	}

	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindWindowEx(LONG parent, BSTR class_name1, BSTR title1, LONG* nret)
{
	
	char* class_name= _com_util::ConvertBSTRToString(class_name1);
	char* title = _com_util::ConvertBSTRToString(title1);
	bool bret = false;
	LONG rethwnd = 0;
	HWND p = NULL;
	if (parent == 0)
		p = ::GetWindow(GetDesktopWindow(), GW_CHILD); //获取桌面窗口的子窗口
	else
		p = ::GetWindow((HWND)parent, GW_CHILD); //获取桌面窗口的子窗口
	if (p == NULL)
	{
		*nret = bret;
		return S_OK;
	}
	p = ::GetWindow(p, GW_HWNDFIRST);
	while (p != NULL)
	{
		if (::IsWindowVisible(p) && ::GetWindow(p, GW_OWNER) == 0)
		{
			if (strlen(class_name) < 1 && strlen(title) < 1)
			{
				rethwnd = (LONG)p;
				bret = true;
				break;
			}
			else
			{//strlen((char*)class_name) >= 1 && strfindclass) || strlen((char*)title) >= 1 && strfindtitle)
				char WindowClassName[MAX_PATH] = { 0 };
				::GetClassNameA(p, WindowClassName, MAX_PATH);
				char WindowTitle[MAX_PATH] = { 0 };
				::GetWindowTextA(p, WindowTitle, MAX_PATH);
				if (strlen(WindowClassName) > 1 && strlen(WindowTitle) > 1)
				{
					char* strfindclass = strstr(WindowClassName, (char*)class_name);   //模糊匹配
					char* strfindtitle = strstr(WindowTitle, (char*)title);   //模糊匹配
					if (strlen((char*)class_name) >= 1&& strfindclass|| strlen((char*)title) >= 1 && strfindtitle)
					{
						rethwnd = (LONG)p;
						bret = true;
						break;
					}
				}
			}
		}
		p = ::GetWindow(p, GW_HWNDNEXT);   //获取下一个窗口
	}

	*nret = rethwnd;
	delete[] class_name;
	delete[] title;

	return S_OK;

}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindWindow(BSTR class_name1, BSTR title1, LONG* nret)
{
	char* class_name = _com_util::ConvertBSTRToString(class_name1);
	char* title = _com_util::ConvertBSTRToString(title1);
	*nret = gDxObj.FindWindow((LPCSTR)class_name, (LPCSTR)title);
	delete[] class_name;
	delete[] title;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnumWindowByProcess(BSTR process_name1, BSTR title1, BSTR	 class_name1, LONG filter, BSTR* nret)
{
	if (filter<1)
	{
		*nret = 0;
		return S_OK;
	}
	// TODO: 在此添加实现代码
	LwMutexlock ts_mutexlock(&gDXEnumWindowByProcessMutex);
	

	char* process_name = _com_util::ConvertBSTRToString(process_name1);
	char* title = _com_util::ConvertBSTRToString(title1);
	char* class_name = _com_util::ConvertBSTRToString(class_name1);
	char* outbf = 0;

	gDxObj.lwEnumWindow((LPCSTR)process_name, (LPCSTR)title, (LPCSTR)class_name,filter, (LPCSTR*)&outbf);
	delete[] class_name;
	delete[] title;
	delete[] process_name;
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnumWindowByProcessId(long pid, BSTR title1, BSTR class_name1, LONG filter,  BSTR* nret)
{
	if (!pid|| filter<1)
	{
		*nret = 0;
		return S_OK;
	}

	LwMutexlock ts_mutexlock(&gDXEnumWindowByProcessIdMutex);

	char* title = _com_util::ConvertBSTRToString(title1);
	char* class_name = _com_util::ConvertBSTRToString(class_name1);
	char* outbf = 0;
	 gDxObj.lwEnumWindowId(pid,(LPCSTR)title, (LPCSTR)class_name,filter, (LPCSTR*)&outbf);
	 delete[] class_name;
	 delete[] title;
	 if (!outbf)
	 {
		 *nret = 0;
		 return S_OK;
	 }
	 CComBSTR newbstr;
	 newbstr.Append(outbf);
	 newbstr.CopyTo(nret);
	 delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnumProcess(BSTR name1, BSTR* nret)
{
	char* name = _com_util::ConvertBSTRToString(name1);

	char* outbf = 0;
	 gDxObj.EnumProcess((LPCSTR)name, (LPCSTR*)&outbf);
	delete[] name;
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnumWindow(LONG parent, BSTR title1, BSTR class_name1, LONG filter, BSTR* nret)
{
	if (filter<1)
	{
		*nret = 0;
		return S_OK;
	}
	char* title = _com_util::ConvertBSTRToString(title1);
	char* class_name = _com_util::ConvertBSTRToString(class_name1);

	char* outbf = 0;
   gDxObj.EnumWindow(parent, (LPCSTR)title, (LPCSTR)class_name,filter, (LPCSTR*)&outbf);
   delete[] class_name;
   delete[] title;
   if (!outbf)
   {
	   *nret = 0;
	   return S_OK;
   }
   CComBSTR newbstr;
   newbstr.Append(outbf);
   newbstr.CopyTo(nret);
   delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetPath(BSTR path1, LONG* nret)
{
	char* path = _com_util::ConvertBSTRToString(path1);
		*nret = gDxObj.lwSetpath((LPCSTR)path);
		delete[] path;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindColor(LONG x1, LONG y1, LONG w1, LONG h1, BSTR color1, double sim, LONG* longX, LONG* longY, LONG* nret)
{
	if ((DWORD64)longY <= 0x10000 || (DWORD64)longX <= 0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);

	char* color = _com_util::ConvertBSTRToString(color1);
	*nret = gDxObj.lwFindColor(x1, y1, w1, h1, (LPCSTR)color, sim, (long*)(*(LONGLONG*)longX), (long*)(*(LONGLONG*)longY));
	delete[] color;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetColor(long x, long y, BSTR* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	char* outbf = 0;
	gDxObj.GetColor(x,y,(LPCSTR*)&outbf);
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetColorNum(long x_1, long y_1, long w_1, long h_1, BSTR color1, double sim, LONG* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	char* color = _com_util::ConvertBSTRToString(color1);
	*nret = gDxObj.GetColorNum(x_1, y_1, w_1, h_1, color, sim);
	delete[] color;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::CmpColor(long x, long y, BSTR color1, double sim, LONG* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	char* color = _com_util::ConvertBSTRToString(color1);
	*nret = gDxObj.CmpColor(x, y, (LPCSTR)color, sim);
	delete[] color;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::Capture(long x, long y, long w, long h, BSTR file1, LONG* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	char* file = _com_util::ConvertBSTRToString(file1);
	*nret= gDxObj.Capture(x,y,w,h,(LPCSTR)file);
	delete[] file;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindColorBlock(long x_1, long y_1, long w_1, long h_1, BSTR color1, double sim, long count, long width, long height, LONG* intX, LONG* intY, LONG* nret)
{
	if ((DWORD64)intX<=0x10000|| (DWORD64)intY <= 0x10000)
	{
		*(LONG*)intX = -1;
		*(LONG*)intY = -1;
		*nret = 0;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	char* color = _com_util::ConvertBSTRToString(color1);
	*nret = gDxObj.FindColorBlock(x_1, y_1, w_1, h_1, (LPCSTR)color, sim, count, width, height, (long*)(*(LONGLONG*)intX), (long*)(*(LONGLONG*)intY));
	delete[] color;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, BSTR pic_name1, BSTR delta_color1, double sim, LONG* longX, LONG* longY, LONG* nret)
{
	if ((DWORD64)longY <= 0x10000 || (DWORD64)longX <= 0x10000 )
	{
		*nret = 0;
		*(LONG*)longX = -1;
		*(LONG*)longY = -1;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);

	char* delta_color = _com_util::ConvertBSTRToString(delta_color1);
	char* pic_name = _com_util::ConvertBSTRToString(pic_name1);
	*nret = gDxObj.lwFindPic(x_1, y_1, w_1, h_1, (LPCSTR)pic_name, (LPCSTR)delta_color, sim, (long*)(*(LONGLONG*)longX), (long*)(*(LONGLONG*)longY));
	delete[] delta_color;
	delete[] pic_name;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindPicEx(LONG x_1, LONG y_1, LONG w_1, LONG h_1, BSTR pic_name1, BSTR delta_color1, double sim, BSTR* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);

	char* delta_color = _com_util::ConvertBSTRToString(delta_color1);
	char* pic_name = _com_util::ConvertBSTRToString(pic_name1);

	char* outbf = 0;

	gDxObj.lwFindPicEx(x_1, y_1, w_1, h_1, (LPCSTR)pic_name, (LPCSTR)delta_color, sim, (LPVOID)&outbf);
	delete[] delta_color;
	delete[] pic_name;
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::Bmp32To24(BSTR Filepath1, BSTR FilepathBak1, LONG ret, LONG* nret)
{
	if ((DWORD64)Filepath1 <= 0x10000 || (DWORD64)FilepathBak1 <= 0x10000 )
	{
		*nret = 0;
		return S_OK;
	}
	char* Filepath = _com_util::ConvertBSTRToString(Filepath1);
	char* FilepathBak = _com_util::ConvertBSTRToString(FilepathBak1);
	*nret = gDxObj.lwBmp32To24((LPCSTR)Filepath, (LPCSTR)FilepathBak, ret);
	delete[] Filepath;
	delete[] FilepathBak;
	return S_OK;
}

STDMETHODIMP ClwObject::Ver(BSTR* nret)
{
	// TODO: 在此添加实现代码

	   CComBSTR newbstr;
	   newbstr.Append(LW_VERSION);
	   newbstr.CopyTo(nret);
	   return S_OK;

}

STDMETHODIMP ClwObject::IsDisplayDead(long x, long y, long w, long h, long t, LONG* nret)
{
	LwMutexlock ts_mutexlock(&gDXFindPicMutex);
	long ret = gDxObj.IsDisplayDead(x, y, w, h, t);
	*nret = ret;
	return S_OK;
}


STDMETHODIMP ClwObject::CheckFontSmooth(LONG* nret)
{
	HKEY Reg_type = HKEY_LOCAL_MACHINE;
	HKEY hKey = NULL;
	char tempstr[MAX_PATH * 2] = { 0 };
	DWORD size = MAX_PATH * sizeof(char), dwType = 0;
	LONG bret = 0;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_WRITE | KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKey, "FontSmoothing", NULL, &dwType, (LPBYTE)tempstr, &size) == ERROR_SUCCESS)
		{
			if (atoi(tempstr) == 2)
				bret = 1;
		}

	}
	
	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::DisableFontSmooth(LONG* nret)
{
	// TODO: 在此添加实现代码

	HKEY Reg_type = HKEY_LOCAL_MACHINE;
	HKEY hKey = NULL;
	LONG bret = 0;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_WRITE | KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if (RegSetValueExA(hKey, "FontSmoothing", NULL, REG_SZ, (LPBYTE)"0", sizeof(char) * 2) == ERROR_SUCCESS)
			bret = 1;
	}
	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnableFontSmooth(LONG* nret)
{
	HKEY Reg_type = HKEY_LOCAL_MACHINE;
	HKEY hKey = NULL;
	LONG bret = 0;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_WRITE | KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if (RegSetValueExA(hKey, "FontSmoothing", NULL, REG_SZ, (LPBYTE)"1", sizeof(char) * 2) == ERROR_SUCCESS)
			bret = 1;
	}
	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::CheckUAC(LONG* nret)
{
	// TODO: 在此添加实现代码
	HKEY Reg_type = HKEY_LOCAL_MACHINE;
	HKEY hKey = NULL;
	DWORD size = sizeof(DWORD), dwType = 0, retvalue = 0;
	LONG bret = 0;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_WRITE | KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKey, "ConsentPromptBehaviorAdmin", NULL, &dwType, (LPBYTE)&retvalue, &size) == ERROR_SUCCESS)
		{
			if (retvalue != 0)
				bret = 1;
		}

	}

	*nret = bret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetUAC(ULONG enable, LONG* nret)
{
	// TODO: 在此添加实现代码
	HKEY Reg_type = HKEY_LOCAL_MACHINE;
	HKEY hKey = NULL;
	LONG bret = 0;
	DWORD vlaue = 0;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_WRITE | KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if (enable == 0)//关闭
		{
			if (RegSetValueExA(hKey, "ConsentPromptBehaviorAdmin", NULL, REG_DWORD, (LPBYTE)&vlaue, sizeof(DWORD)) == ERROR_SUCCESS)
				bret = 1;
		}
		else//打开
		{
			vlaue = 2;
			if (RegSetValueExA(hKey, "ConsentPromptBehaviorAdmin", NULL, REG_DWORD, (LPBYTE)&vlaue, sizeof(DWORD)) == ERROR_SUCCESS)
				bret = 1;
		}

	}

	*nret = bret;
	return S_OK;
}

STDMETHODIMP ClwObject::Delay(long mis, LONG* nret)
{
	if (mis<=0)
	{
		*nret = 0;
		return S_OK;
	}
	//mouse_event();
	*nret = gDxObj.mysleep(mis);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::Delays(long mis_min, long mis_max, LONG* nret)
{
	if (mis_min<0)
	{
		mis_min = 0;
	}

	if (mis_max<mis_min)
	{
		*nret = 0;
		return S_OK;
	}
	long a = 0;
	while (1)
	{

		 a = rand();
		if ((a >= mis_min+1 && a <= mis_max) )
		{
			break;
		}
	}

	*nret = gDxObj.mysleep(a);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::ExitOs(long type, LONG* nret)
{
	if (type<0|| type>2)
	{
		return 0;
	}
	long ret = 0;
	switch (type)
	{
	case 0:
	{
		ret = MySystemShutdown(0);;
		break;
	}
	case 1:
	{
		ret = MySystemShutdown(1);
		
		break;
	}
	case 2:
	{
		ret = MySystemShutdown(2);
		break;
	}
	default:
		break;
	}

	*nret = ret;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::DisableScreenSave(LONG* nret)
{
	bool active = false;
	*nret = SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, false, &active, SPIF_SENDCHANGE); //阻止屏幕保护程序的运行
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::DisablePowerSave(LONG* nret)
{
	*nret = SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED); //禁止系统休眠，在程序入口加入
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::EnablePowerSaveh(LONG* nret)
{
	*nret = SetThreadExecutionState(ES_CONTINUOUS);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::DisableCloseDisplayAndSleep(LONG* nret)
{
	//设置当前的电源设置，禁止关闭显示器，禁止关闭硬盘，禁止睡眠，禁止待机.
	*nret = ClosePowers();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetDir(long type,  BSTR* nret)
{
	char* outbf = 0;
	gDxObj.GetDir(type,(LPCSTR*)&outbf);
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP ClwObject::GetCpuType(LONG* nret)
{
	*nret = gDxObj.GetCpuType();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetCpuUsage(LONG* nret)
{
	 
	*nret = gDxObj.GetCpuUsage();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetDiskSerial(long index,  BSTR* nret)
{
	char* outbf = 0;
	gDxObj.GetDiskSerial(index,(LPCSTR*)&outbf);
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetDisplayInfo(BSTR* nret)
{
	char* outbf = 0;
	gDxObj.GetDisplayInfo((LPCSTR*)&outbf);
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetDPI(LONG* nret)
{
	*nret = gDxObj.GetDPI();
	return S_OK;
}

long ClwObject::RunApp(BSTR path1,long type, LONG* nret)
{
	char* path = _com_util::ConvertBSTRToString(path1);

	*nret = gDxObj.RunApp((LPCSTR)path, type);
	delete[] path;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetHDiskCode(LONG* nret)
{

	*nret = gDxObj.GetHDiskCode();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetCpuCode( BSTR* nret)
{
	char* outbf = 0;
  gDxObj.GetCpuCode((LPCSTR*)&outbf);
  if (!outbf)
  {
	  *nret = 0;
	  return S_OK;
  }
  CComBSTR newbstr;
  newbstr.Append(outbf);
  newbstr.CopyTo(nret);
  delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetMainBoardInfoByCmd(LONG* nret)
{
	*nret = gDxObj.GetMainBoardInfoByCmd();
	return S_OK;

}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetMachineCode( BSTR* nret)
{
	char* outbf = 0;
	gDxObj.GetMachineCode((LPCSTR*)&outbf);
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetMachineCodeNoMac( BSTR* nret)
{
	char* outbf = 0;
  gDxObj.GetMachineCodeNoMac((LPCSTR*)&outbf);
  if (!outbf)
  {
	  *nret = 0;
	  return S_OK;
  }
  CComBSTR newbstr;
  newbstr.Append(outbf);
  newbstr.CopyTo(nret);
  delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetNetTime(BSTR* nret)
{
	char* cht = gDxObj.GetNetTime();
	if (cht==0)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(cht);
	newbstr.CopyTo(nret);
	delete[] cht;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetNetTimeByIp(BSTR ip1,  BSTR* nret)
{
	char* ip = _com_util::ConvertBSTRToString(ip1);
	char* outbf = 0;

	gDxObj.GetNetTimeByIp((LPCSTR)ip, (LPCSTR*)&outbf);
	delete[] ip;
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}


STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetOsBuildNumber(LONG* nret)
{
	//定义变量
	if (m_VerRet)
	{
		*nret = m_VersionInformation.dwBuildNumber;
		return S_OK;
	}

	*nret = 0;
	return S_OK;
}

STDMETHODIMP ClwObject::GetOsType(LONG* nret)
{
	OSVERSIONINFO  osret = { 0 };
	if (!m_VerRet)
	{
		osret.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osret);
	}
	else
	{
		
		memcpy(&osret,&m_VersionInformation, sizeof(OSVERSIONINFO));
	}
	ULONG    dwMajorVersion = 0;
	ULONG    dwMinorVersion = 0;
	ULONG    dwBuildNumber = 0;
	dwMajorVersion = m_VersionInformation.dwMajorVersion;
	dwMinorVersion = m_VersionInformation.dwMinorVersion;
	dwBuildNumber = m_VersionInformation.dwBuildNumber;

	if (dwMajorVersion >= 0&& dwMajorVersion<5)
	{
		*nret = 1;
		return S_OK;
	}
	if (dwMajorVersion == 5 && dwMinorVersion == 1 && dwBuildNumber == 2600 || dwMajorVersion == 5 && dwMinorVersion == 2)
	{
		*nret = 2;
		return S_OK;
	}

	if (dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuildNumber == 7601 || dwMajorVersion == 6 && dwMinorVersion == 1 && dwBuildNumber == 7600 || dwMajorVersion == 6 && dwMinorVersion == 1)
	{
		*nret = 3;
		return S_OK;
	}

	else if (dwMajorVersion == 6 && dwMinorVersion == 2 && dwBuildNumber == 9200 || dwMajorVersion == 6 && dwMinorVersion == 2 ||
		dwMajorVersion == 6 && dwMinorVersion == 3 && dwBuildNumber == 9600 ||
		dwMajorVersion == 6 && dwMinorVersion == 3)
	{
		*nret = 4;
		return S_OK;
	}

	else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuildNumber < 22000)
	{
		*nret = 5;
		return S_OK;
	}
	if (dwBuildNumber>= 22000)
	{
		{*nret = 6;
		return S_OK; }
	}


	*nret = 0;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetTime(LONG* nret)
{
	*nret= GetTickCount();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::Is64Bit(LONG* nret)
{
	*nret= gDxObj.Is64BitSystem();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::IsSurrpotVt(LONG* nret)
{
	if (!CheckCpuid())
	{
		*nret = 0;
		return S_OK;
		//return 0;  //不支持VT
	}

	//if (!VmIsBiosEnableVT())
	//{
	//	return 1;  //支持VT但是主板上关闭了
	//}
	//if (VmIsStarVT())
	//{
	//	return 2;  //VT正在被软件使用
	//}
	//GetDeviceCaps
		//EnumDisplaySettings
	* nret = 1;
	return S_OK;
	//return 1;//支持
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetScreenDepth(LONG* nret)
{
	*nret = gDxObj.GetScreenDepth();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetScreenDepth(long dmBitsPerPel, LONG* nret)
{
	*nret = gDxObj.SetScreenDepth(dmBitsPerPel);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetScreenHeight(LONG* nret)
{
	*nret = ::GetSystemMetrics(SM_CYSCREEN);//SM_CXFULLSCREEN
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetScreenWidth(LONG* nret)
{
	*nret = ::GetSystemMetrics(SM_CXSCREEN);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetScreen(long width, long height, LONG* nret)
{
	bool  bChanged = 0;
	DEVMODE dm;
	memset(&dm, 0, sizeof(DEVMODE));
	EnumDisplaySettings(NULL, ENUM_REGISTRY_SETTINGS, &dm);
	dm.dmSize = sizeof(DEVMODE);
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;
	//dm.dmBitsPerPel = 32;
	//dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	int ret=ChangeDisplaySettings(&dm, DISP_CHANGE_SUCCESSFUL);

	*nret = (ret == 0);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::GetLastError(LONG* nret)
{
	*nret = ::GetLastError();
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::SetDict(BSTR file1, LONG* nret)
{
	char* file = _com_util::ConvertBSTRToString(file1);
	*nret = gDxObj.SetDict((LPCSTR)file);
	delete[] file;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindStr(long x1, long y1, long w, long h, BSTR str1, BSTR color_format1, double sim, LONG* intX, LONG* intY, LONG* nret)
{
	if ((DWORD64)intX<=0x10000||(DWORD64)intY<=0x10000)
	{
		*nret =-1;
		*(LONG*) intX = -1;
		*(LONG*)intY = -1;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXFindStrMutex);
	char* str = _com_util::ConvertBSTRToString(str1);
	char* color_format = _com_util::ConvertBSTRToString(color_format1);
	*nret= gDxObj.FindStr(x1, y1, w, h, (LPCSTR)str, (LPCSTR)color_format, sim, (long*)intX, (long*)intY);
	delete[] str;
	delete[] color_format;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::FindStrEx(long x1, long y1, long w, long h, BSTR str1, BSTR color_format1, double sim,  BSTR* nret)
{
	if ((DWORD64)str1<=0x10000|| (DWORD64)color_format1 <= 0x10000)
	{
		*nret = 0;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXFindStrMutex);

	char* str = _com_util::ConvertBSTRToString(str1);
	char* color_format = _com_util::ConvertBSTRToString(color_format1);
	char* outbf = 0;
	 gDxObj.FindStrEx(x1, y1, w, h, (LPCSTR)str, (LPCSTR)color_format, sim, (LPCSTR*)&outbf);
	 if (!outbf)
	 {
		 *nret = 0;
		 return S_OK;
	 }
	 CComBSTR newbstr;
	 newbstr.Append(outbf);
	 newbstr.CopyTo(nret);
	 delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::Ocr(long x_1, long y_1, long w_1, long h_1, BSTR color_format1, double sim, BSTR* nret)
{
	if ((DWORD64)color_format1 <= 0x10000 )
	{
		*nret = 0;
		return S_OK;
	}
	LwMutexlock ts_mutexlock(&gDXOcrMutex);
	char* color_format = _com_util::ConvertBSTRToString(color_format1);
	char* outbf = 0;
	gDxObj.Ocr(x_1, y_1, w_1, h_1, (LPCSTR)color_format, sim, (LPCSTR*)&outbf);
	delete[] color_format; 
	if (!outbf)
	{
		*nret = 0;
		return S_OK;
	}
	CComBSTR newbstr;
	newbstr.Append(outbf);
	newbstr.CopyTo(nret);
	delete[] outbf;
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::MoveTo(long x, long y, LONG* nret)
{
	*nret = gDxObj.MoveTo(x,y);
	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ClwObject::LeftClick(LONG* nret)
{
	*nret = gDxObj.LeftClick();
	return S_OK;
}




