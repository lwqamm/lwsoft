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
	//指定操作窗口
	virtual long BindWindow(long hwnd );
	//解除绑定窗口,并释放系统资源.一般在
	virtual long UnBindWindow();
	//设置窗口的状态
	virtual long SetWindowState(long hwnd, long flag);
	//设置窗口的透明度
	virtual long SetWindowTransparent(long hwnd, long trans);
	//设置窗口的标题
	virtual long  SetWindowText(long hwnd, const TCHAR* title);
	//设置窗口的大小
	virtual long SetWindowSize(long hwnd, long width, long hight);
	//设置窗口客户区域的宽度和高度
	virtual long SetClientSize(long hwnd, long width, long height);
	//移动指定窗口到指定位置
	virtual long MoveWindow(LONG hwnd, LONG x, LONG y);
	//把屏幕坐标转换为窗口坐标
	virtual long ScreenToClient(LONG hwnd, LONG* x, LONG* y);
	virtual long ScreenToClient(LONG hwnd, int* x, int* y);
	//向指定窗口发送粘贴命令. 把剪贴板的内容发送到目标窗口.
	virtual long SendPaste(LONG hwnd);
	//获取剪贴板的内容
	virtual CString GetClipboard();
	//设置剪贴板的内容
	virtual long SetClipboard(const TCHAR* values);
	//向指定窗口发送文本数据
	virtual long SendString(long hwnd, const TCHAR* str);
	//向指定窗口发送文本数据2
	virtual long SendString2(LONG hwnd, const TCHAR* str);



	//获取窗口的标题
	virtual CString GetWindowTitle(LONG hwnd);
	//获取指定窗口所在的线程ID.
	virtual long GetWindowThreadProcessId(long  hWnd);
	//获取指定窗口所在的进程ID.
	virtual long GetWindowProcessId(long hwnd);
	//获取指定窗口所在的进程的exe文件全路径.
	virtual CString GetWindowProcessPath(LONG hwnd);
	//获取窗口在屏幕上的位置
	virtual long GetWindowRect(long hwnd, LONG* x1, long* y1, long* x2, long* y2);
	virtual long GetWindowRect(long hwnd, int* x1, int* y1, int* x2, int* y2);
	//获取窗口的类名
	virtual CString GetWindowClass(long hwnd);
	//获取指定窗口的一些属性
	virtual long GetWindowState(LONG hwnd, LONG flag);
	//获取特殊窗口
	virtual long GetSpecialWindow(LONG flag);
	//获取给定窗口相关的窗口句柄
	virtual long GetWindow(long hwnd, long flag);
	//获取鼠标指向的可见窗口句柄
	virtual long GetMousePointWindow();
	//获取给定坐标的可见窗口句柄
	virtual long GetPointWindow(long x, long y);
	//获取顶层活动窗口,可以获取到按键自带插件无法获取到的句柄
	virtual long GetForegroundWindow();
	//获取顶层活动窗口中具有输入焦点的窗口句柄 
	virtual long GetForegroundFocus();
	//设置输入焦点到窗口
	virtual long SetForegroundFocus(long hwnd);
	//获取窗口客户区域的宽度和高度
	virtual long GetClientSize(long hwnd, LONG* w, LONG* h);
	virtual long GetClientSize(long hwnd, int* w, int* h);
	//获取窗口客户区域在屏幕上的位置
	virtual long GetClientRect(LONG hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2);
	virtual long GetClientRect(LONG hwnd, int* x1, int* y1, int* x2, int* y2);
	//查找符合类名或者标题名的顶层可见窗口,如果指定了parent,则在parent的第一层子窗口中查找.
	virtual long  FindWindowEx(LONG parent, const TCHAR* class_name, const TCHAR* title);
	//查找符合类名或者标题名的顶层可见窗口
	virtual long FindWindow(const TCHAR* class_name, const TCHAR* title);
	//根据指定进程以及其它条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
	virtual CString EnumWindowByProcess(const TCHAR* process_name, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//根据指定进程pid以及其它条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
	virtual CString EnumWindowByProcessId(long pid, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//根据指定进程名,枚举系统中符合条件的进程PID,并且按照进程打开顺序排序.
	virtual CString EnumProcess(const TCHAR* name);
	//根据指定条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
	virtual CString EnumWindow(LONG parent, const TCHAR* title, const TCHAR* class_name, LONG filter);
	//系统功能篇
//检测当前系统是否有开启屏幕字体平滑.
	virtual long CheckFontSmooth();
	//关闭当前系统屏幕字体平滑.同时关闭系统的ClearType功能.
	virtual long DisableFontSmooth();
	//开启当前系统屏幕字体平滑.同时开启系统的ClearType功能.
	virtual long EnableFontSmooth();
	//检测当前系统是否有开启UAC(用户账户控制).
	virtual long CheckUAC();
	//设置当前系统的UAC(用户账户控制).
	virtual long SetUAC(LONG enable);
	//延时指定的毫秒,过程中不阻塞UI操作. 一般高级语言使用.按键用不到.
	virtual long Delay(long mis);
	//延时指定范围内随机毫秒,过程中不阻塞UI操作. 一般高级语言使用.按键用不到.
	virtual long Delays(long mis_min, long  mis_max);
	//退出系统(注销 重启 关机) 
	virtual long ExitOs(long type);
	//得到系统的路径 
	virtual CString GetDir(long type);
	//获取当前CPU类型(intel或者amd).
	virtual long GetCpuType();
	//获取当前CPU的使用率. 用百分比返回.
	virtual long GetCpuUsage();
	//获取本机的指定硬盘的序列号. 要求调用进程必须有管理员权限. 否则返回空串.
	virtual CString GetDiskSerial(long index);
	//获取本机的显卡信息.
	virtual CString  GetDisplayInfo();
	//判断当前系统的DPI(文字缩放)是不是100%缩放.
	virtual long GetDPI();
	//运行指定的应用程序.返回进程PID
	virtual long RunApp(const TCHAR* path, long type = 0);
	//取硬盘特征字
	virtual long long GetHDiskCode();
	//获取CPU序列号
	virtual CString GetCpuCode();
	//获取BOIS制造日期
	virtual long long GetMainBoardInfoByCmd();
	//获取本机的机器码.(带网卡). 
	virtual CString GetMachineCode();
	//获取本机的机器码.(带网卡). 
	virtual CString GetMachineCodeNoMac();
	//从网络获取当前北京时间.
	virtual CString GetNetTime();
	//根据指定时间服务器IP,从网络获取当前北京时间.
	virtual CString GetNetTimeByIp(const TCHAR* ip);
	//得到操作系统的build版本号.  比如win10 16299,那么返回的就是16299. 其他类似
	virtual long GetOsBuildNumber();
	//得到操作系统的类型
	virtual long GetOsType();
	//获取当前系统从开机到现在所经历过的时间，单位是毫秒
	virtual long GetTime();
	//判断当前系统是否为64位
	virtual BOOL Is64Bit();
	//判断当前CPU是否支持vt,并且是否在bios中开启了vt. 仅支持intel的CPU.
	virtual long IsSurrpotVt();
	//获取屏幕的色深
	virtual long GetScreenDepth();
	//设置屏幕的色深
	virtual long SetScreenDepth(long dmBitsPerPel);
	//获取屏幕的高度
	virtual long  GetScreenHeight();
	//获取屏幕的高度
	virtual long  GetScreenWidth();
	//设置系统的分辨率 系统色深 
	virtual long SetScreen(long width, long height);
	//获得上次APi错误
	virtual long GetLastError();
	//找图
	virtual long FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, LONG* longX, LONG* longY);
	virtual long FindPic(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim, int* intX, int* intY);
	//找图返回坐标系列
	virtual CString FindPicEx(LONG x_1, LONG y_1, LONG w_1, LONG h_1, const TCHAR* pic_name, const TCHAR* delta_color, double sim);
	virtual long    FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, long* longX, long* longY);
	virtual long    FindColor(LONG x1, LONG y1, LONG w1, LONG h1, const TCHAR* color, double sim, int* intX, int* intY);
	//查找指定区域内的颜色块,颜色格式"RRGGBB-020202",
	virtual long FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, long* intX, long* intY);
	virtual long FindColorBlock(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim, long count, long width, long height, int* intX, int* intY);

	//32位图片转换24位位图 参数3是否覆盖原来的
	virtual long Bmp32To24(const TCHAR* Filepath, const TCHAR* FilepathBak, int ret);
	//取插件版本号
	virtual CString Ver();
	//抓取指定区域(x1, y1, x2, y2)的图像,保存为file(24位位图)
	virtual long Capture(long x, long y, long w, long h, const TCHAR* file);
	//比较指定坐标点(x,y)的颜色
	virtual long CmpColor(long x, long y, const TCHAR* color, double sim);
	//获取(x,y)的颜色,颜色返回格式"RRGGBB"
	virtual CString GetColor(long x, long  y);
	//获取指定区域的颜色数量, 颜色格式"RRGGBB-DRDGDB"
	virtual long GetColorNum(long x_1, long y_1, long w_1, long h_1, const TCHAR* color, double sim);
	//卡屏检测
	virtual long IsDisplayDead(long x, long y, long w, long h, long t);
	//设置操作基础磁盘
	virtual long SetPath(const TCHAR* patht);
	//文字识别
//设置字库文件
	BOOL SetDict(const TCHAR* file);
	//在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意个字符串的组合),并返回符合color_format的坐标位置
	long FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, long* intX, long* intY);
	long FindStr(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim, int* intX, int* intY);
	//在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意字符串的组合),并返回符合color_format的所有坐标位置,相似度sim同Ocr接口描述.
	virtual CString FindStrEx(long x1, long y1, long w, long h, const TCHAR* str, const TCHAR* color_format, double sim);
	//识别屏幕范围(x1,y1,x2,y2)内符合color_format的字符串,并且相似度为sim,sim取值范围(0.1-1.0),
	virtual CString Ocr(long x_1, long y_1, long w_1, long h_1, const TCHAR* color_format, double  sim);
	//鼠标操作
//把鼠标移动到目的点(x,y)
	virtual long MoveTo(long x, long y);
	//按下鼠标左键
	virtual long LeftClick();


};
#pragma pack (0)
#endif