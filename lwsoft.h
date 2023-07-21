#pragma once
#ifndef __INCLUDE_BOJ_H__
#define __INCLUDE_BOJ_H__

#define  LW_KEY        1
#define  LW_MOUSE      2

#include <objbase.h>
#pragma pack (1)
class lwsoft
{
private:
	IDispatch* obj;
public:
	lwsoft();
	virtual ~lwsoft();
	//ָ����������
	virtual long BindWindow(long hwnd );
	//����󶨴���,���ͷ�ϵͳ��Դ.һ����
	virtual long UnBindWindow();
	//���ô��ڵ�״̬
	virtual long SetWindowState(long hwnd, long flag);
	//���ô��ڵ�͸����
	virtual long SetWindowTransparent(long hwnd, long trans);
	//���ô��ڵı���
	virtual long  SetWindowText(long hwnd, const TCHAR* title);
	//���ô��ڵĴ�С
	virtual long SetWindowSize(long hwnd, long width, long hight);
	//���ô��ڿͻ�����Ŀ�Ⱥ͸߶�
	virtual long SetClientSize(long hwnd, long width, long height);
	//�ƶ�ָ�����ڵ�ָ��λ��
	virtual long MoveWindow(LONG hwnd, LONG x, LONG y);
	//����Ļ����ת��Ϊ��������
	virtual long ScreenToClient(LONG hwnd, LONG* x, LONG* y);
	virtual long ScreenToClient(LONG hwnd, int* x, int* y);
	//��ָ�����ڷ���ճ������. �Ѽ���������ݷ��͵�Ŀ�괰��.
	virtual long SendPaste(LONG hwnd);
	//��ȡ�����������
	virtual CString GetClipboard();
	//���ü����������
	virtual long SetClipboard(const TCHAR* values);
	//��ָ�����ڷ����ı�����
	virtual long SendString(long hwnd, const TCHAR* str);
	//��ָ�����ڷ����ı�����2
	virtual long SendString2(LONG hwnd, const TCHAR* str);



