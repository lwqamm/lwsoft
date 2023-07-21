#include "pch.h"
#include "mybmp.h"

#define   PAGE_EXECUTE_FLAGES \
 (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)
//检测目标进程内存是否有效
BOOL UMS_IsExecutableAddress( LPVOID VirtualAddress)
{
	BOOL IsOk = FALSE;
	MEMORY_BASIC_INFORMATION MemoryBasicInfo = { 0 };


	VirtualQuery( VirtualAddress, &MemoryBasicInfo, sizeof(MEMORY_BASIC_INFORMATION));

	

	if ((MemoryBasicInfo.State == MEM_COMMIT &&
		(MemoryBasicInfo.Protect & PAGE_EXECUTE_FLAGES)))
	{
		IsOk = TRUE;
	}
	return IsOk;
}

UINT64 __stdcall HexToInt(const char* strhex1)
{
	UINT64 Dec = 0;
	UINT64 temp = 0;
	UINT64 count = 0;
	UINT64 DecCount = 0;
	//int strlen = aHex.length();
	char* strhex = new char[strlen(strhex1)];
	sprintf(strhex, "%s", strhex1);
	toUpper_(strhex);
	UINT64 StrLen = strlen(strhex); //计算字符串长度
	UINT64 a = 0;
	char ch[3] = { 0 };
	UINT64 b = 0;
	char cahr[256] = { 0 };
	if (StrLen >= 3)
	{
		for (size_t i = 0; i < StrLen; i++)
		{
			memcpy(ch, strhex + i, 2);
			if (strcmp(ch, "0x") == 0)
			{
				b = i + 1;
				break;
			}
		}
		// 00xAAAA
		if (b > 0)
		{
			memcpy(cahr, strhex + (b + 1), StrLen - (b + 1));
			a = StrLen - (b + 1);
		}
		else
		{
			memcpy(cahr, strhex, StrLen);
			a = StrLen;
		}

	}
	else
	{
		memcpy(cahr, strhex, StrLen);
		a = StrLen;
	}
	//MessageBox(NULL, (LPWSTR)cahr, TEXT("提示"), 1);

	StrLen = strlen(cahr);
	if (StrLen == 0)
	{
		if (strhex)
		{
			delete[] strhex;
		}
		return 0;
	}
	while (a--)
	{
		if (cahr[count] < '0' || (cahr[count] > '9' && cahr[count] < 'A') || (cahr[count] > 'F' && cahr[count] < 'a') || cahr[count]>'f')
		{
			//cout << "输入的不是十六进制格式" << endl;
			if (strhex)
			{
				delete[] strhex;
			}
			return 0;
		}
		count++;
	}


	UINT64 sum = 0;             //用long long防止结果过大
	for (UINT64 i = 0; cahr[i] != '\0'; i++)         //最后一位是'\0'，不用算进去
	{
		switch (cahr[i])
		{
		case '0': temp = 0; break;
		case '1': temp = 1; break;
		case '2': temp = 2; break;
		case '3': temp = 3; break;
		case '4': temp = 4; break;
		case '5': temp = 5; break;
		case '6': temp = 6; break;
		case '7': temp = 7; break;
		case '8': temp = 8; break;
		case '9': temp = 9; break;
		case 'A': temp = 10; break;
		case 'B': temp = 11; break;
		case 'C': temp = 12; break;
		case 'D': temp = 13; break;
		case 'E': temp = 14; break;
		case 'F': temp = 15; break;
		case 'a': temp = 10; break;
		case 'b': temp = 11; break;
		case 'c': temp = 12; break;
		case 'd': temp = 13; break;
		case 'e': temp = 14; break;
		case 'f': temp = 15; break;
		default: temp = cahr[i] - '0'; break;
		}
		sum = sum + temp * pow(16, StrLen - 1 - i);
	}
	if (strhex)
	{
		delete[] strhex;
	}
	return sum;
}


