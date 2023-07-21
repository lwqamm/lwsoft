#include "pch.h"
#include "DXBind.h"
#pragma warning(disable:4996)

DXBind::DXBind(void)
{
}

DXBind::~DXBind(void)
{
}

STDMETHODIMP_(HRESULT __stdcall) DXBind::Bind(LONG hwnd)
{
    if (hwnd==0|| ::IsWindow((HWND)hwnd) == false)
    {
		MessageBox(NULL, "无效窗口句柄", "LW", NULL);
		return false;
    }
	//记录被绑定的窗口的句柄
	m_hwnd = (HWND)hwnd;


    return TRUE;
}

bool DXBind::lwSetpath(const char* path)
{
	if (isNull(path))
	{
		return false;
	}
	memset(m_SetPath, 0, MAX_PATH * 2);
	
	int ret =sprintf(m_SetPath, "%s", path);
	return ret;
}

//返回系列字符所需要的空间
int DXBind::GetStrPosLen(int* dx, int* x, int* y)
{
	if (isNull(dx) || isNull(x) || isNull(y))
	{
		return 0;
	}
	if (*dx >= 0 && *dx <= 9)
	{
		*dx = 1;
	}
	else	if (*dx >= 10 && *dx <= 99)
	{
		*dx = 2;
	}
	else	if (*dx >= 100 && *dx <= 999)
	{
		*dx = 3;
	}
	else	if (*dx >= 1000 && *dx <= 9999)
	{
		*dx = 4;
	}
	else
	{
		*dx = 0;
		return 0;
	}
	if (*x >= 0 && *x <= 9)
	{
		*x = 1;
	}
	else	if (*x >= 10 && *x <= 99)
	{
		*x = 2;
	}
	else	if (*x >= 100 && *x <= 999)
	{
		*x = 3;
	}
	else	if (*x >= 1000 && *x <= 9999)
	{
		*x = 4;
	}
	else
	{
		*x = 0;
		return 0;
	}
	if (*y >= 0 && *y <= 9)
	{
		*y = 1;
	}
	else	if (*y >= 10 && *y <= 99)
	{
		*y = 2;
	}
	else	if (*y >= 100 && *y <= 999)
	{
		*y = 3;
	}
	else	if (*y >= 1000 && *y <= 9999)
	{
		*y = 4;
	}
	else
	{
		*y = 0;
		return 0;
	}
	return 1;
}

//设置RECT防止越界
bool DXBind::SetXy(int* x, int* y, int* w, int* h)
{
	RECT rtcc;
	::GetClientRect(m_hwnd, &rtcc);
	if (*x < 0)
	{
		*(int*)x = 0;
	}
	else if (*x >= rtcc.left + rtcc.right)
	{
		return false;
	}
	if (*y < 0)
	{
		*(int*)y = 0;
	}
	else if (*y >= rtcc.top + rtcc.bottom)
	{
		return false;
	}
	if (*w <= 0)
	{
		return false;
	}
	else if (*w >= rtcc.left + rtcc.right)
	{
		*(int*)w = rtcc.left + rtcc.right;
	}
	if (*h <= 0)
	{
		return false;
	}
	else if (*h >= rtcc.top + rtcc.bottom)
	{
		*(int*)h = rtcc.top + rtcc.bottom;
	}
	return true;
}

