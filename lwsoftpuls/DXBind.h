#pragma once
class DXBind
{
public:
	//绑定窗口
	STDMETHODIMP Bind(LONG hwnd);
	//设置默认操作路径
	bool  lwSetpath(const char* path);
	//找图返回坐标
 long lwFindPic( int x_1, int y_1, int w_1, int  h_1, BSTR pic_name, BSTR delta_color, double sim, int* intX, int* intY);
 //找色返回坐标
 long lwFindColor( int x1, int y1, int w1, int h1, BSTR color, double sim, int* intX, int* intY);
 //找图返回坐标系列
 LPVOID lwFindPicEx(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim);

private:
	//检测区域是否越界
	bool SetXy(int* x, int* y, int* w, int* h);
	//纯色填充背景
	bool FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr);
	//从文件加载24位图
	bool loadBitmap(BSTR strPath, LPVOID outdata, PBITMAPINFO PP);
	//获得位图BUFF
	LPVOID BmpTo24Data(const LPVOID src, PBITMAPINFO p2, DWORD dwStyle);
	//从窗口加载位图
	bool GetDcPic( DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);
    //图像缓冲区比较
	long CmpBmpData(const LPVOID pic, const LPVOID pic1, BSTR delta_color, double sim, int x, int y, PBITMAPINFO PP);
	//返回系列字符所需要的空间
	int  GetStrPosLen(int* dx, int* x, int* y);

public:
	HWND m_hwnd;            //被绑定的窗口的句柄
	TCHAR m_SetPath[MAX_PATH*2];//默认操作盘
public:
	DXBind(void);
	~DXBind(void);
};