/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
参数3:是否保存位图到文件
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
char* Bmp32To24(const char* Filepath, const char* src,bool ret)
{
	PBITMAPINFO BmpInfoHeader = (PBITMAPINFO)((UINT64)src + BMP_FILE_HEADER_LENGTH);
	int N = 4 - ((BmpInfoHeader->bmiHeader.biWidth * 3) % 4);
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = BmpInfoHeader->bmiHeader.biWidth;
	bi.biHeight = BmpInfoHeader->bmiHeader.biHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BMP_24_BIT;
	bi.biCompression = 0;
	bi.biSizeImage = ((BmpInfoHeader->bmiHeader.biWidth * 3) * BmpInfoHeader->bmiHeader.biHeight)+(N * BmpInfoHeader->bmiHeader.biHeight);
	bi.biXPelsPerMeter = BmpInfoHeader->bmiHeader.biXPelsPerMeter;
	bi.biYPelsPerMeter= BmpInfoHeader->bmiHeader.biYPelsPerMeter;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	PBITMAPFILEHEADER pbi = (PBITMAPFILEHEADER)src;
	BITMAPFILEHEADER BiHeder = { 0 };
	BiHeder.bfType = pbi->bfType;
	BiHeder.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	int OffSize = BiHeder.bfSize;
	BiHeder.bfOffBits = BiHeder.bfSize;
	BiHeder.bfSize+= bi.biSizeImage+2;
	BiHeder.bfReserved1 = pbi->bfReserved1;
	BiHeder.bfReserved2 = pbi->bfReserved2;
	char* bmp24 = new char[BiHeder.bfSize];
	if (!bmp24)
	{
		return 0;
	}
	memset(bmp24, 0, BiHeder.bfSize);
	memcpy(bmp24, &BiHeder, sizeof(BITMAPFILEHEADER));
	memcpy(bmp24+ sizeof(BITMAPFILEHEADER), &bi, sizeof(BITMAPINFOHEADER));
	int w = bi.biWidth, h = bi.biHeight;
	int dx=0,dx1=0;
	PCHAR p = (PCHAR)((DWORD64)bmp24 + OffSize);
	PCHAR p1 = (PCHAR)((DWORD64)src+ OffSize);
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			if (j==(w-1))
			{
				memcpy(p+dx,p1+dx1,3);
				dx += N+3;	//必须是4的倍数所以指针往后移动3+N；	
			}
			else
			{
				memcpy(p + dx, p1 + dx1, 3);
				dx +=  3;//每次取四个字中的前3个所以+3
			}

			dx1 += 4;//每次取四个字中的前3个第四个丢弃
		}
	}
	if (ret)
	{
		FILE* fp = NULL;
		fopen_s(&fp, Filepath, "wb+");
		if (NULL == fp)
		{
			//FreeRes_ShowError("LockResource");
			delete[] bmp24;
			return FALSE;
		}
		fwrite(bmp24, sizeof(char), BiHeder.bfSize, fp);
		fclose(fp);
	}

	return bmp24;
}