//纯色填充背景
bool DXBind::FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr)
{
	DWORD dw = ::SetBkColor(dc, clr);
	BOOL ret = ::ExtTextOut(dc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	::SetBkColor(dc, dw);
	return	ret;
}

//从磁盘加载文件
bool DXBind::loadBitmap(BSTR strPath, LPVOID outdata, PBITMAPINFO PP)
{
	HANDLE hFile = CreateFile((LPCSTR)strPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD fileSize = GetFileSize(hFile, NULL);    //获得文件大小的低两字节
	char* pSrcData = new char[fileSize];    //创建缓冲区
	DWORD realRead = 0;
	bool ret = false;
	ret = ReadFile(hFile, pSrcData, fileSize, &realRead, NULL);    //拷贝文件的内容给缓冲区fileBuff
	CloseHandle(hFile);

	if (ret)
	{
		BITMAPINFO BmpInfoHeader;

		//BITMAP fHeader;

		if (isNull(pSrcData) || isNull(outdata))
		{

			delete[] pSrcData;

			return false;
		}

		//根据前两个字节，判断是不是BMP图片
		if ((pSrcData[0] != 'B') || (pSrcData[1] != 'M'))
		{
			//printf("not a bmp picture.\n");
			delete[] pSrcData;
			return false;
		}

		//获取信息头
		memcpy(&BmpInfoHeader, pSrcData + BMP_FILE_HEADER_LENGTH, sizeof(BmpInfoHeader));
		*(PBITMAPINFO)PP = BmpInfoHeader;
		//将宽高信息传递出去
		//int N = 4 - ((width * 3) % 4);
		//判断BMP图片像素的位数
		if (BmpInfoHeader.bmiHeader.biBitCount == BMP_24_BIT)
		{
			int bioff = sizeof(BITMAPFILEHEADER) + BmpInfoHeader.bmiHeader.biSize;
			LPVOID chta = BmpTo24Data((LPVOID)((DWORD64)pSrcData + bioff), &BmpInfoHeader, BMP_24_BIT);

			//delete[] chta;
			delete[] pSrcData;
			*(LPVOID*)outdata = chta;
			return true;
		}
		else if (BmpInfoHeader.bmiHeader.biBitCount == BMP_32_BIT)
		{

			LPVOID chta = BmpTo24Data((char*)((DWORD64)pSrcData + ((PBITMAPFILEHEADER)pSrcData)->bfOffBits), &BmpInfoHeader, BMP_32_BIT);

			//delete[] chta;
			delete[] pSrcData;
			*(LPVOID*)outdata = chta;
			return true;
			//return TRUE;
		}


	}
	if (pSrcData)
	{
		delete[] pSrcData;
	}
	return false;
}

/*
功能:32位位图转换24
参数1:文件缓冲区
参数2:位图文件信息
参数3:位图位深
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
LPVOID DXBind::BmpTo24Data(const LPVOID src, PBITMAPINFO p2, DWORD dwStyle)
{
	if (isNull(src) || isNull(p2))
	{
		return 0;
	}
	int w = p2->bmiHeader.biWidth, h = p2->bmiHeader.biHeight;


	COLORREF** pp = new COLORREF * [h];
	for (size_t i = 0; i < h; i++)
	{
		pp[i] = new COLORREF[w];
	}
	if (!pp)
	{
		return 0;
	}
	int N = w * h;//缓冲区大小
	p2->bmiHeader.biSizeImage = N;


	switch (dwStyle)
	{
	case BMP_32_BIT:
	{
		PUCHAR p = (PUCHAR)src;
		int realPitch = 0;
		for (size_t i = 0; i < h; i++)
		{
			realPitch = w * (h - (i + 1)) * 4;
			for (size_t j = 0; j < w; j++)
			{
				UCHAR b = p[realPitch + (j * 4)];
				UCHAR g = p[realPitch + (j * 4) + 1];
				UCHAR r = p[realPitch + (j * 4) + 2];
				pp[i][j] = RGB(r, g, b);
			}
		}
		return  pp;
	}
	case BMP_24_BIT:
	{
		int N = ((w * 3) % 4);
		if (N > 0)
		{
			N = 4 - ((w * 3) % 4);
		}
		PUCHAR p = (PUCHAR)src;
		int realPitch = 0;
		for (size_t i = 0; i < h; i++)
		{
			realPitch = (w * h * 3 + N * h) - ((w * 3 + N) * (i + 1));
			for (size_t j = 0; j < w; j++)
			{
				UCHAR b = p[realPitch + (j * 3)];
				UCHAR g = p[realPitch + (j * 3) + 1];
				UCHAR r = p[realPitch + (j * 3) + 2];
				pp[i][j] = RGB(r, g, b);
				if (j == w - 1)
				{
					p = p;
				}
			}
		}
		return  pp;
	}
	default:
		break;
	}
	delete[] pp;
	return 0;
}

/*
功能:CDC 截图
参数1:窗口句柄
参数2:x 图片左上角x
参数3:y 图片左上角y
参数4:w 图片宽度
参数5:h 图片高度
参数6:位图文件缓冲区
参数7:位图文件信息
*/
bool DXBind::GetDcPic(DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP)
{
	if (!::IsWindow(m_hwnd))
	{
		return false;
	}
	if (!SetXy( (int*)&x, (int*)&y, (int*)&w, (int*)&h))
	{
		return false;
	}

	HDC pdc = GetDC(m_hwnd);//获得窗口画图设备句柄
	HDC cacheDC = CreateCompatibleDC(pdc);//创建兼容DC
	HBITMAP HEditBmp = CreateCompatibleBitmap(pdc, w, h); //内存编辑框位图
	HBITMAP pOHEditmap = (HBITMAP)::SelectObject(cacheDC, HEditBmp);        //内存画编辑框位图

	RECT rct;
	rct.left = x;
	rct.top = y;
	rct.right = x + w;
	rct.bottom = y + h;
	FillSolidRect(cacheDC, &rct, RGB(0xFF, 0xFF, 0xFF));
	::BitBlt(cacheDC, 0, 0, w, h, pdc, x, y, SRCCOPY);

	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	::GetDIBits(cacheDC, HEditBmp, 0, h, NULL, &bi, DIB_RGB_COLORS);

	char* data = new char[bi.bmiHeader.biSizeImage + 2];
	if (!data)
	{
		return false;
	}
	::GetDIBits(cacheDC, HEditBmp, 0, h, data, &bi, DIB_RGB_COLORS);
	//删除DC
	//CImage age;
	//age.Attach(HEditBmp);
	//age.Save("D:\\123.bmp");
	//age.Destroy();
	//BmpTo24DataFile("H:\\VS1\\FindPic\\res\\123.bmp", data,&bi);//保存成本地文件

	::DeleteDC(cacheDC);
	::SelectObject(cacheDC, pOHEditmap);
	::DeleteObject(HEditBmp);
	//清除完毕
	LPVOID pbi = BmpTo24Data(data, &bi, bi.bmiHeader.biBitCount);
	if (!pbi)
	{
		delete[] data;
		return false;
	}

	*(PBITMAPINFO)PP = bi;
	*(LPVOID*)outdata = pbi;
	delete[] data;
	return true;
}

/*
图像缓冲区比较

*/
long DXBind::CmpBmpData(const LPVOID pic, const LPVOID pic1, BSTR delta_color, double sim, int x, int y, PBITMAPINFO PP)
{
	if (isNull(pic) || isNull(pic1) || isNull(delta_color) || isNull(PP))
	{
		return 0;
	}

	//处理偏色
	int R = 0, G = 0, B = 0;
	if (strlen((char*)delta_color) >= 6)
	{
		char tch[3] = { 0 };
		memset(tch, 0, 3);
		memcpy(tch, delta_color, 2);
		StrToIntEx(tch, STIF_SUPPORT_HEX, &R);
		memset(tch, 0, 3);
		memcpy(tch, delta_color + 2, 2);
		StrToIntEx(tch, STIF_SUPPORT_HEX, &G);
		memset(tch, 0, 3);
		memcpy(tch, delta_color + 4, 2);
		StrToIntEx(tch, STIF_SUPPORT_HEX, &B);
	}

	COLORREF** p = (COLORREF**)pic, ** p1 = (COLORREF**)pic1;
	//BOOL ret = FALSE;

	COLORREF simColor = 0;

	{
		if (sim <= 0.0)
		{
			sim = 0.1;
		}
		else if (sim > 1)
		{
			sim = 1;
		}

		if (sim >= 0.1 && sim <= 0.19)
		{
			simColor = 83;
		}
		else if (sim >= 0.2 && sim <= 0.29)
		{
			simColor = 73;
		}
		else if (sim >= 0.3 && sim <= 0.39)
		{
			simColor = 65;
		}
		else if (sim >= 0.4 && sim <= 0.49)
		{
			simColor = 56;
		}
		else if (sim >= 0.5 && sim <= 0.59)
		{
			simColor = 49;
		}
		else if (sim >= 0.6 && sim <= 0.69)
		{
			simColor = 39;
		}
		else if (sim >= 0.7 && sim <= 0.79)
		{
			simColor = 30;
		}
		else if (sim >= 0.8 && sim <= 0.89)
		{
			simColor = 24;
		}
		else if (sim >= 0.9 && sim <= 0.99)
		{
			simColor = 18;
		}
		else if (sim == 1)
		{
			simColor = 9;
		}
	}

	BYTE loadR = 0, loadG = 0, loadB = 0;
	BYTE wndR = 0, wndG = 0, wndB = 0;
	COLORREF pLoadColor = 0, pWndColor = 0;
	BOOL ret = false;

	if (p1[0][0] == p1[0][PP->bmiHeader.biWidth - 1] && p1[0][0] == p1[PP->bmiHeader.biHeight - 1][0] && p1[0][0] == p1[PP->bmiHeader.biHeight - 1][PP->bmiHeader.biWidth - 1])
	{
		int len = 0;
		for (size_t i = 0; i < PP->bmiHeader.biHeight; i++)
		{
			for (size_t j = 0; j < PP->bmiHeader.biWidth; j++)
			{
				if (p1[0][0] == p1[i][j])
				{
					len++;
				}
			}
		}
		if (len == PP->bmiHeader.biHeight * PP->bmiHeader.biWidth)
		{
			ret = false;
		}
		else
		{
			ret = TRUE;
		}

	}

	for (int i = 0; i < PP->bmiHeader.biHeight; i++)
	{
		for (int j = 0; j < PP->bmiHeader.biWidth; j++)
		{
			if (ret)//是否有透明图的特性
			{
				if (p1[0][0] == p1[i][j])
				{
					continue;//过滤掉透明色
				}
			}
			pLoadColor = p[y + i][x + j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			pWndColor = p1[i][j];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			//用于偏色比较
			if (abs(loadR - wndR) <= (R + simColor)
				&& abs(loadG - wndG) <= (G + simColor)
				&& abs(loadB - wndB) <= (B + simColor))
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}


	return true;
}

/*
x 整形数: 区域的左上X坐标
y 整形数: 区域的左上Y坐标
w  整形数: 区域的宽度
h  整形数: 区域的高度
pic_name 字符串:图片名,可以是多个图片,比如"test.bmp"
delta_color 字符串:颜色色偏比如"203040" 表示RGB的色偏分别是20 30 40 (这里是16进制表示)
sim 双精度浮点数:相似度,取值范围0.1-1.0
intX 变参指针:返回图片左上角的X坐标
intY 变参指针:返回图片左上角的Y坐标
*/
long DXBind::lwFindPic(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim, int* intX, int* intY)
{
	if (!::IsWindow(m_hwnd))
	{
		*(int*)intX = -1;
		*(int*)intY = -1;
		return -1;
	}
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		*(int*)intX = -1;
		*(int*)intY = -1;
		return -2;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &pic, &bi))
	{
		*(int*)intX = -1;
		*(int*)intY = -1;
		return -3;
	}
	BITMAPINFO pbi;
	LPVOID data = 0;
	if (!loadBitmap(pic_name, &data, &pbi))
	{
		COLORREF** p = (COLORREF**)pic;
		for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
		{
			delete p[i];
		}
		delete[] pic;
		*(int*)intX = -1;
		*(int*)intY = -1;
		return -5;
	}
	int    w1 = pbi.bmiHeader.biWidth;
	int	h1 = pbi.bmiHeader.biHeight;
	int x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;
	bool ret = false;

	for (int y = 0; y < y_len; y++)
	{
		for (size_t x = 0; x < x_len; x++)
		{
			ret = false;
			if (CmpBmpData(pic, data, delta_color, sim, x, y, &pbi))
			{
				ret = true;
				*(int*)intX = x + x_1;
				*(int*)intY = y + y_1;
				goto sEnd;
			}

		}

	}
sEnd:
	COLORREF** p = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete p[i];
	}
	delete[] pic;
	COLORREF** fp = (COLORREF**)data;
	for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
	{
		delete fp[i];
	}
	delete[] fp;
	if (ret)
	{
		return 1;
	}
	*(int*)intX = -1;
	*(int*)intY = -1;
	return -7;
}

/*
x1 整形数 : 区域的左上X坐标
y1 整形数 : 区域的左上Y坐标
x2 整形数 : 区域的右下X坐标
y2 整形数 : 区域的右下Y坐标
color 字符串 : 颜色 格式为"RRGGBB-DRDGDB", 比如"123456-000000|aabbcc-202020".也可以支持反色模式.前面加@即可.比如"@123456-000000|aabbcc-202020".具体可以看下放注释.注意，这里只支持RGB颜色.
sim 双精度浮点数 : 相似度, 取值范围0.1 - 1.0
intX 变参指针:返回X坐标
intY 变参指针:返回Y坐标
*/
long DXBind::lwFindColor(int x1, int y1, int w1, int h1, BSTR color, double sim, int* intX, int* intY)
{

	if (!::IsWindow(m_hwnd) || isNull(color))
	{
		return  0;
	}
	if (!SetXy(&x1, &y1, &w1, &h1))
	{
		return 0;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x1, y1, w1, h1, &pic, &bi))
	{
		return 0;
	}
	BOOL ret = FALSE;
	int stlen = 0, slen = strlen((char*)color);

	PCHAR p = (PCHAR)color;
	char** colorStr = 0;
	for (size_t i = 0; i < slen; i++)
	{
		if (p[i] == '|')
		{
			stlen++;
		}
	}
	stlen += 1;
	colorStr = new char* [stlen];
	int sart = 0, sEnd = 0;
	for (size_t i = 0; i < stlen; i++)
	{
		sart = sEnd;
		for (size_t j = sart; j < slen; j++)
		{

			if (p[j] == '|' || j == slen - 1)
			{
				sEnd = j;
				break;
			}
		}


		if (i > 0)
		{
			colorStr[i] = new char[sEnd - sart + 2];
			memset(colorStr[i], 0, sEnd - sart + 2);
			if (sEnd != slen - 1 && sart != 0)
			{
				memcpy(colorStr[i], p + sart, sEnd - sart);
			}
			else
			{
				memcpy(colorStr[i], p + sart, sEnd - sart + 1);
			}

		}
		else
		{
			colorStr[i] = new char[sEnd - sart + 2];
			memset(colorStr[i], 0, sEnd - sart + 2);
			memcpy(colorStr[i], p + sart, sEnd - sart + 1);
		}

		sEnd++;
	}
	COLORREF simColor = 0;

	{
		if (sim <= 0.0)
		{
			sim = 0.1;
		}
		else if (sim > 1)
		{
			sim = 1;
		}

		if (sim >= 0.1 && sim <= 0.19)
		{
			simColor = 83;
		}
		else if (sim >= 0.2 && sim <= 0.29)
		{
			simColor = 73;
		}
		else if (sim >= 0.3 && sim <= 0.39)
		{
			simColor = 65;
		}
		else if (sim >= 0.4 && sim <= 0.49)
		{
			simColor = 56;
		}
		else if (sim >= 0.5 && sim <= 0.59)
		{
			simColor = 49;
		}
		else if (sim >= 0.6 && sim <= 0.69)
		{
			simColor = 39;
		}
		else if (sim >= 0.7 && sim <= 0.79)
		{
			simColor = 30;
		}
		else if (sim >= 0.8 && sim <= 0.89)
		{
			simColor = 24;
		}
		else if (sim >= 0.9 && sim <= 0.99)
		{
			simColor = 18;
		}
		else if (sim == 1)
		{
			simColor = 9;
		}
	}



	int loadR = 0, loadG = 0, loadB = 0;
	int wndR = 0, wndG = 0, wndB = 0;
	int R = 0, G = 0, B = 0;
	COLORREF pLoadColor = 0, pWndColor = 0, pRGB = 0;
	COLORREF** p1 = (COLORREF**)pic;

	for (size_t y = 0; y < bi.bmiHeader.biHeight; y++)
	{
		ret = FALSE;
		for (size_t x = 0; x < bi.bmiHeader.biWidth; x++)
		{
			pLoadColor = p1[y][x];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			for (size_t k = 0; k < stlen; k++)
			{
				if (strlen(colorStr[k]) != 13)
				{
					return 0;
				}
				char t_ch[3] = { 0 };
				memcpy(t_ch, colorStr[k], 2);

				wndR = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k] + 2, 2);
				wndG = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k] + 4, 2);
				wndB = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k] + 7, 2);
				R = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k] + 9, 2);
				G = HexToInt(t_ch);

				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k] + 11, 2);
				B = HexToInt(t_ch);


				//用于偏色比较
				if (abs(loadR - wndR) <= (R + simColor)
					&& abs(loadG - wndG) <= (G + simColor)
					&& abs(loadB - wndB) <= (B + simColor))
				{
					*(int*)intX = x;
					*(int*)intY = y;
					ret = TRUE;
					//break;
					goto sEnd;
				}
			}

		}

	}

