// lwObject.h: ClwObject 的声明

#pragma once
#include "resource.h"       // 主符号



#include "lwsoft1_i.h"

#define CPUID_ECX_VMX_ABILITY 5
#define MSR_IA32_FEATURE_CONTROL 58


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// ClwObject

class ATL_NO_VTABLE ClwObject :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<ClwObject, &CLSID_lwObject>,
	public IDispatchImpl<IlwObject, &IID_IlwObject, &LIBID_lwsoft1Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	ClwObject()
	{
		//定义变量
		typedef LONG(__stdcall* fnRtlGetVersion)(POSVERSIONINFO lpVersionInformation);
		fnRtlGetVersion pRtlGetVersion;
		HMODULE hNtdll;
		LONG ntStatus;

		hNtdll = GetModuleHandle("ntdll.dll");
		if (hNtdll == NULL)goto endsl;

		pRtlGetVersion = (fnRtlGetVersion)GetProcAddress(hNtdll, "RtlGetVersion");
		if (pRtlGetVersion == NULL)goto endsl;

		m_VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		char str[32] = { 0 };
		//sprintf(str, "%p", &VersionInformation.dwBuildNumber);
		//MessageBox(0,str,0,0);
		ntStatus = pRtlGetVersion(&m_VersionInformation);

		if (ntStatus != 0)goto endsl;

		m_VerRet = TRUE;
		FreeLibrary(hNtdll);
		return ;
	endsl:
		FreeLibrary(hNtdll);
		return ;
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(ClwObject)
	COM_INTERFACE_ENTRY(IlwObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	DXBind gDxObj;
	//绑定窗口
	STDMETHODIMP BindWindow(LONG hwnd,LONG KeyMouse, LONG* nret);
	//绑定窗口
	STDMETHODIMP UnBindWindow( LONG* nret);
	//设置窗口的状态
	STDMETHODIMP SetWindowState(long hwnd, long flag, LONG* nret);
	//设置窗口的透明度
	STDMETHODIMP SetWindowTransparent(long hwnd, long trans, LONG* nret);
	//设置窗口的标题
	STDMETHODIMP SetWindowText(long hwnd, BSTR title, LONG* nret);
	//设置窗口的大小
	STDMETHODIMP SetWindowSize(long hwnd, long width, long hight, LONG* nret);
	//设置窗口客户区域的宽度和高度
	STDMETHODIMP SetClientSize(long hwnd, long width, long height, LONG* nret);
	//移动指定窗口到指定位置
	STDMETHODIMP MoveWindow(LONG hwnd, LONG x, LONG y, LONG* nret);
	//把屏幕坐标转换为窗口坐标
	STDMETHODIMP ScreenToClient(LONG hwnd, LONG* x, LONG* y, LONG* nret);
	//向指定窗口发送粘贴命令. 把剪贴板的内容发送到目标窗口.
	STDMETHODIMP SendPaste(LONG hwnd, LONG* nret);
	//获取剪贴板的内容
	STDMETHODIMP GetClipboard(BSTR* nret);
	//设置剪贴板的内容
	STDMETHODIMP SetClipboard(BSTR values, LONG* nret);
	//向指定窗口发送文本数据
	STDMETHODIMP SendString(long hwnd, BSTR str, LONG* nret);
	//向指定窗口发送文本数据2
	STDMETHODIMP SendString2(LONG hwnd, BSTR str, LONG* nret);
	//获取窗口的标题
	STDMETHODIMP GetWindowTitle(LONG hwnd, BSTR* nret);
	//获取指定窗口所在的线程ID.
	STDMETHODIMP GetWindowThreadProcessId(long  hWnd, LONG* nret);
	//获取指定窗口所在的进程ID.
	STDMETHODIMP GetWindowProcessId(long hwnd, LONG* nret);
	//获取指定窗口所在的进程的exe文件全路径.
	STDMETHODIMP GetWindowProcessPath(LONG hwnd, BSTR* nret);
	//获取窗口在屏幕上的位置
	STDMETHODIMP GetWindowRect(long hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2, LONG* nret);
	//获取窗口的类名
	STDMETHODIMP GetWindowClass(long hwnd, BSTR* nret);
	//获取指定窗口的一些属性
	STDMETHODIMP GetWindowState(LONG hwnd, LONG flag, LONG* nret);
	//获取特殊窗口
	STDMETHODIMP GetSpecialWindow(LONG flag, LONG* nret);
	//获取给定窗口相关的窗口句柄
	STDMETHODIMP GetWindow(long hwnd, long flag, LONG* nret);
	//获取鼠标指向的可见窗口句柄
	STDMETHODIMP GetMousePointWindow( LONG* nret);
	//获取给定坐标的可见窗口句柄
	STDMETHODIMP GetPointWindow(long x, long y, LONG* nret);
	//获取顶层活动窗口,可以获取到按键自带插件无法获取到的句柄
	STDMETHODIMP GetForegroundWindow( LONG* nret);
	//获取顶层活动窗口中具有输入焦点的窗口句柄 
	STDMETHODIMP GetForegroundFocus(LONG* nret);
	//设置输入焦点到窗口
	STDMETHODIMP SetForegroundFocus(long hwnd, LONG* nret);
	//获取窗口客户区域的宽度和高度
	STDMETHODIMP GetClientSize(long hwnd, LONG*  w, LONG* h, LONG* nret);
	//获取窗口客户区域在屏幕上的位置
	STDMETHODIMP GetClientRect(LONG hwnd, LONG* x1, LONG* y1, LONG* x2, LONG* y2, LONG* nret);
	//查找符合类名或者标题名的顶层可见窗口,如果指定了parent,则在parent的第一层子窗口中查找.
	STDMETHODIMP  FindWindowEx(LONG parent, BSTR class_name, BSTR title, LONG* nret);
	//查找符合类名或者标题名的顶层可见窗口
	STDMETHODIMP FindWindow(BSTR class_name, BSTR title, LONG* nret);
	//根据指定进程以及其它条件,枚举系统中符合条件的窗口
	STDMETHODIMP  EnumWindowByProcess(BSTR process_name, BSTR title, BSTR class_name, LONG filter, BSTR* nret);
	//根据指定进程pid以及其它条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
	STDMETHODIMP EnumWindowByProcessId(long pid, BSTR title, BSTR class_name, LONG filter, BSTR* nret);
	//根据指定进程名,枚举系统中符合条件的进程PID,并且按照进程打开顺序排序.
	STDMETHODIMP EnumProcess(BSTR name, BSTR* nret);
	//根据指定条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
	STDMETHODIMP EnumWindow(LONG parent, BSTR title, BSTR class_name, LONG filter, BSTR* nret);

	//设置默认操作盘
	STDMETHODIMP SetPath(BSTR path, LONG* nret);

	//图色识别功能篇
	//找色返回坐标
	STDMETHODIMP FindColor(LONG x1, LONG y1, LONG w1, LONG h1, BSTR color, double sim, LONG* longX, LONG* longY, LONG* nret);
	//获取(x,y)的颜色,颜色返回格式"RRGGBB",注意,和按键的颜色格式相反
	STDMETHODIMP  GetColor(long x, long y, BSTR* nret);
	//获取指定区域的颜色数量, 颜色格式"RRGGBB-DRDGDB",
	STDMETHODIMP GetColorNum(long x_1, long y_1, long w_1, long h_1, BSTR color, double sim, LONG* nret);
	//比较指定坐标点(x,y)的颜色
	STDMETHODIMP CmpColor(long x, long y, BSTR color, double sim, LONG* nret);
	//抓取指定区域(x1, y1, x2, y2)的图像,保存为file(24位位图)
	STDMETHODIMP  Capture(long x, long y, long w, long h, BSTR file, LONG* nret);
	//查找指定区域内的颜色块,颜色格式"RRGGBB-DRDGDB",注意,和按键的颜色格式相反
	STDMETHODIMP FindColorBlock(long x_1, long y_1, long w_1, long h_1, BSTR color, double sim, long count, long width, long height, LONG* intX, LONG* intY, LONG* nret);
	//找图返回坐标
	STDMETHODIMP FindPic(LONG x_1, LONG y_1, LONG w_1, LONG  h_1, BSTR pic_name, BSTR delta_color, double sim, LONG* longX, LONG* longY, LONG* nret);
	//找图返回坐标系列
	STDMETHODIMP FindPicEx(LONG x_1, LONG y_1, LONG w_1, LONG h_1, BSTR pic_name, BSTR delta_color, double sim, BSTR* nret);
	//32位BMP转换24位位图文件
	STDMETHODIMP Bmp32To24(BSTR Filepath, BSTR FilepathBak, LONG ret, LONG* nret);
	//返回插件版本
	STDMETHODIMP  Ver(BSTR* nret);
	//判断指定的区域，在指定的时间内(秒),图像数据是否一直不变.(卡屏). (或者绑定的窗口不存在也返回1)
	STDMETHODIMP IsDisplayDead(long x, long y, long w, long h, long t, LONG* nret);//[out,retval] LONG* nret
	
	//系统功能篇
	//检测当前系统是否有开启屏幕字体平滑.
	STDMETHODIMP  CheckFontSmooth(LONG* nret);
	//关闭当前系统屏幕字体平滑.同时关闭系统的ClearType功能.
	STDMETHODIMP DisableFontSmooth( LONG* nret);
	//开启当前系统屏幕字体平滑.同时开启系统的ClearType功能.
	STDMETHODIMP EnableFontSmooth(LONG* nret);
	//检测当前系统是否有开启UAC(用户账户控制).
	STDMETHODIMP  CheckUAC(LONG* nret);
	//设置当前系统的UAC(用户账户控制).
	STDMETHODIMP SetUAC(ULONG enable, LONG* nret);
	//延时指定的毫秒,过程中不阻塞UI操作. 一般高级语言使用.按键用不到.
	STDMETHODIMP Delay(long mis, LONG* nret);
	//延时指定范围内随机毫秒,过程中不阻塞UI操作. 一般高级语言使用.按键用不到.
	STDMETHODIMP Delays(long mis_min, long  mis_max, LONG* nret);
	//退出系统(注销 重启 关机) 
	STDMETHODIMP ExitOs(long type, LONG* nret);
	//关闭屏幕保护.
	STDMETHODIMP DisableScreenSave(LONG* nret);
	//关闭电源管理，不会进入睡眠.
	STDMETHODIMP DisablePowerSave( LONG* nret);
	//恢复系统修改，在程序退出加入
	STDMETHODIMP EnablePowerSaveh( LONG* nret);
	//设置当前的电源设置，禁止关闭显示器，禁止关闭硬盘，禁止睡眠，禁止待机. 
	STDMETHODIMP DisableCloseDisplayAndSleep(LONG* nret);
	//得到系统的路径 
	STDMETHODIMP GetDir(long type, BSTR* nret);
	//获取当前CPU类型(intel或者amd).
	STDMETHODIMP GetCpuType(LONG* nret);
	//获取当前CPU的使用率. 用百分比返回.
	STDMETHODIMP GetCpuUsage(LONG* nret);
	//获取本机的指定硬盘的序列号. 要求调用进程必须有管理员权限. 否则返回空串.
	STDMETHODIMP GetDiskSerial(long index, BSTR* nret);
	//获取本机的显卡信息.
	STDMETHODIMP GetDisplayInfo(BSTR* nret);
	//判断当前系统的DPI(文字缩放)是不是100%缩放.
	STDMETHODIMP GetDPI(LONG* nret);
	//运行指定的应用程序.返回进程PID
	STDMETHODIMP RunApp(BSTR path, long type, LONG* nret);
	//取硬盘特征字
	STDMETHODIMP GetHDiskCode( LONG* nret);
	//获取CPU序列号
	STDMETHODIMP GetCpuCode(BSTR* nret);
	//获取BOIS制造日期
	STDMETHODIMP GetMainBoardInfoByCmd(LONG* nret);
	//获取本机的机器码.(带网卡). 
	STDMETHODIMP GetMachineCode(BSTR* nret);
	//获取本机的机器码.(带网卡). 
	STDMETHODIMP GetMachineCodeNoMac(BSTR* nret);
	//从网络获取当前北京时间.
	STDMETHODIMP GetNetTime( BSTR* nret);
	//根据指定时间服务器IP,从网络获取当前北京时间.
	STDMETHODIMP GetNetTimeByIp(BSTR ip,  BSTR* nret);
	//得到操作系统的build版本号.  比如win10 16299,那么返回的就是16299. 其他类似
	STDMETHODIMP GetOsBuildNumber(LONG* nret);
	//得到操作系统的类型
	STDMETHODIMP GetOsType( LONG* nret);
	//获取当前系统从开机到现在所经历过的时间，单位是毫秒
	STDMETHODIMP GetTime(LONG* nret);
	//判断当前系统是否是64位操作系统
	STDMETHODIMP Is64Bit(LONG* nret);
	//判断当前CPU是否支持vt,并且是否在bios中开启了vt. 仅支持intel的CPU.
	STDMETHODIMP IsSurrpotVt( LONG* nret);
	//获取屏幕的色深
	STDMETHODIMP GetScreenDepth( LONG* nret);
	//设置屏幕的色深
	STDMETHODIMP SetScreenDepth(long dmBitsPerPel, LONG* nret);
	//获取屏幕的高度
	STDMETHODIMP GetScreenHeight( LONG* nret);
	//获取屏幕的高度
	STDMETHODIMP GetScreenWidth(LONG* nret);
	//设置系统的分辨率 系统色深 
	STDMETHODIMP SetScreen(long width, long height ,LONG* nret);
	//获得上次APi错误
	STDMETHODIMP GetLastError( LONG* nret);

	//文字识别功能篇
	//设置字库文件
	STDMETHODIMP SetDict(BSTR file, LONG* nret);
	//在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意个字符串的组合),并返回符合color_format的坐标位置
	STDMETHODIMP FindStr(long x1, long y1, long w, long h, BSTR str1, BSTR color_format1, double sim, LONG* intX, LONG* intY, LONG* nret);
	//在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意字符串的组合),并返回符合color_format的所有坐标位置,相似度sim同Ocr接口描述.
	STDMETHODIMP FindStrEx(long x1, long y1, long w, long h, BSTR str, BSTR color_format, double sim, BSTR* nret);
	//识别屏幕范围(x1,y1,x2,y2)内符合color_format的字符串,并且相似度为sim,sim取值范围(0.1-1.0),
	STDMETHODIMP Ocr(long x_1, long y_1, long w_1, long h_1, BSTR color_format, double  sim, BSTR* nret);

	//鼠标操作
    //把鼠标移动到目的点(x,y)
	STDMETHODIMP MoveTo(long x, long y, LONG* nret);
	//按下鼠标左键
	STDMETHODIMP LeftClick(LONG* nret);
	private:
		//检测CPU是否支持VT
		ULONG64 CheckCpuid()
		{
			int ctx[4] = { 0 };
			__cpuid(ctx, 1);
			return ctx[2] & CPUID_ECX_VMX_ABILITY;
		}
		//检测主板是否被开启VT
		BOOLEAN VmIsBiosEnableVT()
		{
			ULONG64 ctrl = 0;
			ctrl = __readmsr(MSR_IA32_FEATURE_CONTROL);
			return (ctrl & 5) == 5;
		}
		//检测VT是否被开启
		BOOLEAN VmIsStarVT()
		{

			ULONG64 ctrl = __readcr4();
			return (ctrl & 0x2000) == 0x2000;
		}
	private:
		OSVERSIONINFO m_VersionInformation = { 0 };  //系统版本号
		BOOL          m_VerRet = FALSE;              //系统版本号加载标志
};

OBJECT_ENTRY_AUTO(__uuidof(lwObject), ClwObject)
