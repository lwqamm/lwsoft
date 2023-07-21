#pragma once
#pragma pack(1)
//BMP�ļ�ͷ
typedef struct _BITMAPS
{
	short type;
	int bfSize;
	short re1, re2;
	int Offbits;
}BITMAPS, * PBITMAPS;


//BMP��Ϣͷ
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
//BMPͼƬ��ѹ����ʽ
#define BI_RGB          (0)
#define BI_BITFIELDS         (3)

//RGB555������
#define RGB555_RED_MASK        (31744)
#define RGB555_GREEN_MASK       (992)
#define RGB555_BLUE_MASK       (31)

//RGB565������
#define RGB565_RED_MASK        (63488)
#define RGB565_GREEN_MASK       (2016)
#define RGB565_BLUE_MASK       (31)

//BMPͼƬ������λ��
#define BMP_8_BIT          (8)
#define BMP_16_BIT         (16)
#define BMP_24_BIT         (24)
#define BMP_32_BIT         (32)

//16λBMPͼƬ���ļ�ͷ��ͼ�����ݵ�ƫ����
#define BMP_16_BIT_BI_BITFIELDS_OFFSET    (66)
#define BMP_16_BIT_BI_RGB_OFFSET     (54)

//8λBMPͼƬ��ɫ��Ĵ�С
#define BMP_8_BIT_OFFSET       (1024)

//BMPͼƬ���ļ�ͷ���̶�14�ֽ�
#define BMP_FILE_HEADER_LENGTH       (14)

#define isNull(ptr)        	(NULL == (ptr))
#define isNotNull(ptr)        (NULL != (ptr))


#define SetRValue(rgb,cor)     * (char*)((DWORD64)&rgb) = cor
#define SetGValue(rgb,cor)     * (char*)((DWORD64)&rgb+1) = cor

#define SetBValue(rgb,cor)     * (char*)((DWORD64)&rgb+2) = cor; 


/*
*�������ܣ���bmpͼƬ���룬���BGRͼ��ͼ����������
*���Σ�	pSrcData(in)	��������bmpͼ������
*		pDstData(out)	�������BGRͼ��
*		pWidth(out)		����bmpͼ��Ŀ�
*		pHeight	(out)	����bmpͼ��ĸ�
*
*����ֵ���ɹ�����0��ʧ�ܷ���-1
*/
BOOL loadBitmap(const LPVOID strPath, LPVOID pDstData, PBITMAPINFO PP);

/*��д��Сд*/
char toUpper_(char* src);//��д��Сд
/*���ܣ�ʮ�����Ƶ����������޳�
����1��ʮ�������ı�
����2�����صĶ������ı�
*/
BOOL HexToBin(const char* str1, char** otr);
/*
����:32λλͼת��24
����1:�����ļ���·��
����2:32λλͼ�ļ�������
����ֵ:����ת�����24λ λͼ������ ����ֱ��
*/
char* Bmp32To24(const char* Filepath, const char* src,bool ret = FALSE);

//��ɫ��䱳��
BOOL  FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr);
/*
����:CDC ��ͼ
����1:���ھ��
����2:x ͼƬ���Ͻ�x
����3:y ͼƬ���Ͻ�y
����4:w ͼƬ���
����5:h ͼƬ�߶�
����6:λͼ�ļ�������
����7:λͼ�ļ���Ϣ
*/
BOOL GetDcPic(HWND hwnd, DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);
/*
x ������:  ���������X����
y ������:  ���������Y����
w  ������: ����Ŀ��
h  ������: ����ĸ߶�
pic_name �ַ���:ͼƬ��,�����Ƕ��ͼƬ,����"test.bmp"
delta_color �ַ���:��ɫɫƫ����"203040" ��ʾRGB��ɫƫ�ֱ���20 30 40 (������16���Ʊ�ʾ)
sim ˫���ȸ�����:���ƶ�,ȡֵ��Χ0.1-1.0
intX ���ָ��:����ͼƬ���Ͻǵ�X����
intY ���ָ��:����ͼƬ���Ͻǵ�Y����
*/
long FindPic(HWND hwnd, int x, int y, int w, int  h, const char* pic_name, const char* delta_color, double sim, int* intX, int* intY);

/*
x ������: ���������X����
y ������: ���������Y����
w  ������: ����Ŀ��
h  ������: ����ĸ߶�
pic_name �ַ���:ͼƬ��,�����Ƕ��ͼƬ,����"test.bmp"
delta_color �ַ���:��ɫɫƫ����"203040" ��ʾRGB��ɫƫ�ֱ���20 30 40 (������16���Ʊ�ʾ)
sim ˫���ȸ�����:���ƶ�,ȡֵ��Χ0.1-1.0
�ַ���:
���ص��������ҵ��������ʽ����:"id,x,y|id,x,y..|id,x,y" (ͼƬ���Ͻǵ�����)
*/
const char* FindPicEx(HWND hwnd, int x, int y, int w, int  h, const char* pic_name, const char* delta_color, double sim);

/*
����:32λλͼת��24
����1:�����ļ���·��
����2:32λλͼ�ļ�������
����3:32λλͼ�ļ���Ϣָ��
����ֵ:����ת�����24λ λͼ������ ����ֱ��
*/
BOOL BmpTo24DataFile(const char* Filepath, const char* src, PBITMAPINFO bmp);

/*
x1 ������ : ���������X����
y1 ������ : ���������Y����
x2 ������ : ���������X����
y2 ������ : ���������Y����
color �ַ��� : ��ɫ ��ʽΪ"RRGGBB-DRDGDB", ����"123456-000000|aabbcc-202020".Ҳ����֧�ַ�ɫģʽ.ǰ���@����.����"@123456-000000|aabbcc-202020".������Կ��·�ע��.ע�⣬����ֻ֧��RGB��ɫ.
sim ˫���ȸ����� : ���ƶ�, ȡֵ��Χ0.1 - 1.0
intX ���ָ��:����X����
intY ���ָ��:����Y����
*/
long FindColor(HWND hwnd, int x1, int y1, int x2, int y2,const char* color,double sim, int* intX,int* intY);