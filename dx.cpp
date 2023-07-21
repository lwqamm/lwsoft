#include "pch.h"
#include "dx.h"
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

mydx::mydx()
{
	CLSID clsid;
	IUnknown* pUnknown = NULL;
	HRESULT hr = 0;

	obj = NULL;
	hr = ::CLSIDFromProgID(L"dxkey.kbd", &clsid);
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

mydx::~mydx()
{
	if (obj) obj->Release();
}

long mydx::dxKeyDown(long hwnd,const TCHAR* str)
{
	if (!obj || !hwnd)return 0;
	static DISPID dispatch_id = -1;
	MyDispatchDriver spDisp(obj);
	HRESULT hr = 0;
	COleVariant pn[2];
	CComVariant vResult;

	pn[1] = COleVariant(hwnd);
	pn[0] = COleVariant(str);


	if (dispatch_id == -1)
	{
		spDisp.GetIDOfName(L"dxkeydown", &dispatch_id);
	}

	hr = spDisp.InvokeN(dispatch_id, pn, 2, &vResult);
	if (SUCCEEDED(hr))
	{
		return vResult.lVal;
	}
	return 0;
}
