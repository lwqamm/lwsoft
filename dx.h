#pragma once
#ifndef __INCLUDE_BOJ_HL__
#define __INCLUDE_BOJ_HL__

#define  LW_KEY        1
#define  LW_MOUSE      2

#include <objbase.h>
#pragma pack (1)
class mydx
{
	public:
	IDispatch* obj;
	mydx();
	~mydx();
public:
	virtual long dxKeyDown(long hwnd, const TCHAR* str);

};
#pragma pack (0)
#endif

