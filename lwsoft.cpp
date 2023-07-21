// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#include "pch.h"


#include "lwsoft.h"
#include "atlbase.h"


class MyDispatchDriver
{
public:
	IDispatch* p;
	MyDispatchDriver()
	{
		p = NULL;
	}
	MyDispatchDriver(IDispatch* lp)
	{
		if ((p = lp) != NULL)
			p->AddRef();
	}
	~MyDispatchDriver() { if (p) p->Release(); }
	HRESULT GetIDOfName(LPCOLESTR lpsz, DISPID* pdispid)
	{
		HRESULT hr = -1;
		if (p == NULL) return hr;
		return p->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpsz, 1, LOCALE_USER_DEFAULT, pdispid);
	}
	HRESULT Invoke0(DISPID dispid, VARIANT* pvarRet = NULL)
	{
		HRESULT hr = -1;
		DISPPARAMS dispparams = { NULL, NULL, 0, 0 };
		if (p == NULL) return hr;
		return p->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, pvarRet, NULL, NULL);
	}
	HRESULT InvokeN(DISPID dispid, VARIANT* pvarParams, int nParams, VARIANT* pvarRet = NULL)
	{
		HRESULT hr = -1;
		DISPPARAMS dispparams = { pvarParams, NULL, nParams, 0 };
		if (p == NULL) return hr;
		return p->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, pvarRet, NULL, NULL);
	}
};


lwsoft::lwsoft()
{
	CLSID clsid;
	IUnknown* pUnknown = NULL;
	HRESULT hr = 0;

	obj = NULL;
	hr = ::CLSIDFromProgID(L"lwsoft1.obj", &clsid);
	if (FAILED(hr))
	{
		int eroo = GetLastError();
		return;
	}

	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID*)&pUnknown);
	if (FAILED(hr))
	{
		return;
	}

	pUnknown->QueryInterface(IID_IDispatch, (void**)&obj);
	if (pUnknown) pUnknown->Release();
}

lwsoft::~lwsoft()
{
	if (obj) obj->Release();
}

long lwsoft::FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, LONG* intX, LONG* intY)
{
	if (!obj || !pic_name || !delta_color || (LONGLONG)intX <= 0x10000 || (LONGLONG)intY <= 0x10000)
	{
		return 0;
	}
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[9];
	CComVariant vResult;

	pn[8] = COleVariant(x_1);
	pn[7] = COleVariant(y_1);
	pn[6] = COleVariant(w_1);
	pn[5] = COleVariant(h_1);
	pn[4] = COleVariant(pic_name);
	pn[3] = COleVariant(delta_color);
	pn[2] = COleVariant(sim);
	pn[1].vt = VT_I4;
	pn[1].plVal = intX;
	pn[0].vt = VT_I4;
	pn[0].plVal = intY;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindPic", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 9, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, int* intX, int* intY)
{
	return FindPic(x_1, y_1, w_1, h_1, pic_name, delta_color, sim, (long*)intX, (long*)intY);
}

CString lwsoft::FindPicEx(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim)
{
	if (!obj || !pic_name || !delta_color)
	{
		return CString();
	}
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[7];
	CComVariant vResult;

	pn[6] = COleVariant(x_1);
	pn[5] = COleVariant(y_1);
	pn[4] = COleVariant(w_1);
	pn[3] = COleVariant(h_1);
	pn[2] = COleVariant(pic_name);
	pn[1] = COleVariant(delta_color);
	pn[0] = COleVariant(sim);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindPicEx", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 7, &vResult);
	if (SUCCEEDED(hr))
	{

		return CString(vResult.bstrVal);
	}

	return CString();
}

long lwsoft::FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, long* longX, long* longY)
{
	if (!obj || !color || !longX || !longY)
	{
		return 0;
	}
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[8];
	CComVariant vResult;

	pn[7] = COleVariant(x1);
	pn[6] = COleVariant(y1);
	pn[5] = COleVariant(w1);
	pn[4] = COleVariant(h1);
	pn[3] = COleVariant(color);
	pn[2] = COleVariant(sim);
	pn[1].vt = VT_I4;//4字节指针
	pn[1].plVal = longX;
	pn[0].vt = VT_I4;
	pn[0].plVal = longY;
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindColor", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 8, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}

	return 0;
}

long lwsoft::FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, int* intX, int* intY)
{
	return FindColor(x1, y1, w1, h1, color, sim, (long*)intX, (long*)intY);
}

