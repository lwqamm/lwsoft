#pragma once
#pragma pack(1)
//BMP文件头
typedef struct _BITMAPS
{
	short type;
	int bfSize;
	short re1, re2;
	int Offbits;
}BITMAPS, * PBITMAPS;


//BMP信息头
typedef  struct _BITINFO
{
	int size;
	int width, height;
	short planes, bitCount;
	int comp, sizeImg;
	int xpels, ypels;
	int used, important;
}BITINFO, * PBITINFO;

typedef struct _MyRGB
{
public:
	CHAR B = 0;
	CHAR G = 0;
	CHAR R = 0;
	bool operator == (const _MyRGB& rhs)
	{
		return ((R == rhs.R) && (G == rhs.G) && (B == rhs.B));
	}
	bool operator == (const COLORREF& rhs)
	{
		return ((R == GetRValue(rhs)) && (G == GetGValue(rhs)) && (B == GetBValue(rhs)));
	}
	bool operator != (const _MyRGB& rhs)
	{
		return ((R != rhs.R) || (G != rhs.G) || (B != rhs.B));
	}
	void operator = (const _MyRGB& rhs)
	{
		R = rhs.R;
		G = rhs.G;
		B = rhs.B;
		return;
	}
	void operator = (const COLORREF& rhs)
	{
		R = GetRValue(rhs);
		G = GetGValue(rhs);
		B = GetBValue(rhs);;
		return;
	}
	//void operator = (const int& rhs)
	//{
	//	R = rhs.R;
	//	G = rhs.G;
	//	B = rhs.B;
	//	return;
	//}
}MyRGB, * PMyRGB, * LPMyRGB;

#pragma pack(0)
//BMP图片的压缩方式
#define BI_RGB          (0)
#define BI_BITFIELDS         (3)

//RGB555的掩码
#define RGB555_RED_MASK        (31744)
#define RGB555_GREEN_MASK       (992)
#define RGB555_BLUE_MASK       (31)

//RGB565的掩码
#define RGB565_RED_MASK        (63488)
#define RGB565_GREEN_MASK       (2016)
#define RGB565_BLUE_MASK       (31)

//BMP图片的像素位数
#define BMP_8_BIT          (8)
#define BMP_16_BIT         (16)
#define BMP_24_BIT         (24)
#define BMP_32_BIT         (32)

//16位BMP图片从文件头到图像数据的偏移量
#define BMP_16_BIT_BI_BITFIELDS_OFFSET    (66)
#define BMP_16_BIT_BI_RGB_OFFSET     (54)

//8位BMP图片调色板的大小
#define BMP_8_BIT_OFFSET       (1024)

//BMP图片的文件头，固定14字节
#define BMP_FILE_HEADER_LENGTH       (14)

#define isNull(ptr)        	(NULL == (ptr))
#define isNotNull(ptr)        (NULL != (ptr))


#define SetRValue(rgb,cor)     * (char*)((DWORD64)&rgb) = cor
#define SetGValue(rgb,cor)     * (char*)((DWORD64)&rgb+1) = cor

#define SetBValue(rgb,cor)     * (char*)((DWORD64)&rgb+2) = cor; 


/*
*函数功能：将bmp图片传入，输出BGR图像，图像方向是正的
*传参：	pSrcData(in)	——输入bmp图像数据
*		pDstData(out)	——输出BGR图像
*		pWidth(out)		——bmp图像的宽
*		pHeight	(out)	——bmp图像的高
*
*返回值：成功返回0，失败返回-1
*/
BOOL loadBitmap(const LPVOID strPath, LPVOID pDstData, PBITMAPINFO PP);

/*大写到小写*/
char toUpper_(char* src);//大写到小写
/*功能：十六进制到二进制无限长
参数1：十六进制文本
参数2：返回的二进制文本
*/
BOOL HexToBin(const char* str1, char** otr);
/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
char* Bmp32To24(const char* Filepath, const char* src,bool ret = FALSE);

//纯色填充背景
BOOL  FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr);
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
BOOL GetDcPic(HWND hwnd, DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);
/*
x 整形数:  区域的左上X坐标
y 整形数:  区域的左上Y坐标
w  整形数: 区域的宽度
h  整形数: 区域的高度
pic_name 字符串:图片名,可以是多个图片,比如"test.bmp"
delta_color 字符串:颜色色偏比如"203040" 表示RGB的色偏分别是20 30 40 (这里是16进制表示)
sim 双精度浮点数:相似度,取值范围0.1-1.0
intX 变参指针:返回图片左上角的X坐标
intY 变参指针:返回图片左上角的Y坐标
*/
long FindPic(HWND hwnd, int x, int y, int w, int  h, const char* pic_name, const char* delta_color, double sim, int* intX, int* intY);

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
const char* FindPicEx(HWND hwnd, int x, int y, int w, int  h, const char* pic_name, const char* delta_color, double sim);

/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
参数3:32位位图文件信息指针
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
BOOL BmpTo24DataFile(const char* Filepath, const char* src, PBITMAPINFO bmp);

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
long FindColor(HWND hwnd, int x1, int y1, int x2, int y2,const char* color,double sim, int* intX,int* intY);