sEnd:
	for (size_t i = 0; i < stlen; i++)
	{
		delete[] colorStr[i];
	}
	delete[] colorStr;

	COLORREF** pp = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete pp[i];
	}
	delete[] pp;

	return ret;

}

/*
x 整形数: 区域的左上X坐标
y 整形数: 区域的左上Y坐标
w  整形数: 区域的宽度
h  整形数: 区域的高度
pic_name 字符串:图片名,可以是多个图片,比如"test.bmp"
delta_color 字符串:颜色色偏比如"203040" 表示RGB的色偏分别是20 30 40 (这里是16进制表示)
sim 双精度浮点数:相似度,取值范围0.1-1.0
字符串:
返回的是所有找到的坐标格式如下:"id,x,y|id,x,y..|id,x,y" (图片左上角的坐标)
*/
LPVOID DXBind::lwFindPicEx(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim)
{
	if (!::IsWindow(m_hwnd))
	{
		return  0;
	}
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		return 0;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &pic, &bi))
	{
		return 0;
	}

	BITMAPINFO pbi;
	LPVOID data = 0;
	if (!loadBitmap(pic_name, &data, &pbi))
	{
		COLORREF** p = (COLORREF**)pic;
		for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
		{
			delete p[i];
		}
		delete[] pic;
		return  0;
	}
	int    w1 = pbi.bmiHeader.biWidth;
	int	h1 = pbi.bmiHeader.biHeight;
	int x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;
	BOOL ret = FALSE;

	int xxx_t = 0;
	char* retStr = 0, * retStr_t = 0;
	int strdx = 0;
	for (int y = 0; y < y_len; y++)
	{
		xxx_t = 0;
		for (size_t x = 0; x < x_len; x++)
		{
			if (xxx_t > 0)
			{
				if (x < xxx_t)
				{
					continue;
				}
				xxx_t = 0;
			}
			ret = false;
			if (CmpBmpData(pic, data, delta_color, sim, x, y, &pbi))
			{
				ret = true;
				xxx_t = x + w1;
			}
			if (ret)
			{
				int x1 = x, y1 = y, t_dx = strdx;
				if (strdx > 1499)
				{
					break;
				}
				if (GetStrPosLen(&t_dx, &x1, &y1))
				{
					if (strdx == 0)
					{
						t_dx += x1 + y1 + 4;
						retStr = new char[t_dx];
						memset(retStr, 0, t_dx);
						sprintf(retStr, "%d,%d,%d", strdx, x, y);
						strdx++;
					}
					else
					{
						t_dx += x1 + y1 + 5 + strlen(retStr);
						retStr_t = new char[t_dx];
						memset(retStr_t, 0, t_dx);
						sprintf(retStr_t, "%s|%d,%d,%d", retStr, strdx, x, y);
						delete[] retStr;
						retStr = retStr_t;
						retStr_t = 0;
						strdx++;
					}
				}
				else
				{
					delete[] pic;
					delete[] data;
					return 0;
				}
				break;
			}
		}

	}

	COLORREF** p = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete p[i];
	}
	delete[] pic;
	COLORREF** fp = (COLORREF**)data;
	for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
	{
		delete fp[i];
	}
	delete[] fp;

	if (strdx >= 1)
	{
		return retStr;
	}
	return 0;
}