long lwsoft::FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, long* intX, long* intY)
{
	if (!obj || (DWORD64)color <= 0x10000 || (DWORD64)intX <= 0x10000 || (DWORD64)intY <= 0x10000)
	{
		return 0;
	}
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[11];
	CComVariant vResult;

	pn[10] = CComVariant(x_1);
	pn[9] = CComVariant(y_1);
	pn[8] = CComVariant(w_1);
	pn[7] = CComVariant(h_1);
	pn[6] = CComVariant(color);
	pn[5] = CComVariant(sim);
	pn[4] = CComVariant(count);
	pn[3] = CComVariant(width);
	pn[2] = CComVariant(height);
	pn[1].vt = VT_I4;
	pn[1].plVal = intX;
	pn[0].vt = VT_I4;
	pn[0].plVal = intY;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindColorBlock", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 11, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, int* intX, int* intY)
{
	return FindColorBlock(x_1, y_1, w_1, h_1, color, sim, count, width, height, (long*)intX, (long*)intY);
}

long lwsoft::BindWindow(long hwnd)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;
	long as2 = 0;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(as2);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"BindWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::UnBindWindow()
{
	if (!obj )return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"UnBindWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetWindowState(long hwnd, long flag)
{
	if (!obj || !hwnd || flag < 0 || flag>15)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(flag);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetWindowState", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetWindowTransparent(long hwnd, long trans)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(trans);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetWindowTransparent", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetWindowText(long hwnd, const TCHAR* title)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(title);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetWindowText", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetWindowSize(long hwnd, long width, long hight)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;

	pn[2] = COleVariant(hwnd);
	pn[1] = COleVariant(width);
	pn[0] = COleVariant(hight);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetWindowSize", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetClientSize(long hwnd, long width, long height)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;

	pn[2] = COleVariant(hwnd);
	pn[1] = COleVariant(width);
	pn[0] = COleVariant(height);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetClientSize", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::MoveWindow(LONG hwnd, LONG x, LONG y)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;

	pn[2] = COleVariant(hwnd);
	pn[1] = COleVariant(x);
	pn[0] = COleVariant(y);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"MoveWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::ScreenToClient(LONG hwnd, int* x, int* y)
{
	return ScreenToClient(hwnd, (LONG*)x, (LONG*)y);
}

long lwsoft::SendPaste(LONG hwnd)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SendPaste", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetClipboard()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetClipboard", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::SetClipboard(const TCHAR* values)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant((LONGLONG)values);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetClipboard", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SendString(long hwnd, const TCHAR* str)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(str);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SendString", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SendString2(LONG hwnd, const TCHAR* str)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(str);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SendString2", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetWindowTitle(LONG hwnd)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;



	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowTitle", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::GetWindowThreadProcessId(long hwnd)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowThreadProcessId", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetWindowProcessId(long hwnd)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowProcessId", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetWindowProcessPath(LONG hwnd)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	char* outstr = 0;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowProcessPath", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{

		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::GetWindowRect(long hwnd, LONG* x1, long* y1, long* x2, long* y2)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;

	pn[4] = COleVariant(hwnd);
	pn[3].vt = VT_I4;
	pn[3].plVal = x1;
	pn[2].vt = VT_I4;
	pn[2].plVal = y1;
	pn[1].vt = VT_I4;
	pn[1].plVal = x2;
	pn[0].vt = VT_I4;
	pn[0].plVal = y2;
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowRect", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 5, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetWindowRect(long hwnd, int* x1, int* y1, int* x2, int* y2)
{
	return GetWindowRect(hwnd, (long*)x1, (long*)y1, (long*)x2, (long*)y2);
}

CString lwsoft::GetWindowClass(long hwnd)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	char* outstr = 0;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowClass", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::GetWindowState(LONG hwnd, LONG flag)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(flag);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindowState", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetSpecialWindow(LONG flag)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant(flag);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetSpecialWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetWindow(long hwnd, long flag)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(flag);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetMousePointWindow()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetMousePointWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetPointWindow(long x, long y)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(x);
	pn[0] = COleVariant(y);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetPointWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetForegroundWindow()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetForegroundWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetForegroundFocus()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetForegroundFocus", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetForegroundFocus(long hwnd)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(hwnd);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetForegroundFocus", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetClientSize(long hwnd, LONG* w, LONG* h)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;

	pn[2] = COleVariant(hwnd);
	pn[1].vt = VT_I4;
	pn[0].vt = VT_I4;
	pn[1].plVal = w;
	pn[0].plVal = h;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetClientSize", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetClientSize(long hwnd, int* w, int* h)
{
	return GetClientSize(hwnd, (long*)w, (long*)h);
}

long lwsoft::GetClientRect(LONG hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;

	pn[4] = COleVariant(hwnd);
	pn[3].vt = VT_I4;
	pn[2].vt = VT_I4;
	pn[1].vt = VT_I4;
	pn[0].vt = VT_I4;
	pn[3].plVal = x1;
	pn[2].plVal = y1;
	pn[1].plVal = x2;
	pn[0].plVal = y2;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetClientRect", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 5, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetClientRect(LONG hwnd, int* x1, int* y1, int* x2, int* y2)
{
	return GetClientRect(hwnd, (long*)x1, (long*)y1, (long*)x2, (long*)y2);
}

long lwsoft::FindWindowEx(LONG parent, const TCHAR* class_name, const TCHAR* title)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;



	pn[2] = COleVariant(parent);
	pn[1] = COleVariant(class_name);
	pn[0] = COleVariant(title);
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindWindowEx", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::FindWindow(const TCHAR* class_name, const TCHAR* title)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;


	pn[1] = COleVariant(class_name);
	pn[0] = COleVariant(title);
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::EnumWindowByProcess(const TCHAR* process_name, const TCHAR* title, const TCHAR* class_name, LONG filter)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[4];
	CComVariant vResult;



	pn[3] = COleVariant(process_name);
	pn[2] = COleVariant(title);
	pn[1] = COleVariant(class_name);
	pn[0] = COleVariant(filter);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"EnumWindowByProcess", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 4, &vResult);
	if (SUCCEEDED(hr))
	{

		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::EnumWindowByProcessId(long pid, const TCHAR* title, const TCHAR* class_name, LONG filter)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[4];
	CComVariant vResult;



	pn[3] = COleVariant(pid);
	pn[2] = COleVariant((LONGLONG)title);
	pn[1] = COleVariant((LONGLONG)class_name);
	pn[0] = COleVariant(filter);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"EnumWindowByProcessId", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 4, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::EnumProcess(const TCHAR* name)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;




	pn[0] = COleVariant(name);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"EnumProcess", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::EnumWindow(LONG parent, const TCHAR* title, const TCHAR* class_name, LONG filter)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[4];
	CComVariant vResult;

	pn[3] = COleVariant(parent);
	pn[2] = COleVariant(title);
	pn[1] = COleVariant(class_name);
	pn[0] = COleVariant(filter);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"EnumWindow", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 4, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::CheckFontSmooth()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"CheckFontSmooth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::DisableFontSmooth()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"DisableFontSmooth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::EnableFontSmooth()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"EnableFontSmooth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::CheckUAC()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"CheckUAC", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetUAC(LONG enable)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(enable);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetUAC", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::Delay(long mis)
{
	if (!obj || !mis)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(mis);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Delay", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::Delays(long mis_min, long mis_max)
{
	if (!obj || !mis_max)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;


	pn[1] = COleVariant(mis_min);
	pn[0] = COleVariant(mis_max);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Delays", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::ExitOs(long type)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant(type);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"ExitOs", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetDir(long type)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(type);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetDir", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return 0;
}

long lwsoft::GetCpuType()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetCpuType", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetCpuUsage()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetCpuUsage", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetDiskSerial(long index)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;

	pn[0] = COleVariant(index);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetDiskSerial", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString  lwsoft::GetDisplayInfo()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetDisplayInfo", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::GetDPI()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetDPI", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::RunApp(const TCHAR* path, long type)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(path);
	pn[0] = COleVariant(type);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"RunApp", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long long lwsoft::GetHDiskCode()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetHDiskCode", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetCpuCode()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetCpuCode", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);

	}
	return CString();
}

long long lwsoft::GetMainBoardInfoByCmd()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetMainBoardInfoByCmd", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetMachineCode()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetMachineCode", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::GetMachineCodeNoMac()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetMachineCodeNoMac", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::GetNetTime()
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetNetTime", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

CString lwsoft::GetNetTimeByIp(const TCHAR* ip)
{
	if (!obj)return CString();
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant(ip);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetNetTimeByIp", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return CString();
}

long lwsoft::GetOsBuildNumber()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetOsBuildNumber", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetOsType()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetOsType", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetTime()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetTime", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

BOOL lwsoft::Is64Bit()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Is64Bit", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::IsSurrpotVt()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"IsSurrpotVt", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetScreenDepth()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetScreenDepth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetScreenDepth(long dmBitsPerPel)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetScreenDepth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetScreenHeight()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetScreenHeight", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetScreenWidth()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetScreenWidth", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetScreen(long width, long height)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(width);
	pn[0] = COleVariant(height);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetScreen", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::GetLastError()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;

	// __cpuid();
	//__readcr4();
	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetLastError", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}



long lwsoft::ScreenToClient(LONG hwnd, LONG* x, LONG* y)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;

	pn[2] = COleVariant(hwnd);
	pn[1].vt = VT_I4;
	pn[0].vt = VT_I4;
	pn[1].plVal = x;
	pn[0].plVal = y;

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"ScreenToClient", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::Bmp32To24(const TCHAR* Filepath, const TCHAR* FilepathBak, int ret)
{
	if (!obj || (DWORD64)Filepath <= 0x10000 || (DWORD64)FilepathBak <= 0x10000)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[3];
	CComVariant vResult;
	pn[2] = COleVariant(Filepath);
	pn[1] = COleVariant(FilepathBak);
	pn[0] = COleVariant((LONG)ret);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Bmp32To24", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 3, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::Ver()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;

	CComVariant vResult;


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Ver", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return 0;
}

long lwsoft::Capture(long x, long y, long w, long h, const TCHAR* file)
{
	if (!obj || (DWORD64)file <= 0x10000)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;

	pn[4] = COleVariant(x);
	pn[3] = COleVariant(y);
	pn[2] = COleVariant(w);
	pn[1] = COleVariant(h);
	pn[0] = COleVariant(file);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Capture", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 5, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::CmpColor(long x, long y, const TCHAR* color, double sim)
{
	if (!obj || (DWORD64)color <= 0x10000)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;

	pn[3] = COleVariant(x);
	pn[2] = COleVariant(y);
	pn[1] = COleVariant(color);
	pn[0] = COleVariant(sim);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Capture", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 4, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

CString lwsoft::GetColor(long x, long y)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;



	pn[1] = COleVariant(x);
	pn[0] = COleVariant(y);



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetColor", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return 0;
}

long lwsoft::GetColorNum(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[6];
	CComVariant vResult;



	pn[5] = COleVariant(x_1);
	pn[4] = COleVariant(y_1);
	pn[3] = COleVariant(w_1);
	pn[2] = COleVariant(h_1);
	pn[1] = COleVariant(color);
	pn[0] = COleVariant(sim);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"GetColorNum", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 6, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

long lwsoft::IsDisplayDead(long x, long y, long w, long h, long t)
{
	if (!obj || t <= 0)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[5];
	CComVariant vResult;




	pn[4] = COleVariant(x);
	pn[3] = COleVariant(y);
	pn[2] = COleVariant(w);
	pn[1] = COleVariant(h);
	pn[0] = COleVariant(t);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"IsDisplayDead", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 5, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

long lwsoft::SetPath(const TCHAR* patht)
{
	if (!obj || (DWORD64)patht <= 0x10000)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant((LONGLONG)patht);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"IsDisplayDead", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

BOOL lwsoft::SetDict(const TCHAR* file)
{
	if (!obj || (DWORD64)file <= 0x10000)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[1];
	CComVariant vResult;


	pn[0] = COleVariant((LONGLONG)file);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"SetDict", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 1, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

long lwsoft::FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, long* intX, long* intY)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[9];
	CComVariant vResult;

	pn[8] = COleVariant(x1);
	pn[7] = COleVariant(y1);
	pn[6] = COleVariant(w);
	pn[5] = COleVariant(h);
	pn[4] = COleVariant(str);
	pn[3] = COleVariant(color_format);
	pn[2] = COleVariant(sim);
	pn[1] = COleVariant((LONGLONG)intX);
	pn[0] = COleVariant((LONGLONG)intY);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindStr", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 9, &vResult);
	if (SUCCEEDED(hr))
	{

		return vResult.lVal;
	}
	return 0;
}

long lwsoft::FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, int* intX, int* intY)
{
	return FindStr(x1, y1, w, h, str, color_format, sim, (long*)intX, (long*)intY);
}

CString lwsoft::FindStrEx(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[7];
	CComVariant vResult;



	pn[6] = COleVariant(x1);
	pn[5] = COleVariant(y1);
	pn[4] = COleVariant(w);
	pn[3] = COleVariant(h);
	pn[2] = COleVariant(str);
	pn[1] = COleVariant(color_format);
	pn[0] = COleVariant(sim);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"FindStrEx", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 7, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return 0;
}

CString lwsoft::Ocr(long x_1, long y_1, long w_1, long h_1, const TCHAR* color_format, double sim)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[7];
	CComVariant vResult;




	pn[5] = COleVariant(x_1);
	pn[4] = COleVariant(y_1);
	pn[3] = COleVariant(w_1);
	pn[2] = COleVariant(h_1);
	pn[1] = COleVariant(color_format);
	pn[0] = COleVariant(sim);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"Ocr", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 7, &vResult);
	if (SUCCEEDED(hr))
	{
		return CString(vResult.bstrVal);
	}
	return 0;
}

long lwsoft::MoveTo(long x, long y)
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;





	pn[1] = COleVariant(x);
	pn[0] = COleVariant(y);

	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"MoveTo", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

long lwsoft::LeftClick()
{
	if (!obj)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	CComVariant vResult;



	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"LeftClick", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, 0, 0, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}

