// lwsoft.cpp: Clwsoft 的实现

#include "pch.h"
#include "DXBind.h"
#include "lwsoft.h"


// Clwsoft

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::Number(LONG __num, LONG* __result)
{
    *__result = __num * __num;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::BindWindow(LONG hwnd)
{
    return gDxObj.Bind(hwnd);
}

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::SetPath(BSTR path, LONG* nret)
{
    *nret= gDxObj.lwSetpath((char*)path);
    *nret = 1;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::FindPic(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim, int* intX, int* intY)
{
	return gDxObj.lwFindPic(x_1, y_1, w_1, h_1, pic_name, delta_color, sim, intX, intY);
}

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::FindPicEx(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim)
{
    return (STDMETHODIMP)gDxObj.lwFindPicEx(x_1,y_1, w_1,h_1, pic_name, delta_color, sim);
}

STDMETHODIMP_(HRESULT __stdcall) Clwsoft::FindColor(int x1, int y1, int w1, int h1, BSTR color, double sim, int* intX, int* intY)
{
    return gDxObj.lwFindColor(x1,y1,w1,h1,color,sim,intX,intY);
}