/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
参数3:是否保存位图到文件
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
LPVOID BmpTo24Data(const LPVOID src, PBITMAPINFO p2, DWORD dwStyle)
{
	if (isNull(src)||isNull(p2))
	{
		return 0;
	}
	int w = p2->bmiHeader.biWidth, h = p2->bmiHeader.biHeight;
	
	
	COLORREF**  pp = new COLORREF*[h];
	for (size_t i = 0; i < h; i++)
	{
		pp[i] = new COLORREF[w];
	}
	if (!pp)
	{
		return 0;
	}
	int N = w * h ;//缓冲区大小
	p2->bmiHeader.biSizeImage = N;


	switch (dwStyle)
	{
	case BMP_32_BIT:
	{
		PUCHAR p = (PUCHAR)src;
		int realPitch = 0;
		for (size_t i = 0; i < h; i++)
		{
			realPitch = w * (h - (i+1)) * 4;
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
			if (N>0)
			{
				N = 4 - ((w * 3) % 4);
			}
		PUCHAR p = (PUCHAR)src;
		int realPitch = 0;
		for (size_t i = 0; i < h; i++)
		{
			realPitch =(w*h*3+N*h)-((w*3 + N)*(i+1));
			for (size_t j = 0; j < w; j++)
			{
				UCHAR b = p[realPitch + (j * 3)];
				UCHAR g = p[realPitch + (j * 3) + 1];
				UCHAR r = p[realPitch + (j * 3) + 2];
				pp[i][j] = RGB(r, g, b);
				if (j==w-1)
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
//0123456789
//

/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
参数3:32位位图文件信息指针
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
BOOL BmpTo24DataFile(const char* Filepath,const char* src, PBITMAPINFO bmp)
{
	if (isNull(src) || isNull(bmp)||isNull(Filepath))
	{
		return FALSE;
	}
	int N = 4 - ((bmp->bmiHeader.biWidth * 3) % 4);
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmp->bmiHeader.biWidth;
	bi.biHeight = bmp->bmiHeader.biHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BMP_24_BIT;
	bi.biCompression = 0;
	bi.biSizeImage = ((bmp->bmiHeader.biWidth * 3) * bmp->bmiHeader.biHeight) + (N * bmp->bmiHeader.biHeight);
	bi.biXPelsPerMeter = bmp->bmiHeader.biXPelsPerMeter;
	bi.biYPelsPerMeter = bmp->bmiHeader.biYPelsPerMeter;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	BITMAPFILEHEADER BiHeder = { 0 };
	BiHeder.bfType = 'MB';
	BiHeder.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	int OffSize = BiHeder.bfSize;
	BiHeder.bfOffBits = BiHeder.bfSize;
	BiHeder.bfSize += bi.biSizeImage + 2;
	BiHeder.bfReserved1 = 0;
	BiHeder.bfReserved2 = 0;

	char* bmp24 = new char[BiHeder.bfSize];
	if (!bmp24)
	{
		return 0;
	}
	memset(bmp24, 0, BiHeder.bfSize);
	memcpy(bmp24, &BiHeder, sizeof(BITMAPFILEHEADER));
	memcpy(bmp24 + sizeof(BITMAPFILEHEADER), &bi, sizeof(BITMAPINFOHEADER));
	int w = bi.biWidth, h = bi.biHeight;
	int dx = 0, dx1 = 0;
	PCHAR p = (PCHAR)((DWORD64)bmp24 + OffSize);
	PCHAR p1 = (PCHAR)src;
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			if (j == (w - 1))
			{
				memcpy(p + dx, p1 + dx1, 3);
				dx += N + 3;	//必须是4的倍数所以指针往后移动3+N；	
			}
			else
			{
				memcpy(p + dx, p1 + dx1, 3);
				dx += 3;//每次取四个字中的前3个所以+3
			}

			dx1 += 4;//每次取四个字中的前3个第四个丢弃
		}
	}

		FILE* fp = NULL;
		fopen_s(&fp, Filepath, "wb+");
		if (NULL == fp)
		{
			//FreeRes_ShowError("LockResource");
			delete[] bmp24;
			return FALSE;
		}
		fwrite(bmp24, sizeof(char), BiHeder.bfSize, fp);
		fclose(fp);
		delete[] bmp24;
		return TRUE;
}

/*大写到小写*/
char toUpper_(char* src)//大写到小写
{
	char* p = NULL;
	p = src;
	while (*p)//字符串不结束就循环
	{
		if (*p >= 'A' && *p <= 'Z') //判断小写字母
			*p += 32; //转大写
		p++; //指针后指，准备处理下一个字母
	}
	return *src; //返回修改后的字符串首地址
}

/*小写到大写*/
char _toUpper_(char* src)//大写到小写
{
	char* p = NULL;
	p = src;
	while (*p)//字符串不结束就循环
	{
		if (*p >= 'a' && *p <= 'z') //判断小写字母
			*p -= 32; //转大写
		p++; //指针后指，准备处理下一个字母
	}
	return *src; //返回修改后的字符串首地址
}

/*功能：十六进制到二进制无限长
参数1：十六进制文本
参数2：返回的二进制文本
*/
BOOL HexToBin(const char* str1, char** otr)
{
	if (isNull(str1)||isNull(otr))
	{
		return FALSE;
	}
	int len=strlen(str1);
	if (!len)
	{
		return FALSE;
	}
	char* str = new char[len+1];
	memset(str, 0, len + 1);
	sprintf(str, "%s", str1);
	toUpper_(str);
	PCHAR p = (PCHAR)str;
	for (size_t i = 0; i < len; i++)
	{
		if (!((p[i] >= '0' && p[i] <= '9') || (p[i] >= 'a' && p[i] <= 'f')))
		{
			delete[] str;
			return FALSE;
		}
	}
	char* t_ch2= new char[len * 4 + 1];
	*otr = t_ch2;
	memset(t_ch2, 0, len*4 + 1);
	for (size_t i = 0; i < len; i++)
	{
		int syew = 0;
		if ((p[i] >= '0' && p[i] <= '9'))
		{
			syew = p[i]-48;
		}
		else if ((p[i] >= 'a' && p[i] <= 'f'))
		{
			syew = p[i] - 87;
		}
		else
		{
			delete[] str;
			delete[] t_ch2;
			return FALSE;
		}

		switch (syew)
		{
		case 0x0:
		{
			char t_ch[] = "0000";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x1:
		{
			char t_ch[] = "0001";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x2:
		{
			char t_ch[] = "0010";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x3:
		{
			char t_ch[] = "0011";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x4:
		{
			char t_ch[] = "0100";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x5:
		{
			char t_ch[] = "0101";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x6:
		{
			char t_ch[] = "0110";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x7:
		{
			char t_ch[] = "0111";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x8:
		{
			char t_ch[] = "1000";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0x9:
		{
			char t_ch[] = "1001";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xA:
		{
			char t_ch[] = "1010";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xB:
		{
			char t_ch[] = "1011";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xC:
		{
			char t_ch[] = "1100";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xD:
		{
			char t_ch[] = "1101";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xE:
		{
			char t_ch[] = "1110";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		case 0xF:
		{
			char t_ch[] = "1111";
			sprintf(t_ch2 + strlen(t_ch2), "%s", t_ch);
			break;
		}
		break;
		}
	}

	delete[] str;
	return TRUE;
}

//32位图数据转换成24位位图数据：
unsigned char* RGB32TO24(unsigned char* src, int width, int height)
{
	uint8_t* data = NULL;
	uint32_t src_row_bytes;
	uint32_t dst_row_bytes;
	uint32_t off;
	int i, j;
	uint32_t* ptr;
	uint8_t* img;
	uint32_t color;
	int pad;

	src_row_bytes = width << 2;
	dst_row_bytes = (width * 3 + 3) & ~3;
	pad = dst_row_bytes - width * 3;

	data = (uint8_t*)malloc(dst_row_bytes * height);
	if (!data)
	{
		return NULL;
	}

	off = (height - 1) * dst_row_bytes;
	ptr = (uint32_t*)src;

	for (i = 0; i < height; i++)
	{
		img = data + off;
		for (j = 0; j < width; j++)
		{
			color = *ptr++;
			*img++ = color & 0x000000FF;
			*img++ = (color >> 8) & 0x000000FF;
			*img++ = (color >> 16) & 0x000000FF;
		}
		off -= dst_row_bytes;
	}
	return data;
}
//24位位图转换成32位位图：
unsigned char* RGB24TO32(unsigned char* src, int width, int height)
{
	uint8_t* data;
	int row_bytes;
	int i, j;
	uint8_t* dst;
	uint8_t* ptr;
	//int src_pad;
	uint32_t off;

	row_bytes = (width * 3 + 3) & ~3;
	data = (uint8_t*)malloc(width * 4 * height);
	if (!data)
		return NULL;
	off = (height - 1) * row_bytes;
	dst = data;
	for (i = 0; i < height; i++)
	{
		ptr = src + off;
		for (j = 0; j < width; j++)
		{
			*dst++ = *ptr++;
			*dst++ = *ptr++;
			*dst++ = *ptr++;
			*dst++ = 0;
		}
		off -= row_bytes;
	}
	return data;
}

/*
功能： 打开本地位图文件
参数1:位图文件路径
参数2:位图文件缓冲区
参数3:位图文件信息
返回值:成功返回TRUE 失败返回FALSE
*/
BOOL loadBitmap(const char* strPath, LPVOID outdata,PBITMAPINFO PP)
{
	HANDLE hFile = CreateFile(strPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD fileSize = GetFileSize(hFile, NULL);    //获得文件大小的低两字节
	char* pSrcData = new char[fileSize];    //创建缓冲区
	DWORD realRead = 0;
	BOOL ret = false;
	ret = ReadFile(hFile, pSrcData, fileSize, &realRead, NULL);    //拷贝文件的内容给缓冲区fileBuff
	CloseHandle(hFile);

	if (ret)
	{
		BITMAPINFO BmpInfoHeader;

		//BITMAP fHeader;

		if (isNull(pSrcData) || isNull(outdata))
		{

			delete[] pSrcData;

			return FALSE;
		}

		//根据前两个字节，判断是不是BMP图片
		if ((pSrcData[0] != 'B') || (pSrcData[1] != 'M'))
		{
			//printf("not a bmp picture.\n");
			delete[] pSrcData;
			return FALSE;
		}

		//获取信息头
		memcpy(&BmpInfoHeader, pSrcData + BMP_FILE_HEADER_LENGTH, sizeof(BmpInfoHeader));
		*(PBITMAPINFO) PP = BmpInfoHeader;
		//将宽高信息传递出去
		//int N = 4 - ((width * 3) % 4);
		//判断BMP图片像素的位数
		if (BmpInfoHeader.bmiHeader.biBitCount == BMP_24_BIT)
		{
			int bioff = sizeof(BITMAPFILEHEADER)+ BmpInfoHeader.bmiHeader.biSize;
			LPVOID chta = BmpTo24Data((LPVOID)((DWORD64)pSrcData + bioff), &BmpInfoHeader, BMP_24_BIT);

			//delete[] chta;
			delete[] pSrcData;
			*(LPVOID*)outdata = chta;
			return TRUE;
		}
		else if (BmpInfoHeader.bmiHeader.biBitCount == BMP_32_BIT)
		{

			LPVOID chta = BmpTo24Data((char*)((DWORD64)pSrcData + ((PBITMAPFILEHEADER)pSrcData)->bfOffBits), &BmpInfoHeader,BMP_32_BIT);

			//delete[] chta;
			delete[] pSrcData;
			* (LPVOID*)outdata = chta;
			return TRUE;
			//return TRUE;
		}


	}
	if (pSrcData)
	{
		delete[] pSrcData;
	}
	return FALSE;
}

//纯色填充背景
BOOL FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr)
{
	ENSURE(dc != NULL);
	ENSURE(lpRect);

	DWORD dw = ::SetBkColor(dc, clr);
	BOOL ret = ::ExtTextOut(dc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	::SetBkColor(dc, dw);
	return	ret;
}

BOOL SetXy(HWND hwnd,int* x,int* y,int* w,int* h)
{
	RECT rtcc;
	::GetClientRect(hwnd, &rtcc);
	if (*x < 0)
	{
		*(int*)x = 0;
	}
	else if (*x >= rtcc.left + rtcc.right)
	{
		return FALSE;
	}
	if (*y < 0)
	{
		*(int*)y = 0;
	}
	else if (*y >= rtcc.top + rtcc.bottom)
	{
		return FALSE;
	}
	if (*w <= 0)
	{
		return FALSE;
	}
	else if (*w >= rtcc.left + rtcc.right)
	{
		*(int*)w = rtcc.left + rtcc.right;
	}
	if (*h <= 0)
	{
		return FALSE;
	}
	else if (*h >= rtcc.top + rtcc.bottom)
	{
		*(int*)h = rtcc.top + rtcc.bottom;
	}
	return TRUE;
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
BOOL GetDcPic(HWND hwnd,DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP)
{
	if (!::IsWindow(hwnd))
	{
		return FALSE;
	}
	if (!SetXy(hwnd,(int*)&x, (int*) &y, (int*)&w, (int*)&h))
	{
		return FALSE;
	}
	
	HDC pdc = GetDC(hwnd);//获得窗口画图设备句柄
	HDC cacheDC = CreateCompatibleDC(pdc);//创建兼容DC
	HBITMAP HEditBmp = CreateCompatibleBitmap(pdc,w, h); //内存编辑框位图
	HBITMAP pOHEditmap = (HBITMAP)::SelectObject(cacheDC, HEditBmp);        //内存画编辑框位图

	RECT rct;
	rct.left = x;
	rct.top = y;
	rct.right = x + w;
	rct.bottom = y + h;
	FillSolidRect(cacheDC, &rct, RGB(0xFF, 0xFF, 0xFF));
	::BitBlt(cacheDC,0, 0, w, h, pdc, x, y, SRCCOPY);

	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	::GetDIBits(cacheDC, HEditBmp, 0, h, NULL, &bi, DIB_RGB_COLORS);

	char* data = new char[bi.bmiHeader.biSizeImage + 2];
	if (!data)
	{
		return FALSE;
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
		return FALSE;
	}

	*(PBITMAPINFO) PP = bi;
	*(LPVOID*)outdata = pbi;
	delete[] data;
	return TRUE;
}
/*
图像缓冲区比较

*/
long CmpBmpData(const LPVOID pic, const LPVOID pic1, const char* delta_color, double sim,int x, int y, PBITMAPINFO PP)
{
	if (isNull(pic)||isNull(pic1) || isNull(delta_color) || isNull(PP))
	{
		return 0;
	}

    //处理偏色
	int R = 0, G = 0, B = 0;
	if (strlen(delta_color)>=6)
	{
		char tch[3] = { 0 };
		memset(tch, 0, 3);
		memcpy(tch,  delta_color,2);
		StrToIntEx(tch, STIF_SUPPORT_HEX, &R);
		memset(tch, 0, 3);
		memcpy(tch, delta_color+2, 2);
		StrToIntEx(tch, STIF_SUPPORT_HEX,&G);
		memset(tch, 0, 3);
		memcpy(tch, delta_color + 4, 2);
		StrToIntEx(tch, STIF_SUPPORT_HEX, &B);
	}

	COLORREF** p = (COLORREF**)pic, **p1 = (COLORREF**)pic1;
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
	BOOL ret = FALSE;

	if (p1[0][0] ==p1[0][PP->bmiHeader.biWidth-1]&& p1[0][0] ==p1[PP->bmiHeader.biHeight-1][0] && p1[0][0] == p1[PP->bmiHeader.biHeight - 1][PP->bmiHeader.biWidth - 1])
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
		if (len== PP->bmiHeader.biHeight* PP->bmiHeader.biWidth)
		{
			ret = FALSE;
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
				if (p1[0][0]== p1[i][j])
				{
					continue;//过滤掉透明色
				}
			}
			pLoadColor = p[y+i][x+j];
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
long FindPic(HWND hwnd, int x_1, int y_1, int w_1, int  h_1, const char* pic_name, const char* delta_color, double sim, int* intX, int* intY)
{
	if (!::IsWindow(hwnd))
	{
		*(int*)intX = -1;
		*(int*)intY = -1;
		return -1;
	}
    if (!SetXy(hwnd,&x_1,&y_1,&w_1,&h_1))
    {
		*(int*)intX = -1;
		*(int*)intY = -1;
    	return -2;
    }
	LPVOID pic = 0;
	BITMAPINFO bi = {0};
	if (!GetDcPic(hwnd, x_1, y_1, w_1, h_1, &pic, &bi))
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
         int    w1 = pbi.bmiHeader.biWidth ;
         int	h1 = pbi.bmiHeader.biHeight ;
		 int x_len = w_1-w1+1, y_len = h_1-h1+1;
		 BOOL ret = FALSE;

		 for (int y = 0; y < y_len; y++)
		 {
			 for (size_t x = 0; x < x_len; x++)
			 {
				 ret = FALSE;
				 if (CmpBmpData(pic,data,delta_color,sim,x,y,&pbi))
				 {
					 ret = TRUE;
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

//返回系列字符所需要的空间
int GetStrPosLen(int* dx,int* x,int* y)
{
	if (isNull(dx)|| isNull(x)|| isNull(y))
	{
		return 0;
	}
	if (*dx>=0&&*dx<=9)
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
const char* FindPicEx(HWND hwnd,int x_1, int y_1, int w_1, int  h_1, const char* pic_name, const char* delta_color, double sim)
{
	if (!::IsWindow(hwnd))
	{
		return  "-1";
	}
	if (!SetXy(hwnd, &x_1, &y_1, &w_1, &h_1))
	{
		return "-2";
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(hwnd, x_1, y_1, w_1, h_1, &pic, &bi))
	{
		return "-3";
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
		return  "-4";
	}
	int    w1 = pbi.bmiHeader.biWidth;
	int	h1 = pbi.bmiHeader.biHeight;
	int x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;
	BOOL ret = FALSE;

	int xxx_t = 0;
	char* retStr = 0, *retStr_t = 0;
	int strdx = 0;
	for (int y = 0; y < y_len; y++)
	{
		xxx_t = 0;
		for (size_t x = 0; x < x_len; x++)
		{
			if (xxx_t>0)
			{
				if (x< xxx_t)
				{
					continue;
				}
				xxx_t = 0;
			}
			ret = FALSE;
			if (CmpBmpData(pic, data, delta_color, sim, x, y, &pbi))
			{
				ret = TRUE;
				xxx_t = x+w1;
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
					return "-7";
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

	if (strdx>=1)
	{
		return retStr;
	}
	return "-8";


}

long FindColor(HWND hwnd, int x1, int y1, int w1, int h1, const char* color, double sim, int* intX, int* intY)
{
	if (!::IsWindow(hwnd)||isNull(color))
	{
		return  0;
	}
	if (!SetXy(hwnd, &x1, &y1, &w1, &h1))
	{
		return 0;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(hwnd, x1, y1, w1, h1, &pic, &bi))
	{
		return 0;
	}
	BOOL ret = FALSE;
	int stlen = 0,slen=strlen(color);

	PCHAR p = (PCHAR)color;
	char** colorStr = 0;
	for (size_t i = 0; i < slen; i++)
	{
		if (p[i]=='|')
		{
			stlen++;
		}
	}
	stlen += 1;
	colorStr = new char*[stlen];
	int sart = 0,sEnd=0;
	for (size_t i = 0; i < stlen; i++)
	{
		sart = sEnd;
		for (size_t j = sart; j < slen; j++)
		{
			
			if (p[j] == '|'||j==slen-1)
			{
				sEnd = j;
				break;
			}
		}

	
		if (i>0)
		{
			colorStr[i] = new char[sEnd - sart+2];
			memset(colorStr[i], 0, sEnd - sart+2);
			if (sEnd!=slen-1&&sart!=0)
			{
				memcpy(colorStr[i], p + sart, sEnd - sart );
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
			memcpy(colorStr[i], p + sart, sEnd - sart+1);
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

		if (sim >= 0.1&& sim <= 0.19)
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
	COLORREF pLoadColor = 0, pWndColor = 0,pRGB=0;
	COLORREF** p1 = (COLORREF**)pic;
	
	for (size_t y = 0; y < bi.bmiHeader.biHeight; y++)
	{
		ret = FALSE;
		for (size_t x = 0; x < bi.bmiHeader.biWidth; x++)
		{
			pLoadColor = p1[y ][x];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			for (size_t k = 0; k < stlen; k++)
			{
				if (strlen(colorStr[k])!=13)
				{
					return 0;
				}
				char t_ch[3] = { 0 };
				memcpy(t_ch, colorStr[k],2);
		
				wndR = HexToInt(t_ch);
				
				memset(t_ch, 0, 3);
				memcpy(t_ch, colorStr[k]+2, 2);
				wndG=HexToInt(t_ch);
		
				memset(t_ch , 0, 3);
				memcpy(t_ch, colorStr[k] + 4, 2);
				wndB = HexToInt(t_ch);

				memset(t_ch , 0, 3);
			 memcpy(t_ch, colorStr[k] + 7, 2);
			 R = HexToInt(t_ch);

			 memset(t_ch , 0, 3);
			 memcpy(t_ch, colorStr[k] + 9, 2);
			 G = HexToInt(t_ch);

			 memset(t_ch , 0, 3);
			 memcpy(t_ch, colorStr[k] + 11, 2);
			 B = HexToInt(t_ch);


				//用于偏色比较
				if (abs(loadR - wndR) <=    (R + simColor)
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