	//��ȡ���ڵı���
	virtual CString GetWindowTitle(LONG hwnd);
	//��ȡָ���������ڵ��߳�ID.
	virtual long GetWindowThreadProcessId(long  hWnd);
	//��ȡָ���������ڵĽ���ID.
	virtual long GetWindowProcessId(long hwnd);
	//��ȡָ���������ڵĽ��̵�exe�ļ�ȫ·��.
	virtual CString GetWindowProcessPath(LONG hwnd);
	//��ȡ��������Ļ�ϵ�λ��
	virtual long GetWindowRect(long hwnd, LONG* x1, long* y1, long* x2, long* y2);
	virtual long GetWindowRect(long hwnd, int* x1, int* y1, int* x2, int* y2);
	//��ȡ���ڵ�����
	virtual CString GetWindowClass(long hwnd);
	//��ȡָ�����ڵ�һЩ����
	virtual long GetWindowState(LONG hwnd, LONG flag);
	//��ȡ���ⴰ��
	virtual long GetSpecialWindow(LONG flag);
	//��ȡ����������صĴ��ھ��
	virtual long GetWindow(long hwnd, long flag);
	//��ȡ���ָ��Ŀɼ����ھ��
	virtual long GetMousePointWindow();
	//��ȡ��������Ŀɼ����ھ��
	virtual long GetPointWindow(long x, long y);
	//��ȡ��������,���Ի�ȡ�������Դ�����޷���ȡ���ľ��
	virtual long GetForegroundWindow();
	//��ȡ���������о������뽹��Ĵ��ھ�� 
	virtual long GetForegroundFocus();
	//�������뽹�㵽����
	virtual long SetForegroundFocus(long hwnd);
	//��ȡ���ڿͻ�����Ŀ�Ⱥ͸߶�
	virtual long GetClientSize(long hwnd, LONG* w, LONG* h);
	virtual long GetClientSize(long hwnd, int* w, int* h);
	//��ȡ���ڿͻ���������Ļ�ϵ�λ��
	virtual long GetClientRect(LONG hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2);
	virtual long GetClientRect(LONG hwnd, int* x1, int* y1, int* x2, int* y2);
	//���ҷ����������߱������Ķ���ɼ�����,���ָ����parent,����parent�ĵ�һ���Ӵ����в���.
	virtual long  FindWindowEx(LONG parent, const TCHAR* class_name, const TCHAR* title);
	//���ҷ����������߱������Ķ���ɼ�����
	virtual long FindWindow(const TCHAR* class_name, const TCHAR* title);
	//����ָ�������Լ���������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	virtual CString EnumWindowByProcess(const TCHAR* process_name, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//����ָ������pid�Լ���������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	virtual CString EnumWindowByProcessId(long pid, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//����ָ��������,ö��ϵͳ�з��������Ľ���PID,���Ұ��ս��̴�˳������.
	virtual CString EnumProcess(const TCHAR* name);
	//����ָ������,ö��ϵͳ�з��������Ĵ���,����ö�ٵ������Դ����޷�ö�ٵ��Ĵ���
	virtual CString EnumWindow(LONG parent, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//ϵͳ����ƪ
//��⵱ǰϵͳ�Ƿ��п�����Ļ����ƽ��.
	virtual long CheckFontSmooth();
	//�رյ�ǰϵͳ��Ļ����ƽ��.ͬʱ�ر�ϵͳ��ClearType����.
	virtual long DisableFontSmooth();
	//������ǰϵͳ��Ļ����ƽ��.ͬʱ����ϵͳ��ClearType����.
	virtual long EnableFontSmooth();
	//��⵱ǰϵͳ�Ƿ��п���UAC(�û��˻�����).
	virtual long CheckUAC();
	//���õ�ǰϵͳ��UAC(�û��˻�����).
	virtual long SetUAC(LONG enable);
	//��ʱָ���ĺ���,�����в�����UI����. һ��߼�����ʹ��.�����ò���.
	virtual long Delay(long mis);
	//��ʱָ����Χ���������,�����в�����UI����. һ��߼�����ʹ��.�����ò���.
	virtual long Delays(long mis_min, long  mis_max);
	//�˳�ϵͳ(ע�� ���� �ػ�) 
	virtual long ExitOs(long type);
	//�õ�ϵͳ��·�� 
	virtual CString GetDir(long type);
	//��ȡ��ǰCPU����(intel����amd).
	virtual long GetCpuType();
	//��ȡ��ǰCPU��ʹ����. �ðٷֱȷ���.
	virtual long GetCpuUsage();
	//��ȡ������ָ��Ӳ�̵����к�. Ҫ����ý��̱����й���ԱȨ��. ���򷵻ؿմ�.
	virtual CString GetDiskSerial(long index);
	//��ȡ�������Կ���Ϣ.
	virtual CString  GetDisplayInfo();
	//�жϵ�ǰϵͳ��DPI(��������)�ǲ���100%����.
	virtual long GetDPI();
	//����ָ����Ӧ�ó���.���ؽ���PID
	virtual long RunApp(const TCHAR* path, long type = 0);
	//ȡӲ��������
	virtual long long GetHDiskCode();
	//��ȡCPU���к�
	virtual CString GetCpuCode();
	//��ȡBOIS��������
	virtual long long GetMainBoardInfoByCmd();
	//��ȡ�����Ļ�����.(������). 
	virtual CString GetMachineCode();
	//��ȡ�����Ļ�����.(������). 
	virtual CString GetMachineCodeNoMac();
	//�������ȡ��ǰ����ʱ��.
	virtual CString GetNetTime();
	//����ָ��ʱ�������IP,�������ȡ��ǰ����ʱ��.
	virtual CString GetNetTimeByIp(const TCHAR* ip);
	//�õ�����ϵͳ��build�汾��.  ����win10 16299,��ô���صľ���16299. ��������
	virtual long GetOsBuildNumber();
	//�õ�����ϵͳ������
	virtual long GetOsType();
	//��ȡ��ǰϵͳ�ӿ�������������������ʱ�䣬��λ�Ǻ���
	virtual long GetTime();
	//�жϵ�ǰϵͳ�Ƿ�Ϊ64λ
	virtual BOOL Is64Bit();
	//�жϵ�ǰCPU�Ƿ�֧��vt,�����Ƿ���bios�п�����vt. ��֧��intel��CPU.
	virtual long IsSurrpotVt();
	//��ȡ��Ļ��ɫ��
	virtual long GetScreenDepth();
	//������Ļ��ɫ��
	virtual long SetScreenDepth(long dmBitsPerPel);
	//��ȡ��Ļ�ĸ߶�
	virtual long  GetScreenHeight();
	//��ȡ��Ļ�ĸ߶�
	virtual long  GetScreenWidth();
	//����ϵͳ�ķֱ��� ϵͳɫ�� 
	virtual long SetScreen(long width, long height);
	//����ϴ�APi����
	virtual long GetLastError();
	//��ͼ
	virtual long FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, LONG* longX, LONG* longY);
	virtual long FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, int* intX, int* intY);
	//��ͼ��������ϵ��
	virtual CString FindPicEx(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim);
	virtual long    FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, long* longX, long* longY);
	virtual long    FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, int* intX, int* intY);
	//����ָ�������ڵ���ɫ��,��ɫ��ʽ"RRGGBB-020202",
	virtual long FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, long* intX, long* intY);
	virtual long FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, int* intX, int* intY);

	//32λͼƬת��24λλͼ ����3�Ƿ񸲸�ԭ����
	virtual long Bmp32To24(const TCHAR* Filepath, const TCHAR* FilepathBak, int ret);
	//ȡ����汾��
	virtual CString Ver();
	//ץȡָ������(x1, y1, x2, y2)��ͼ��,����Ϊfile(24λλͼ)
	virtual long Capture(long x, long y, long w, long h, const TCHAR* file);
	//�Ƚ�ָ�������(x,y)����ɫ
	virtual long CmpColor(long x, long y, const TCHAR* color, double sim);
	//��ȡ(x,y)����ɫ,��ɫ���ظ�ʽ"RRGGBB"
	virtual CString GetColor(long x, long  y);
	//��ȡָ���������ɫ����, ��ɫ��ʽ"RRGGBB-DRDGDB"
	virtual long GetColorNum(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim);
	//�������
	virtual long IsDisplayDead(long x, long y, long w, long h, long t);
	//���ò�����������
	virtual long SetPath(const TCHAR* patht);
	//����ʶ��
//�����ֿ��ļ�
	BOOL SetDict(const TCHAR* file);
	//����Ļ��Χ(x1,y1,x2,y2)��,����string(������������ַ��������),�����ط���color_format������λ��
	long FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, long* intX, long* intY);
	long FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, int* intX, int* intY);
	//����Ļ��Χ(x1,y1,x2,y2)��,����string(�����������ַ��������),�����ط���color_format����������λ��,���ƶ�simͬOcr�ӿ�����.
	virtual CString FindStrEx(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim);
	//ʶ����Ļ��Χ(x1,y1,x2,y2)�ڷ���color_format���ַ���,�������ƶ�Ϊsim,simȡֵ��Χ(0.1-1.0),
	virtual CString Ocr(long x_1, long y_1, long w_1, long h_1, const TCHAR* color_format, double  sim);
	//������
//������ƶ���Ŀ�ĵ�(x,y)
	virtual long MoveTo(long x, long y);
	//����������
	virtual long LeftClick();


};
#pragma pack (0)
#endif