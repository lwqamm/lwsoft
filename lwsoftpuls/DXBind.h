#pragma once
class DXBind
{
public:
	//�󶨴���
	STDMETHODIMP Bind(LONG hwnd);
	//����Ĭ�ϲ���·��
	bool  lwSetpath(const char* path);
	//��ͼ��������
 long lwFindPic( int x_1, int y_1, int w_1, int  h_1, BSTR pic_name, BSTR delta_color, double sim, int* intX, int* intY);
 //��ɫ��������
 long lwFindColor( int x1, int y1, int w1, int h1, BSTR color, double sim, int* intX, int* intY);
 //��ͼ��������ϵ��
 LPVOID lwFindPicEx(int x_1, int y_1, int w_1, int h_1, BSTR pic_name, BSTR delta_color, double sim);

private:
	//��������Ƿ�Խ��
	bool SetXy(int* x, int* y, int* w, int* h);
	//��ɫ��䱳��
	bool FillSolidRect(HDC dc, LPCRECT lpRect, COLORREF clr);
	//���ļ�����24λͼ
	bool loadBitmap(BSTR strPath, LPVOID outdata, PBITMAPINFO PP);
	//���λͼBUFF
	LPVOID BmpTo24Data(const LPVOID src, PBITMAPINFO p2, DWORD dwStyle);
	//�Ӵ��ڼ���λͼ
	bool GetDcPic( DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP);
    //ͼ�񻺳����Ƚ�
	long CmpBmpData(const LPVOID pic, const LPVOID pic1, BSTR delta_color, double sim, int x, int y, PBITMAPINFO PP);
	//����ϵ���ַ�����Ҫ�Ŀռ�
	int  GetStrPosLen(int* dx, int* x, int* y);

public:
	HWND m_hwnd;            //���󶨵Ĵ��ڵľ��
	TCHAR m_SetPath[MAX_PATH*2];//Ĭ�ϲ�����
public:
	DXBind(void);
	~DXBind(void);
};

