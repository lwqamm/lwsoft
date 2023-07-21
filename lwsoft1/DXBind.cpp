#include "pch.h"


#include "LwMutexlock.h"
#include <Psapi.h>
#include <Tlhelp32.h> 
#include <Shlobj.h>
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Shell32.lib")
#pragma comment(lib,"D3d9.lib")
#include "X64asm.h"
#include "DXBind.h"
#include <string>  
#include <d3d9.h >
#include <winuser.h >
#pragma comment(lib,"User32.lib")
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")

using namespace std;
#pragma warning(disable:4996)

#include "get_internet_time.h"
//SendString互斥
TsMutex gDXSendStringMutex(LW_SENDSTRINGEVEN);

#ifdef TESTDLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	DLLEXPORT void WINAPI SetHook(HWND hw, UINT ky); //为了操作窗体，我们将主窗体的句柄传进去
	DLLEXPORT void WINAPI UnHook(HWND hw); //为了操作窗体，我们将主窗体的句柄传进去
#define  LW_KEY        1
#define  LW_MOUSE      2
#ifdef __cplusplus
}
#endif

///< 枚举窗口参数
struct EnumWindowsArg
{
	HWND hwnd = 0; // 窗口句柄
	DWORD pid = 0; // 进程ID
	char title[MAX_PATH] = { 0 };
	char class_name[MAX_PATH] = { 0 };
	LONG type = 0;
};
///< 枚举窗口参数
struct EnumWindowsArgId
{
	HWND hwnd = 0; // 窗口句柄
	DWORD pid = 0; // 进程ID
	char title[MAX_PATH] = { 0 };
	char class_name[MAX_PATH] = { 0 };
	LONG type = 0;
	PMyPid p = 0;
};

///< 枚举窗口回调函数
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	EnumWindowsArg* pArg = (EnumWindowsArg*)lParam;
	DWORD dwProcessID = 0;
	// 通过窗口句柄取得进程ID
	::GetWindowThreadProcessId(hwnd, &dwProcessID);
	char cals[MAX_PATH] = { 0 };


	if (dwProcessID == pArg->pid)
	{
		if (pArg->type & 1)
		{
			char text[MAX_PATH] = { 0 };
			GetWindowTextA(hwnd, text, MAX_PATH); // 必须含有标题文字
			toUpper_(text);

			if (!FindStrRightEXS(text,pArg->title))//模糊匹配
			{
				return TRUE;
			}
			text[0] = 0;
		}
		if (pArg->type & 2)
		{
			char text[MAX_PATH] = { 0 };
			GetClassNameA(hwnd, text, MAX_PATH); // 必须含有标题文字
			toUpper_(text);
		
			if (!FindStrRightEXS(text, pArg->class_name))//模糊匹配
			{
				return TRUE;
			}
			text[0] = 0;
		}

		if (pArg->type & 8)
		{
			if (::GetParent(hwnd) != 0)
			{
				return TRUE;
			}
		}
		if (pArg->type & 16)
		{
			if (!IsWindowVisible(hwnd))
			{
				return TRUE;
			}
		}
		pArg->hwnd = hwnd;
		// 找到了返回FALSE
		return FALSE;
	}
	// 没找到，继续找，返回TRUE
	return TRUE;
}

///< 枚举窗口回调函数
BOOL CALLBACK EnumWindowsProcId(HWND hwnd, LPARAM lParam)
{
	EnumWindowsArgId* pArg = (EnumWindowsArgId*)lParam;
	DWORD dwProcessID = 0;
	// 通过窗口句柄取得进程ID
	::GetWindowThreadProcessId(hwnd, &dwProcessID);

	if (dwProcessID == pArg->pid)
	{
		if (pArg->type & 1)
		{
			char text[MAX_PATH] = { 0 };
			GetWindowTextA(hwnd, text, MAX_PATH);
			toUpper_(text);
			if (!FindStrRightEXS( text, pArg->title))//模糊匹配
			{
				return TRUE;
			}
		}
		if (pArg->type & 2)
		{
			char text[MAX_PATH] = { 0 };
			GetClassNameA(hwnd, text, MAX_PATH); 
			toUpper_(text);
			if (!FindStrRightEXS(text, pArg->class_name))//模糊匹配
			{
				return TRUE;
			}
		}

		if (pArg->type & 8)
		{
			if (::GetParent(hwnd) != 0)
			{
				return TRUE;
			}
		}
		if (pArg->type & 16)
		{
			if (!IsWindowVisible(hwnd))
			{
				return TRUE;
			}
		}

		pArg->p->AddPid((long)hwnd);
		// 找到了返回FALSE
		//return FALSE;
	}
	// 没找到，继续找，返回TRUE
	return TRUE;
}

///< 枚举窗口回调函数
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	EnumWindowsArgId* pArg = (EnumWindowsArgId*)lParam;

	if (pArg->hwnd != 0)
	{
		DWORD pid = 0;
		::GetWindowThreadProcessId(hwnd, &pid);
		if (pArg->pid != pid)
		{
			return TRUE;
		}
	}
	if (pArg->type & 8)
	{
		if (::GetParent(hwnd) != 0)
		{
			return TRUE;
		}
	}
	if (pArg->type & 16)
	{
		if (!IsWindowVisible(hwnd))
		{
			return TRUE;
		}
	}
	if (pArg->type & 4)
	{
		if (::GetParent(hwnd) != pArg->hwnd)
		{
			return TRUE;
		}
	}

	if (pArg->type & 1)
	{
		char text[MAX_PATH] = { 0 };
		GetWindowTextA(hwnd, text, MAX_PATH); // 必须含有标题文字
		toUpper_(text);
		toUpper_(pArg->title);
		if (!FindStrRightEXS(text,pArg->title))//模糊匹配
		{
			return TRUE;
		}
	}
	if (pArg->type & 2)
	{
		char text[MAX_PATH] = { 0 };
		GetClassNameA(hwnd, text, MAX_PATH); // 必须含有标题文字
		toUpper_(text);
		toUpper_(pArg->class_name);
		if (!FindStrRightEXS(text, pArg->class_name))//模糊匹配
		{
			return TRUE;
		}
	}
	pArg->p->AddPid((long)hwnd);

	return TRUE;
}
#pragma warning(disable:4996)


DXBind::DXBind(void)
{
	if (!m_poc.ConnEct(TS_MAPVIEW_NAME, TS_MAPVIEW_NAME,sizeof(MyProc)))
	{
		
		if (!m_poc.Create(TS_MAPVIEW_NAME, TS_MAPVIEW_NAME, sizeof(MyProc)))
		{
			return;
		}
	}

	PMyProc t_p = (PMyProc)m_poc.GetBuffer();
 if (t_p->X64&& t_p->X86)
 {
	 return;
 }
	char* texePath= 0;//exe文件盘
	GetDir(4, (LPCTSTR*)&texePath);
	char exePath[MAX_PATH * 2] = { 0 };
	sprintf(exePath, "%s\\%s", texePath, "plush.exe");
	delete[] texePath;
	if (sizeof(LPVOID)==8)
	{
		m_MyProc.X64 = (UINT64)LoadLibraryA;
		m_poc.WriteIn(&m_MyProc, sizeof(MyProc));
		FreeMyResource(EXE_X86, "EXE", exePath);
	}
	else if (sizeof(LPVOID) == 4)
	{
		m_MyProc.X86 = (UINT)LoadLibraryA;
		m_poc.WriteIn(&m_MyProc, sizeof(MyProc));
		FreeMyResource(EXE_X64,"EXE", exePath);
	}

	if (!file_exist(exePath))
	{
		return ;
	}

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	BOOL ret = CreateProcess(exePath, NULL,
		NULL, NULL, FALSE, CREATE_NO_WINDOW,
		NULL, NULL, &si, &pi);
	if (!ret)
	{
		return;
	}
	int alen = 0;
	while (true)
	{
		MyProc p = { 0 };
			m_poc.Read(sizeof(MyProc),(LPVOID*)&p);
		if (sizeof(LPVOID)==8)
		{
			if (p.X86)
			{
				m_MyProc.X86 = p.X86;
				break;
			}
		}
		else
		{
			if (p.X64)
			{
				m_MyProc.X64 = p.X64;
				break;
			}
		}
		alen++;
		if (alen==1000)
		{
			break;
		}
		mysleep(1);
	}
	
	DeleteFileA(exePath);
}

DXBind::~DXBind(void)
{
}

bool DXBind::EnablePrivilege(LPCTSTR pszPrivName, bool fEnable)
{
	bool fOk = false;
	// Assume function fails    
	HANDLE hToken;
	// Try to open this process's access token   
	if (OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		TOKEN_PRIVILEGES tp = { 1 };

		//如果成功查找到特权值
		if (LookupPrivilegeValueA(NULL, pszPrivName, &tp.Privileges[0].Luid))
		{
			tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;

			AdjustTokenPrivileges(hToken, false, &tp,
				sizeof(tp), NULL, NULL);

			fOk = (GetLastError() == ERROR_SUCCESS);
		}
		CloseHandle(hToken);
	}
	return(fOk);
}

//窗口句柄_取进程pid
long DXBind::GetWindowProcessId(long h)
{
	if (h <= 110)
	{
		return 0;
	}
	DWORD dword = 0;;
	::GetWindowThreadProcessId((HWND)h, &dword);
	return dword;
}

long DXBind::GetWindowProcessPath(LONG hwnd, LPCSTR* retstring)
{
	DWORD pid = GetWindowProcessId(hwnd);
	if (!pid)
	{
		return 0;
	}
	HANDLE hProcess = NULL;
	hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, pid);

	HMODULE hMods = NULL;
	DWORD cbNeededModule = 0;
	EnumProcessModules(hProcess, &hMods, sizeof(hMods), &cbNeededModule);
	char* process_path = new char[MAX_PATH * 2];
	memset(process_path, 0, MAX_PATH * 2);
	int ret = GetModuleFileNameEx(hProcess, hMods, process_path, MAX_PATH * 2);

	*retstring = process_path;

	return ret;
}
BOOL IsWow64ProcessEx_bak(HANDLE hProcess)
{
	// 如果系统是x86的，那么进程就不可能有x64  
	bool isX86 = false;
#ifndef _WIN64  
	isX86 = GetProcAddress(GetModuleHandle(TEXT("ntdl ")), "NtWow64DebuggerCal ") == nullptr ? TRUE : FALSE;
#endif  
	if (isX86)
		return FALSE;

	// 进程架构未知，系统是x64的，可以利用IsWow64Process函数判断  
	typedef BOOL(WINAPI* ISWOW64PROCESS)(HANDLE, PBOOL);
	ISWOW64PROCESS fnIsWow64Process;
	BOOL isWow64 = TRUE;
	fnIsWow64Process = (ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
	if (fnIsWow64Process != nullptr)
		fnIsWow64Process(hProcess, &isWow64);
	return !isWow64;
}

//判断窗口所在进程是不是64位
BOOL DXBind::IsWow64ProcessEx(HWND h)
{

	DWORD pid = 0;
	GetWindowThreadProcessId(h, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == 0)
	{
		return FALSE;
	}
	BOOL bret = ::IsWow64ProcessEx_bak(hProcess);
	if (hProcess)	CloseHandle(hProcess);
	return bret;
}


long DXBind::GetWindowState(LONG hwnd, LONG flag)
{
	bool bret = false;
	HWND wnd = (HWND)hwnd;

	switch (flag)
	{
	case 0:        //判断窗口是否存在
	{
		bret = ::IsWindow(wnd);
		break;
	}
	case 1:        //判断窗口是否处于激活
	{
		if (::GetActiveWindow() == wnd)
			bret = true;
		break;
	}
	case 2:         //判断窗口是否可见
	{
		bret = ::IsWindowVisible(wnd);
		break;
	}
	case 3:        //判断窗口是否最小化
	{
		bret = ::IsIconic(wnd);
		break;
	}
	case 4:        //判断窗口是否最大化
	{
		bret = ::IsZoomed(wnd);
		break;
	}
	case 5:      //判断窗口是否置顶
	{
		if (::GetForegroundWindow() == wnd)
			bret = true;
		break;
	}
	case 6:     //判断窗口是否无响应
	{
		bret = ::IsHungAppWindow(wnd);
		break;
	}
	case 7:      //判断窗口是否可用(灰色为不可用)
	{
		bret = ::IsWindowEnabled(wnd);
		break;
	}
	case 8:       //另外的方式判断窗口是否无响应,如果6无效可以尝试这个
	{
		DWORD_PTR dwResult = 0;
		LRESULT lr = SendMessageTimeoutA(wnd, WM_NULL, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 1000, &dwResult);
		if (lr)
		{
			//not hang
			bret = false;
		}
		else
		{
			//hang
			bret = true;
		}
		break;
	}
	case 9:       //判断窗口所在进程是不是64位
	{
		bret = IsWow64ProcessEx(wnd);
		break;
	}
	break;
	}


	return bret;
}

long DXBind::GetMousePointWindow(LONG x, LONG y)
{

	bool bret = false;
	HWND	rethwnd = 0;
	POINT point;
	if (x != -1 && y != -1)
	{
		point.x = x;
		point.y = y;
	}
	else
		//::GetCursorPos(&point);
		::GetCursorPos(&point);
	rethwnd = ::WindowFromPoint(point);
	if (rethwnd == NULL)
	{
		HWND p = ::GetWindow(GetDesktopWindow(), GW_CHILD); //获取桌面窗口的子窗口
		p = ::GetWindow(p, GW_HWNDFIRST);
		while (p != NULL)
		{
			if (::IsWindowVisible(p) && ::GetWindow(p, GW_OWNER) == 0)
			{
				RECT rc;
				::GetWindowRect(p, &rc);
				if ((rc.top <= point.y) && (rc.left <= point.x) && (rc.right >= (point.x - rc.left)) && (rc.bottom >= (point.y - rc.top)))
				{
					wchar_t WindowClass[MAX_PATH] = { 0 };
					::GetClassNameW(p, WindowClass, MAX_PATH);
					//if((windowpoint.x==0||windowpoint.x<rc.left)&&wcscmp(WindowClass,L"CabinetWClass")!=0)	//IE框窗体排除在外
					if (wcscmp(WindowClass, L"CabinetWClass") != 0)	//IE框窗体排除在外
					{
						rethwnd = p;
						bret = true;
						break;
					}
				}
			}
			p = ::GetWindow(p, GW_HWNDNEXT);   //获取下一个窗口
		}
	}


	return (long)rethwnd;
}

BOOL CALLBACK MyEnumProc(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	LPWNDINFO pInfo = (LPWNDINFO)lParam;
	if (dwProcessId == pInfo->dwProcessId)
	{
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND DXBind::GetProcessMainWnd(DWORD dwProcessId)//获取自身窗口句柄
{
	WNDINFO  wi;
	wi.dwProcessId = dwProcessId;
	wi.hWnd = NULL;
	EnumWindows(MyEnumProc, (LPARAM)&wi);
	return wi.hWnd;
}

long DXBind::FindWindow(LPCSTR class_name, LPCSTR title)
{
	long rethwnd = 0;
	HWND p = NULL;
	if (p == 0)
		p = ::GetWindow(GetDesktopWindow(), GW_CHILD); //获取桌面窗口的子窗口
	else
		p = ::GetWindow((HWND)p, GW_CHILD); //获取桌面窗口的子窗口
	if (p == NULL)
		return 0;
	p = ::GetWindow(p, GW_HWNDFIRST);

	while (p != NULL)
	{
		if (::IsWindowVisible(p) && ::GetWindow(p, GW_OWNER) == 0)
		{
			if (strlen(class_name) < 1 && strlen(title) < 1)
			{
				rethwnd = (LONG)p;
				break;
			}
			else
			{
				char WindowClassName[MAX_PATH] = { 0 };
				::GetClassNameA(p, WindowClassName, MAX_PATH);
				char WindowTitle[MAX_PATH] = { 0 };
				::GetWindowTextA(p, WindowTitle, MAX_PATH);
				if (strlen(WindowClassName) > 1 && strlen(WindowTitle) > 1)
				{
					char* strfindclass = strstr(WindowClassName, class_name);   //模糊匹配
					char* strfindtitle = strstr(WindowTitle, title);   //模糊匹配
					if ((strlen(class_name) >= 1 && strfindclass) || (strlen(title) >= 1 && strfindtitle))
					{
						rethwnd = (LONG)p;
						break;
					}
				}
			}
		}
		p = ::GetWindow(p, GW_HWNDNEXT);   //获取下一个窗口
	}

	return rethwnd;
}

bool DXBind::EnumProcessbyName(LPCSTR process_name, PMyPid p)
{
	//toUpper_(ss_name);
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return FALSE;
	BOOL ret = ::Process32First(hProcessSnap, &pe32);
	if (!ret)
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	char t_ch[MAX_PATH] = { 0 };
	int aret = 0;
	while (ret)
	{
		memset(t_ch, 0, MAX_PATH);
		sprintf(t_ch, "%s", pe32.szExeFile);
		toUpper_(t_ch);
		if (FindStrRightEXS(t_ch, process_name) == 0)
		{
			p->AddPid(pe32.th32ProcessID);
			aret = 1;
		}
		ret = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return aret;
}

LONGLONG DXBind::IDE(int iDrive)
{
	char physical[256]{ 0 };
	sprintf_s(physical, 256, "\\\\.\\PhysicalDrive%d", iDrive);
	HANDLE hFile = CreateFile(physical, 3221225472, 3, 0, 3, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE) { return FALSE; }
	GETVERSIONINPARAMS OutBuffer1 = { 0 };
	DWORD BytesRet = 0;
	DeviceIoControl(hFile, 475264, 0, 0, &OutBuffer1, sizeof(GETVERSIONINPARAMS), &BytesRet, 0);
	if (OutBuffer1.bIDEDeviceMap > 0)
	{
		char OutBuffer2[544]{ 0 };
		SENDCMDINPARAMS InBuffer = { 0 };
		InBuffer.cBufferSize = 512;
		InBuffer.irDriveRegs.bSectorCountReg = 1;
		InBuffer.irDriveRegs.bSectorNumberReg = 1;
		if (iDrive & 1 != 0)
		{
			InBuffer.irDriveRegs.bDriveHeadReg = 176;
		}
		else
		{
			InBuffer.irDriveRegs.bDriveHeadReg = 160;
		}
		//
		if (iDrive != 0)
		{
			InBuffer.irDriveRegs.bCommandReg = OutBuffer1.bIDEDeviceMap / (iDrive & 16);
		}
		else
		{
			InBuffer.irDriveRegs.bCommandReg = OutBuffer1.bIDEDeviceMap;
		}

		if (InBuffer.irDriveRegs.bCommandReg == 0)
		{
			InBuffer.irDriveRegs.bCommandReg = 161;
		}
		else
		{
			InBuffer.irDriveRegs.bCommandReg = 236;
		}
		if (DeviceIoControl(hFile, 508040, &InBuffer, sizeof(SENDCMDINPARAMS), OutBuffer2, sizeof(OutBuffer2), &BytesRet, 0))
		{
			IDSECTOR IDEData;
			RtlMoveMemory(&IDEData, OutBuffer2 + 16, 276);



			CloseHandle(hFile);

			return Characteristic_character(&IDEData);
		}
		CloseHandle(hFile);
		return 0;
	}
	return 0;
}
LONGLONG DXBind::SCSI(int iDrive)
{
	char physical[256]{ 0 };
	sprintf_s(physical, 256, "\\.\Scsi%d:", iDrive);
	HANDLE	hFile = CreateFile(physical, 3221225472, 3, 0, 3, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE) { return 0; }
	SRB_IO_CONTROL InBuffer;
	InBuffer.Timeout = 2;
	InBuffer.Length = 544;
	InBuffer.ControlCode = 1770753;   //IOCTL_SCSI_MINIPORT_IDENTIFY
	InBuffer.cBufferSize = 512;
	InBuffer.bSectorCountReg = 1;
	InBuffer.bSectorNumberReg = 1;
	if (iDrive&1!=0)
	{
		InBuffer.bDriveHeadReg = 176;
	}
	else
	{
		InBuffer.bDriveHeadReg = 160;
	}
	InBuffer.bCommandReg = 236;

	char OutBuffer[572] = {0};
	DWORD ByteRet = 0;
	if (DeviceIoControl(hFile,315400,&InBuffer,sizeof(SRB_IO_CONTROL),OutBuffer,sizeof(OutBuffer), &ByteRet,0))
	{
		CloseHandle(hFile);
		IDSECTOR IDEData;
		RtlMoveMemory(&IDEData, OutBuffer + 44, 276);

		return Characteristic_character(&IDEData);

	}
	CloseHandle(hFile);
	return 0;
}
LONGLONG DXBind::Characteristic_character(PIDSECTOR Data)
{
	char Dword[40] = { 0 };
	char dwaa[3] = { 0,0,0 };
	int Total = 0;
	int toppp = 0;
	for (size_t i = 0; i < 40; i++)
	{
		if ((i+1) % 2 == 0)
		{
			dwaa[0] = Data->sModelNumber[i];
			memcpy(Dword+1, dwaa,3);
			toppp = 0;
			memcpy(&toppp, Dword, 4);
			Total = Total + toppp;
		}
		else
		{
			memset(Dword, 0, 40);
			Dword[0] = Data->sModelNumber[i];
		}
	}

	for (size_t i = 0; i < 8; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			dwaa[0] = Data->sFirmwareRev[i];
			memcpy(Dword + 1, dwaa, 3);
			toppp = 0;
			memcpy(&toppp, Dword, 4);
			Total = Total + toppp;
		}
		else
		{
			memset(Dword, 0, 40);
			Dword[0] = Data->sFirmwareRev[i];
		}

	}

	for (size_t i = 0; i < 20; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			dwaa[0] = Data->sSerialNumber[i];
			memcpy(Dword + 1, dwaa, 3);
			toppp = 0;
			memcpy(&toppp, Dword, 4);
			Total = Total + toppp;
		}
		else
		{
			memset(Dword, 0, 40);
			Dword[0] = Data->sSerialNumber[i];
		}

	}

	Total += ((Data->wBufferSize + Data->wSectorsPerTrack + Data->wNumHeads + Data->wNumCyls) * 65536);


	return Total;
}

char* DXBind::GetMac()
{
	ULONG ulAdapterInfoSize = sizeof(IP_ADAPTER_INFO);
	IP_ADAPTER_INFO* pAdapterInfoBkp = NULL, * pAdapterInfo = (IP_ADAPTER_INFO*)new char[ulAdapterInfoSize];
	if (GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == ERROR_BUFFER_OVERFLOW) // 缓冲区不够大
	{
		delete pAdapterInfo;
		pAdapterInfo = (IP_ADAPTER_INFO*)new char[ulAdapterInfoSize];
		pAdapterInfoBkp = pAdapterInfo;
	}
	char* str = 0, * str1 = 0;
	if (GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == NO_ERROR)
	{
		do { // 遍历所有适配器
			if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)    // 判断是否为以太网, 以太网适配器是 6  无线局域网适配器是 71
			{
				// pAdapterInfo->Description 是适配器描述
				// pAdapterInfo->AdapterName 是适配器名称


				for (UINT i = 0; i < pAdapterInfo->AddressLength; i++)
				{
					char szTmp[8];
					sprintf(szTmp, "%02X%c", pAdapterInfo->Address[i], (i == pAdapterInfo->AddressLength - 1) ? '\0' : '-');

					if (str == 0)
					{
						int len = strlen(szTmp) + 1;
						str = new char[len];
						memset(str, 0, len);
						sprintf(str, "%s", szTmp);
					}
					else
					{
						int len = strlen(szTmp) + strlen(str) + 1;
						str1 = new char[len];
						memset(str1, 0, len);
						sprintf(str1, "%s%s", str, szTmp);
						delete[] str;
						str = str1;
						str1 = 0;
					}
				}
				return str;
			}
			pAdapterInfo = pAdapterInfo->Next;
		} while (pAdapterInfo);
	}

	if (pAdapterInfoBkp)
		delete pAdapterInfoBkp;

	return str;
}
UCHAR DXBind::CharToInt_bak(UCHAR p)
{

	if (p>='A'&&p<='Z')
	{
		p += 32;
	}

	if (p >= 'g' && p <= 'n')
	{
		p = 'e';
	}
	else if (p >= 'o' && p <= 't')
	{
		p = 'f';
	}
	else if (p >= 'u' && p <= 'w')
	{
		p = '7';
	}
	else if (p >= 'x' && p <= 'z')
	{
		p = '2';
	}

	if (p=='-')
	{
		p = '6';
	}

	int tpy = 0;
	if (p>='0'&&p<='9')
	{
		tpy = p - 48;
	}
	else if (p >= 'a' && p <= 'f')
	{
		tpy = p - 87;
	}

	switch (tpy)
	{
	case 0:
	{
		return  'f';
	}
	case 1:
	{
		return  'e';
	}
	case 2:
	{
		return  'd';
	}
	case 3:
	{
		return  '9';
	}
	case 4:
	{
		return  '7';
	}
	case 5:
	{
		return  'a';
	}
	case 6:
	{
		return  'b';
	}
	case 7:
	{
		return  'c';
	}
	case 8:
	{
		return  '1';
	}
	case 9:
	{
		return  '3';
	}
	case 0xA:
	{
		return  '2';
	}
	case 0xB:
	{
		return  '4';
	}
	case 0xC:
	{
		return  '5';
	}
	case 0xD:
	{
		return  '6';
	}
	case 0xE:
	{
		return  '0';
	}
	case 0xF:
	{
		return  '8';
	}

		break;
	}
	return '0';
}

UCHAR DXBind::CharToInt_bakOnMac(UCHAR p)
{
	if (p >= 'A' && p <= 'Z')
	{
		p += 32;
	}

	if (p >= 'g' && p <= 'n')
	{
		p = '9';
	}
	else if (p >= 'o' && p <= 't')
	{
		p = '9';
	}
	else if (p >= 'u' && p <= 'w')
	{
		p = 'f';
	}
	else if (p >= 'x' && p <= 'z')
	{
		p = 'e';
	}

	if (p == '-')
	{
		p = 'd';
	}

	int tpy = 0;
	if (p >= '0' && p <= '9')
	{
		tpy = p - 48;
	}
	else if (p >= 'a' && p <= 'f')
	{
		tpy = p - 87;
	}

	switch (tpy)
	{
	case 0:
	{
		return  'd';
	}
	case 1:
	{
		return  'f';
	}
	case 2:
	{
		return  'e';
	}
	case 3:
	{
		return  'a';
	}
	case 4:
	{
		return  'b';
	}
	case 5:
	{
		return  'c';
	}
	case 6:
	{
		return  '9';
	}
	case 7:
	{
		return  '4';
	}
	case 8:
	{
		return  '3';
	}
	case 9:
	{
		return  '1';
	}
	case 0xA:
	{
		return  '5';
	}
	case 0xB:
	{
		return  '2';
	}
	case 0xC:
	{
		return  '7';
	}
	case 0xD:
	{
		return  '8';
	}
	case 0xE:
	{
		return  '6';
	}
	case 0xF:
	{
		return  '0';
	}

	break;
	}
	return '0';
}

void DXBind::SetCpuidStr(LPCVOID pp, int dx, PMycpu p, int* ret)
{
	//    const UCHAR  g_incpu[58] = {
	//    0x48,0x33,0xC0,
	//    0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    +5
	//    0x0F,0xA2,
	//    0x49,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    +17
	//    0x49,0x89,0x00,
	//    0x49,0x89,0x58,0x04,
	//    0x49,0x89,0x48,0x08,
	//    0x49,0x89,0x50,0x12,
	//    0x48,0xBF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	+42
	//    0x48,0xC7,0x07,0x01,0x00,0x00,0x00,
	//    0xC3
	//    };
	memcpy((void*)((ULONG_PTR)pp+5),&dx,sizeof(int));   //+6

	ULONG_PTR l_p = (ULONG_PTR)p;
	memcpy((void*)((ULONG_PTR)pp + 17), &l_p, sizeof(ULONG_PTR));   //+17
	l_p = (ULONG_PTR)ret;
	memcpy((void*)((ULONG_PTR)pp + 42), &l_p, sizeof(ULONG_PTR));   //+30
	return;
}
int DXBind::GetStrPos(LPVOID pl,int pos)
{
	if ((ULONG64)pl<=0x10000)
	{
		return 0;
	}
	char* p = (char*)pl;
	int len = 0;

	int ipos = 0;
	for (size_t i = 0; i < pos; i++)
	{
		if (p[len]<0)
		{
			len += 2;
			ipos += 2;
		}

		len += 1;
		ipos += 1;

	}


	return ipos;
}
CHAR* DXBind::GetModuleFile()
{
	char* outbf = new char[MAX_PATH];
	memset(outbf, 0, MAX_PATH);

	//char tchpan[MAX_PATH] = { 0 };
	HMODULE DLL = 0;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, LW_VERSION, &DLL);
	GetModuleFileName(DLL, outbf, MAX_PATH);
	if (strlen(outbf)==0)
	{
		delete[] outbf;
		return 0;
	}

	return outbf;
}

long DXBind::MoveTo(long x, long y)
{
	return SndMeage(LW_MOVETO,x,y);
}

long DXBind::LeftClick()
{
	return SndMeage(LW_LEFTCLICK, 0, 0);
}
//根据指定进程以及其它条件,枚举系统中符合条件的窗口,可以枚举到按键自带的无法枚举到的窗口
long DXBind::lwEnumWindow(LPCSTR process_name, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* otbuff)
{
	if (strlen(process_name) <= 4)
	{
		return 0;
	}
	char ss_name[MAX_PATH] = { 0 };
	sprintf(ss_name, "%s", process_name);
	toUpper_(ss_name);
	MyPid pidarr;
	if (!EnumProcessbyName(ss_name, &pidarr))
	{
		return 0;
	}
	if (pidarr.GetPidLen() == 0)
	{
		return 0;
	}
	int len = pidarr.GetPidLen();
	if (filter & 4)//只取第一个窗口
	{
		EnumWindowsArg ewind = { 0 };
		if (filter & 1)
		{
			if (strlen(title) == 0)
			{
				return 0;
			}
			sprintf(ewind.title, "%s", title);
			toUpper_(ewind.title);
		}
		if (filter & 2)
		{
			if (strlen(class_name) == 0)
			{
				return 0;
			}
			sprintf(ewind.class_name, "%s", class_name);
			toUpper_(ewind.class_name);
		}
		ewind.pid = pidarr.GetPid(0);
		ewind.type = filter;
		//EnumWindowsProc
		EnumWindows(EnumWindowsProc, (LPARAM)&ewind);
		char* chht = new char[10];
		memset(chht, 0, 10);
		if (ewind.hwnd == 0)
		{
			delete[] chht;
			return 0;
		}
		else
		{
			sprintf(chht, "%d", ewind.hwnd);
		}
		*otbuff = chht;
		return (long)ewind.hwnd;
	}

	if (filter & 32)
	{

		if (!pidarr.BubbleSort())
		{
			return 0;
		}

	}
	EnumWindowsArg ewind = { 0 };
	MyPid hwndArr;
	if (filter & 1)
	{
		if (strlen(title) == 0)
		{
			return 0;
		}
		sprintf(ewind.title, "%s", title);
		toUpper_(ewind.title);
	}



	if (filter & 2)
	{
		if (strlen(class_name) == 0)
		{
			return 0;
		}
		sprintf(ewind.class_name, "%s", class_name);
		toUpper_(ewind.class_name);
	}
	ewind.type = filter;
	for (size_t i = 0; i < len; i++)
	{

		ewind.pid = pidarr.GetPid(i);

		//EnumWindowsProc
		EnumWindows(EnumWindowsProc, (LPARAM)&ewind);
		if (ewind.hwnd)
		{
			hwndArr.AddPid((long)ewind.hwnd);
		}
	}
	if (!hwndArr.GetPidLen())
	{
		return 0;
	}
	char* str = 0, * str1 = 0;
	for (size_t i = 0; i < hwndArr.GetPidLen(); i++)
	{
		char ch_[10] = { 0 };
		sprintf(ch_, "%d", hwndArr.GetPid(i));
		if (i == 0)
		{
			int tt_len = strlen(ch_) + 1;
			str = new char[tt_len];
			memset(str, 0, tt_len);
			sprintf(str, "%s", ch_);
		}
		else
		{
			int tt_len = strlen(ch_) + strlen(str) + 2;
			str1 = new char[tt_len];
			memset(str1, 0, tt_len);
			sprintf(str1, "%s,%s", str, ch_);
			delete[] str;
			str = str1;
			str1 = 0;
		}


	}
	*otbuff = str;
	if (str)
	{
		return 1;
	}
	return 0;
}

long DXBind::lwEnumWindowId(long pid, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* otbuff)
{
	EnumWindowsArgId  ewind = { 0 };
	ewind.pid = pid;
	ewind.type = filter;
	MyPid hwndArr;
	ewind.p = &hwndArr;
	if (filter & 1)
	{
		if (strlen(title) < 1)
		{
			return 0;
		}
		sprintf(ewind.title, "%s", title);
		toUpper_(ewind.title);
	}
	if (filter & 2)
	{
		if (strlen(title) < 1)
		{
			return 0;
		}
		sprintf(ewind.class_name, "%s", class_name);
		toUpper_(ewind.class_name);
	}
	EnumWindows(EnumWindowsProcId, (LPARAM)&ewind);
	if (hwndArr.GetPidLen() == 0)
	{
		return 0;
	}

	char* str = 0, * str1 = 0;
	for (size_t i = 0; i < hwndArr.GetPidLen(); i++)
	{
		char ch_[10] = { 0 };
		sprintf(ch_, "%d", hwndArr.GetPid(i));
		if (i == 0)
		{
			int tt_len = strlen(ch_) + 1;
			str = new char[tt_len];
			memset(str, 0, tt_len);
			sprintf(str, "%s", ch_);
		}
		else
		{
			int tt_len = strlen(ch_) + strlen(str) + 2;
			str1 = new char[tt_len];
			memset(str1, 0, tt_len);
			sprintf(str1, "%s,%s", str, ch_);
			delete[] str;
			str = str1;
			str1 = 0;
		}


	}
	*otbuff = str;
	if (str)
	{
		return 1;
	}
	return 0;

}

long DXBind::EnumProcess(LPCSTR name, LPCSTR* otbuff)
{
	if (strlen(name) <= 4)
	{
		return 0;
	}
	char ss_name[MAX_PATH] = { 0 };
	sprintf(ss_name, "%s", name);
	toUpper_(ss_name);
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return FALSE;
	BOOL ret = ::Process32First(hProcessSnap, &pe32);
	if (!ret)
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	char t_ch[MAX_PATH] = { 0 };
	int aret = 0;
	MyPid pidarr;
	while (ret)
	{
		memset(t_ch, 0, MAX_PATH);
		sprintf(t_ch, "%s", pe32.szExeFile);
		toUpper_(t_ch);
		if (strcmp(t_ch, ss_name) == 0)
		{
			pidarr.AddPid(pe32.th32ProcessID);
			aret = 1;
		}
		ret = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	if (!aret || pidarr.GetPidLen() == 0)
	{
		return 0;
	}
	char* str = 0, * str1 = 0;
	for (size_t i = 0; i < pidarr.GetPidLen(); i++)
	{
		char ch_[10] = { 0 };
		sprintf(ch_, "%d", pidarr.GetPid(i));
		if (i == 0)
		{
			int tt_len = strlen(ch_) + 1;
			str = new char[tt_len];
			memset(str, 0, tt_len);
			sprintf(str, "%s", ch_);
		}
		else
		{
			int tt_len = strlen(ch_) + strlen(str) + 2;
			str1 = new char[tt_len];
			memset(str1, 0, tt_len);
			sprintf(str1, "%s,%s", str, ch_);
			delete[] str;
			str = str1;
			str1 = 0;
		}


	}
	*otbuff = str;
	if (str)
	{
		return 1;
	}
	return 0;

}

long DXBind::EnumWindow(LONG parent, LPCSTR title, LPCSTR class_name, LONG filter, LPCSTR* retstr)
{

	//匹配出的窗口按照窗口打开顺序依次排列

	MyPid hunarr;
	EnumWindowsArgId ewnd;
	if (parent != 0)
	{
		ewnd.pid = GetWindowProcessId(parent);
		if (!ewnd.pid)
		{
			return 0;
		}
	}

	ewnd.hwnd = (HWND)parent;
	ewnd.p = &hunarr;
	if (filter & 1)
	{
		if (strlen(title) < 1)
		{
			return 0;
		}
		sprintf(ewnd.title, "%s", title);
		toUpper_(ewnd.title);
	}
	if (filter & 2)
	{
		if (strlen(class_name) < 1)
		{
			return 0;
		}
		sprintf(ewnd.class_name, "%s", class_name);
		toUpper_(ewnd.class_name);
	}
	ewnd.type = filter;
	::EnumWindows(EnumWindowProc, (LPARAM)&ewnd);
	if (hunarr.GetPidLen() == 0)
	{
		return 0;
	}

	char* str = 0, * str1 = 0;
	for (size_t i = 0; i < hunarr.GetPidLen(); i++)
	{
		char ch_[10] = { 0 };
		sprintf(ch_, "%d", hunarr.GetPid(i));
		if (i == 0)
		{
			int tt_len = strlen(ch_) + 1;
			str = new char[tt_len];
			memset(str, 0, tt_len);
			sprintf(str, "%s", ch_);
		}
		else
		{
			int tt_len = strlen(ch_) + strlen(str) + 2;
			str1 = new char[tt_len];
			memset(str1, 0, tt_len);
			sprintf(str1, "%s,%s", str, ch_);
			delete[] str;
			str = str1;
			str1 = 0;
		}


	}
	*retstr = str;

	return (long)str;
}

long DXBind::mysleep(DWORD delaytime)
{
	if (!delaytime)
	{
		return 0;
	}
	//LARGE_INTEGER  large_interger;
	//double dff;
	//__int64  c1, c2;
	//QueryPerformanceFrequency(&large_interger);
	//dff = large_interger.QuadPart;
	//QueryPerformanceCounter(&large_interger);
	//c1 = large_interger.QuadPart;
	//DWORD result;
	//MSG msg;
	//while (1)
	//{
	//	QueryPerformanceCounter(&large_interger);
	//	c2 = large_interger.QuadPart;
	//	if (((c2 - c1) * 1000 / dff >= delaytime))
	//	{
	//		break;
	//	}

	//	mysleep_bak();

	//}
	//return 1;
	
		HANDLE hTimer = CreateWaitableTimerA(0,FALSE,0);
		LARGE_INTEGER T_sj = {0};
		T_sj.QuadPart = -10000* (LONGLONG)delaytime;//* delaytime
		SetWaitableTimer(hTimer, &T_sj, 0, 0, 0, FALSE);
		while (MsgWaitForMultipleObjects(1, &hTimer,FALSE,-1,255)!=0)
		{
			mysleep_bak();
		}
		CloseHandle(hTimer);
		return 1;
}

long DXBind::GetDir(long type,LPCSTR* oubuf)
{
	if (type<0||type>4)
	{
		return 0;
	}
	
	switch (type)
	{
	case 0:									// 获取当前路径
	{
		DWORD dwSize = GetCurrentDirectoryA(0,NULL);
		if (!dwSize)
		{
			return 0;
		}
		char* buf = new char[dwSize + 1];
		dwSize =GetCurrentDirectoryA(dwSize, buf);
		if (!dwSize)
		{
			delete[] buf;
			return 0;
		}
		*oubuf = buf;
		return 1;
	}
	case 1:									//获取系统路径(system32路径)
	{
		char* buf = new char[MAX_PATH];
		memset(buf, 0, MAX_PATH );
		HRESULT hr = SHGetFolderPath(NULL, CSIDL_SYSTEM,NULL, MAX_PATH, buf);
		if (SUCCEEDED(hr))
		{
			*oubuf = buf;
			return 1;
		}
		delete[] buf;
		return 0;
	}									 //
	case 2:								 //获取windows路径(windows所在路径)
	{
		char* buf = new char[MAX_PATH];
		memset(buf, 0, MAX_PATH);
		HRESULT hr = SHGetFolderPath(NULL, CSIDL_WINDOWS, NULL, CSIDL_WINDOWS, buf);
		if (SUCCEEDED(hr))
		{
			*oubuf = buf;
			return 1;
		}
		delete[] buf;
		return 0;;
	}
	case 3:							//获取临时目录路径(temp)
	{
		char* buf = new char[MAX_PATH];
		memset(buf, 0, MAX_PATH);
	
		DWORD dwSize= GetTempPathA(MAX_PATH, buf);
		if (dwSize)
		{
			*oubuf = buf;
			return 1;
		}
		delete[] buf;
		return 0;;
	}
	case 4:                            //获取当前进程(exe)所在的路径
	{
		char* buf = new char[MAX_PATH * 2];
		memset(buf, 0, MAX_PATH * 2);

		DWORD dwSize = GetModuleFileName(NULL, buf,MAX_PATH * 2);
		if (dwSize)
		{
			dwSize = ReverseFind((LPVOID)buf,"\\");
			if (dwSize==-1)
			{
				delete[] buf;
				return 0;
			}
			memset(buf+ dwSize, 0, MAX_PATH * 2- dwSize);
			*oubuf = buf;
			return 1;
		}
		return 0;
		break;
	}
	default:
		break;
	}



	return 0;
}

long DXBind::GetCpuType()
{
	const DWORD id = 0x80000002;
	char cpuType[49];
	memset(cpuType, 0, sizeof(cpuType));
	Mycpu cpu;
	for (DWORD t = 0; t < 3; t++) {

#if _WIN64
		int ret = 0;

		LPVOID t_p = VirtualAlloc(NULL, sizeof(g_incpu), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!t_p)
		{
			return 0;
		}
		memcpy(t_p, g_incpu, sizeof(g_incpu));
		SetCpuidStr(t_p, 3, &cpu, &ret);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t_p, 0, 0, 0);
		while (1)
		{
			if (ret)
			{
				break;
			}
			mysleep(10);//延时
		}
#else

		initCpu(id + t, &cpu);
#endif




		memcpy(cpuType + 16 * t + 0, &cpu.eax, 4);
		memcpy(cpuType + 16 * t + 4, &cpu.ebx, 4);
		memcpy(cpuType + 16 * t + 8, &cpu.ecx, 4);
		memcpy(cpuType + 16 * t + 12, &cpu.edx, 4);
	}
	if (FindStrRightEXS(cpuType,"Intel"))
	{
		return 1;
	}
	if (FindStrRightEXS(cpuType, "AMD"))
	{
		return 2;
	}
	return 0;
}

 __int64 Filetime2Int64(const FILETIME& ftime)
{
	LARGE_INTEGER li;
	li.LowPart = ftime.dwLowDateTime;
	li.HighPart = ftime.dwHighDateTime;
	return li.QuadPart;
}

  __int64 CompareFileTime2(const FILETIME& preTime, const FILETIME& nowTime)
{
	return Filetime2Int64(nowTime) - Filetime2Int64(preTime);
}


long DXBind::GetCpuUsage()
{
	FILETIME preIdleTime;
	FILETIME preKernelTime;
	FILETIME preUserTime;
	GetSystemTimes(&preIdleTime, &preKernelTime, &preUserTime);

	mysleep(1000);

	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);

	__int64 idle = CompareFileTime2(preIdleTime, idleTime);
	__int64 kernel = CompareFileTime2(preKernelTime, kernelTime);
	__int64 user = CompareFileTime2(preUserTime, userTime);

	if (kernel + user == 0)
		return 0;

	return  (kernel + user - idle) * 100 / (kernel + user);
}

long DXBind::SetWindowState(long hwnd, long flag)
{
	
	bool bret = false;
	HWND hWnd = (HWND)hwnd;
	if (IsWindow(hWnd) == false)
		return bret;

	switch (flag)
	{
	case 0://关闭指定窗口
	{
		bret = ::SendMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	}
	case 1://激活指定窗口
	{
		bret=::ShowWindow(hWnd, SW_SHOW);
		SwitchToThisWindow((HWND)hWnd, false);
		bret = ::SetForegroundWindow(hWnd);
		
		break;
	}
	case 2://最小化指定窗口,但不激活
	{
		bret = ::ShowWindow(hWnd, SW_SHOWMINNOACTIVE);
		break;
	}
	case 3://最小化指定窗口,并释放内存,但同时也会激活窗口
	{
		bret = ::ShowWindow(hWnd, SW_SHOWMINIMIZED);
		break;
	}
	case 4://最大化指定窗口,同时激活窗口.
	{
		bret = ::ShowWindow(hWnd, SW_SHOWMAXIMIZED);
		break;
	}
	case 5://恢复指定窗口 ,但不激活
	{
		bret = ::ShowWindow(hWnd, SW_SHOWNOACTIVATE);
		break;
	}
	case 6://隐藏指定窗口
	{
		bret = ::ShowWindow(hWnd, SW_HIDE);
		break;
	}
	case 7://显示指定窗口
	{
		::ShowWindow(hWnd, SW_SHOW);
		SwitchToThisWindow((HWND)hWnd, false);
		bret = ::SetForegroundWindow(hWnd);
		
		break;
	}
	case 8://置顶指定窗口
	{
		DWORD pid = GetWindowProcessId((long)hWnd);
		DWORD	tid = GetWindowThreadProcessId(hWnd, &pid);
		AttachThreadInput(tid, GetCurrentThreadId(), TRUE);
		SetActiveWindow(hWnd);
		AttachThreadInput(tid, GetCurrentThreadId(), FALSE);
		SetForegroundWindow(hWnd);
		ShowWindow(hWnd, SW_RESTORE);
		bret = ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//窗口置顶
		break;
	}
	case 9://取消置顶指定窗口
	{
		bret = ::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); //取消置顶
		break;
	}
	case 10://禁止指定窗口
	{
		bret = ::EnableWindow(hWnd, false);
		break;
	}
	case 11://取消禁止指定窗口
	{
		bret = ::EnableWindow(hWnd, true);
		break;
	}
	case 12://恢复并激活指定窗口
	{
		bret = ::ShowWindow(hWnd, SW_RESTORE);
		break;
	}
	case 13://强制结束窗口所在进程.
	{
		DWORD pid = 0;
		::GetWindowThreadProcessId(hWnd, &pid);

		EnablePrivilege("SeDebugPrivilege", true);
		HANDLE hprocess = NULL;
		//if (my_OpenProcess)
		//	hprocess = my_OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		//else
		hprocess = ::OpenProcess(PROCESS_ALL_ACCESS, false, pid);

		bret = ::TerminateProcess(hprocess, 0);
		break;
	}
	case 14://闪烁指定的窗口
	{
		FLASHWINFO fInfo;
		fInfo.cbSize = sizeof(FLASHWINFO);
		fInfo.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;//这里是闪动窗标题和任务栏按钮,直到用户激活窗体
		fInfo.dwTimeout = 0;
		fInfo.hwnd = hWnd;
		fInfo.uCount = 0xffffff;
		bret = FlashWindowEx(&fInfo);
		break;
	}
	case 15://使指定的窗口获取输入焦点
	{
		::ShowWindow(hWnd, SW_SHOW);
		bret = ::SetFocus(hWnd);
		break;
	}
	default:
		break;
	}

	return bret;
}

//设置窗口的透明度
bool DXBind::SetWindowTransparent(long hwnd, long trans)
{
	bool bret = false;

	COLORREF crKey = NULL;
	DWORD dwFlags = 0;
	BYTE bAlpha = 0;
	if (trans < 0)
		trans = 0;
	if (trans > 255)
		trans = 255;

	typedef bool(__stdcall* mySetLayeredWindowAttributes)(
		HWND hwnd,
		COLORREF pcrKey,
		BYTE pbAlpha,
		DWORD pdwFlags);
	mySetLayeredWindowAttributes obj_SetLayeredWindowAttributes = NULL;
	HINSTANCE hlibrary;
	hlibrary = LoadLibrary(_T("user32.dll"));
	obj_SetLayeredWindowAttributes = (mySetLayeredWindowAttributes)GetProcAddress(hlibrary, "SetLayeredWindowAttributes");
	if (!obj_SetLayeredWindowAttributes)
	{
		return false;
	}
	SetWindowLong((HWND)hwnd, GWL_EXSTYLE, 0x80001);
	bret = obj_SetLayeredWindowAttributes((HWND)hwnd, crKey, trans, 2);

	return bret;
}

long DXBind::SetWindowSize(long hwnd, long width, long hight, int type)
{
	bool bret = false;
	if (type == 0)//SetClientSize
	{
		RECT  rectProgram, rectClient;
		HWND hWnd = (HWND)hwnd;
		::GetWindowRect(hWnd, &rectProgram);   //获得程序窗口位于屏幕坐标
		::GetClientRect(hWnd, &rectClient);      //获得客户区坐标
		//非客户区宽,高
		int nWidth = rectProgram.right - rectProgram.left - (rectClient.right - rectClient.left);
		int nHeiht = rectProgram.bottom - rectProgram.top - (rectClient.bottom - rectClient.top);
		nWidth += width;
		nHeiht += hight;
		rectProgram.right = nWidth;
		rectProgram.bottom = nHeiht;
		int showToScreenx = GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2;    //居中处理
		int showToScreeny = GetSystemMetrics(SM_CYSCREEN) / 2 - nHeiht / 2;
		bret = ::MoveWindow(hWnd, showToScreenx, showToScreeny, rectProgram.right, rectProgram.bottom, false);
	}
	else	//SetWindowSize
	{
		RECT rectClient;
		HWND hWnd = (HWND)hwnd;
		::GetWindowRect(hWnd, &rectClient);   //获得程序窗口位于屏幕坐标
		bret = ::MoveWindow(hWnd, rectClient.left, rectClient.top, width, hight, false);
	}
	return bret;
}

long DXBind::SendPaste(LONG hwnd)
{
	bool bret = true;
	HANDLE hClip;
	char* chBuffer = NULL;
	if (OpenClipboard(NULL))
	{
		//从剪贴板中取出一个内存的句柄
		hClip = GetClipboardData(CF_TEXT);
		//定义字符型指针变量用来保存内存块中的数据
		//对内存块进行加锁，将内存句柄值转化为一个指针,并将内存块的引用计数器加一，内存中的数据也返回到指针型变量中
		chBuffer = (char*)GlobalLock(hClip);
		//将数据保存到字符型变量中
		//将内存块的引用计数器减一
		GlobalUnlock(hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		CloseClipboard();
	}
	//anscii 转 unicode
	DWORD num = MultiByteToWideChar(CP_ACP, 0, chBuffer, -1, NULL, 0);
	wchar_t* wword = new wchar_t[num + 1];//动态的申请空间存字
	memset(wword, 0, (num + 1) * sizeof(wchar_t));   //初始化动作
	int len = MultiByteToWideChar(CP_ACP, 0, chBuffer, -1, wword, num);
	chBuffer[len] = '\0';
	len = wcslen(wword);
	//MessageBoxA(NULL,tts,tts,NULL);
	for (int i = 0; i < len; i++)
	{
		::SendMessage((HWND)hwnd, WM_CHAR, (WPARAM)wword[i], (LPARAM)1);
		Sleep(10);
	}
	delete[] wword;

	return bret;
}

long DXBind::SetClipboard(LPCSTR values)
{
	if ((DWORD64)values <= 0x10000)
	{
		return 0;
	}
	bool bret = false;

	if (OpenClipboard(NULL))
	{
		//将剪贴板内容清空
		EmptyClipboard();
		//字节长度
		int leng = strlen(values) + 1;
		//在堆上分配可移动的内存块，程序返回一个内存句柄
		HANDLE hClip = GlobalAlloc(GHND | GMEM_SHARE, leng);
		//定义指向字符型的指针变量
		char* buff;
		//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加一
		buff = (char*)GlobalLock(hClip);
		//将用户输入的数据拷贝到指针变量中，实际上就是拷贝到分配的内存块中
		memcpy(buff, values, leng);
		buff[leng - 1] = 0;
		//数据写入完毕，进行解锁操作，并将引用计数器数字减一
		GlobalUnlock(hClip);
		//将存放有数据的内存块放入剪贴板的资源管理中
		HANDLE help = SetClipboardData(CF_TEXT, hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		CloseClipboard();
		//MessageBox(0,L"已将数据存入剪贴板",L"剪切扳",0);
		if (help != NULL)
		{
			bret = true;
		}
		else
		{
			bret = false;
		}
	}

	return bret;
}

long DXBind::GetClipboard(LPCSTR* retstr)
{
	bool bret = false;
	HANDLE hClip;
	char* chBuffer = NULL;
	if (OpenClipboard(NULL))
	{
		//从剪贴板中取出一个内存的句柄
		hClip = GetClipboardData(CF_TEXT);
		//定义字符型指针变量用来保存内存块中的数据

		//对内存块进行加锁，将内存句柄值转化为一个指针,并将内存块的引用计数器加一，内存中的数据也返回到指针型变量中
		chBuffer = (char*)GlobalLock(hClip);

		//将数据保存到字符型变量中
		//将内存块的引用计数器减一
		GlobalUnlock(hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		CloseClipboard();
	}

	DWORD num = strlen(chBuffer);
	char* wword = new char[num + 1];//动态的申请空间存字
	memset(wword, 0, num + 1);   //初始化动作
	bret = sprintf(wword, chBuffer, num);
	*retstr = wword;

	return bret;
}

long DXBind::SendString(long hwnd, LPCSTR str)
{
	LwMutexlock ts_mutexlock(&gDXSendStringMutex);
	int len = strlen(str);
	int nret = 0;
	PUCHAR p = (PUCHAR)str;
	for (int i = 0; i < len; i++)
	{
		nret = ::SendMessageA((HWND)hwnd, WM_CHAR, (WPARAM)p[i], 0);
		Sleep(1);
	}

	return nret;
}

long  DXBind::Bind(LONG hwnd, ULONG KeyMouse)
{
	if (hwnd == 0 || ::IsWindow((HWND)hwnd) == false||m_hwnd)
	{
		//MessageBox(NULL, "无效窗口句柄", "LW", NULL);
		return false;
	}
	
	//记录被绑定的窗口的句柄
	m_hwnd = (HWND)hwnd;
	return 1;
	//MessageBox(0,"绑定成功！","lw",MB_OK);
	if (m_Pid==0)
	{
		m_Pid = GetWindowProcessId(hwnd);
		if (m_Pid==0)
		{
			MessageBox(NULL, "无效窗口句柄", "LW", NULL);
			return false;
		}
	}

	//if (KeyMouse<=1)
	//{
	//	return true;
	//}
	//HMODULE DLL = GetModuleHandle("Hook.dll");
	//
	//
	//if (!DLL)
	//{
	//	DLL = LoadLibraryA("Hook.dll");
	//	if (!DLL)
	//	{
	//		return 0;
	//	}
	//}
	//
	//m_HOOK = (sethook)GetProcAddress(DLL,"SetHook");
	//m_unHOOK = (uhook)GetProcAddress(DLL, "UnHook");
	//if (!m_HOOK)
	//{
	//	return 0;
	//}
	//m_HOOK((HWND)hwnd,KeyMouse);

	char pszMapName[MAX_PATH] = { 0 };
	sprintf(pszMapName, "%s%d", TS_MAPVIEW_NAME, m_Pid);
	m_pData.Create(pszMapName, pszMapName,sizeof(HookData));
	if (!m_pData.GetBuffer())
	{
		return false;
	}

	PHookData pdata = (PHookData)m_pData.GetBuffer();
	pdata->m_hwnd = hwnd;
	pdata->m_pid = m_Pid;
	memset(pszMapName,0, MAX_PATH);
	LPVOID poc = 0;

	if (Is64WindowSystem(hwnd))
	{
		sprintf(pszMapName,"%s","H:\\VS1\\FindPic\\x64\\Release\\Hook.dll");
		//EnumDllByZwQueryVirtualMem
		if (sizeof(LPVOID)==4)
		{
			return 0;
		}
		PMyProc p = (PMyProc)m_poc.GetBuffer();
		m_MyProc.X64 = p->X64;
		poc = (LPVOID)m_MyProc.X64;
		
	}
	else
	{
		sprintf(pszMapName, "%s", "H:\\VS1\\FindPic\\Release\\Hook.dll");
		PMyProc p = (PMyProc)m_poc.GetBuffer();
		m_MyProc.X86 = p->X86;
		poc = (LPVOID)m_MyProc.X86;

	}
	if (!poc)
	{
		return FALSE;
	}
	HANDLE  hadle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_Pid);
	if (!hadle)
	{
		return FALSE;
	}
	int strL = strlen(pszMapName);
	void* pRemoteAdrr = VirtualAllocEx(hadle, NULL, strL, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pRemoteAdrr == NULL)
	{
		//AfxMessageBox("在目标进程申请内存失败！");
		CloseHandle(hadle);
		return FALSE;
	}

	if (!WriteProcessMemory(hadle, pRemoteAdrr, pszMapName, strL, NULL))
	{
		//AfxMessageBox("在目标进程内存写DLL路径失败！");
	//	g_dlg3->SetAsmShowText("在目标进程内存写DLL路径失败！");
		CloseHandle(hadle);
		return FALSE;
	}

	DWORD dwpid = 0;
	HANDLE the1 = CreateRemoteThread(hadle, NULL, 0, (LPTHREAD_START_ROUTINE)poc, pRemoteAdrr, 0, &dwpid);
	WaitForSingleObject(the1, INFINITE);
	//GetExitCodeThread(the1, &g_undll);
	if (VirtualFreeEx(hadle, pRemoteAdrr, 0, MEM_RELEASE))
	{
		dwpid = dwpid;
	}
	CloseHandle(the1);
	CloseHandle(hadle);

	return TRUE;
}

long DXBind::UnBindWindow()
{
	if (!m_unHOOK)
	{
		return 0;
	}
	m_hwnd = 0;
	return m_unHOOK(m_hwnd);
}


long DXBind::lwSetpath(const char* path)
{
	if (isNull(path))
	{
		return false;
	}
	memset(m_SetPath, 0, MAX_PATH * 2);
	sprintf(m_SetPath, "%s", path);
	if (strlen(m_SetPath)<=1)
	{
		m_SetPathRet = FALSE;
		return 0;
	}
	m_SetPathRet = TRUE;
	return 1;
}

//返回系列字符所需要的空间
long DXBind::GetStrPosLen(long* dx, long* x, long* y)
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
bool DXBind::SetXy(long* x, long* y, long* w, long* h)
{
	RECT rtcc;
	::GetClientRect(m_hwnd, &rtcc);
	if (*x < 0)
	{
		*(long*)x = 0;
	}
	else if (*x >= rtcc.left + rtcc.right)
	{
		return false;
	}
	if (*y < 0)
	{
		*(long*)y = 0;
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
		*(long*)w = rtcc.left + rtcc.right;
	}
	if (*h <= 0)
	{
		return false;
	}
	else if (*h >= rtcc.top + rtcc.bottom)
	{
		*(long*)h = rtcc.top + rtcc.bottom;
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
bool DXBind::loadBitmap(LPCSTR strPath, LPVOID outdata, PBITMAPINFO PP)
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
			//prlongf("not a bmp picture.\n");
			delete[] pSrcData;
			return false;
		}

		//获取信息头
		memcpy(&BmpInfoHeader, pSrcData + BMP_FILE_HEADER_LENGTH, sizeof(BmpInfoHeader));
		*(PBITMAPINFO)PP = BmpInfoHeader;
		//将宽高信息传递出去
		//long N = 4 - ((width * 3) % 4);
		//判断BMP图片像素的位数
		if (BmpInfoHeader.bmiHeader.biBitCount == BMP_24_BIT)
		{
			long bioff = sizeof(BITMAPFILEHEADER) + BmpInfoHeader.bmiHeader.biSize;
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
	if (isNull(src) || isNull(p2)||(dwStyle!=24&& dwStyle!=32))
	{
		return 0;
	}
	long w = p2->bmiHeader.biWidth, h = p2->bmiHeader.biHeight;


	COLORREF** pp = new COLORREF * [h];
	for (size_t i = 0; i < h; i++)
	{
		pp[i] = new COLORREF[w];
		memset(pp[i], 0, sizeof(COLORREF) * w);
	}
	if (!pp)
	{
		return 0;
	}
	long N = w * h;//缓冲区大小
	p2->bmiHeader.biSizeImage = N;


	switch (dwStyle)
	{
	case BMP_32_BIT:
	{
		PUCHAR p = (PUCHAR)src;
		long realPitch = 0;
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
		long N = ((w * 3) % 4);
		if (N > 0)
		{
			N = 4 - ((w * 3) % 4);
		}
		PUCHAR p = (PUCHAR)src;
		long realPitch = 0;
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

	int ses = GetScreenDepth();
	if (ses != 32 && ses != 24)
	{
		if (!SetScreenDepth(32))
		{
			return false;
		}
	}

	if (!SetXy((long*)&x, (long*)&y, (long*)&w, (long*)&h))
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

	char* data = new char[bi.bmiHeader.biSizeImage];
	if (!data)
	{
		return false;
	}
	memset(data, 0, bi.bmiHeader.biSizeImage);
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
	::ReleaseDC(m_hwnd, pdc);
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
long DXBind::CmpBmpData(const LPVOID pic, const LPVOID pic1, LPCSTR delta_color, double sim, long x, long y, PBITMAPINFO PP)
{
	if (isNull(pic) || isNull(pic1) || isNull(delta_color) || isNull(PP))
	{
		return 0;
	}

	//处理偏色
	long R = 0, G = 0, B = 0;
	if (strlen((char*)delta_color) >= 6)
	{
		char tch[3] = { 0 };
		memset(tch, 0, 3);
		memcpy(tch, delta_color, 2);
		R = HexToInt(tch);
		memset(tch, 0, 3);
		memcpy(tch, delta_color + 2, 2);
		G = HexToInt(tch);
		memset(tch, 0, 3);
		memcpy(tch, delta_color + 4, 2);
		B = HexToInt(tch);
	}

	COLORREF** p = (COLORREF**)pic, ** p1 = (COLORREF**)pic1;
	//BOOL ret = FALSE;

	COLORREF simColor = GetSimLen(sim);

	BYTE loadR = 0, loadG = 0, loadB = 0;
	BYTE wndR = 0, wndG = 0, wndB = 0;
	COLORREF pLoadColor = 0, pWndColor = 0;
	BOOL ret = false;

	if (p1[0][0] == p1[0][PP->bmiHeader.biWidth - 1] && p1[0][0] == p1[PP->bmiHeader.biHeight - 1][0] && p1[0][0] == p1[PP->bmiHeader.biHeight - 1][PP->bmiHeader.biWidth - 1])
	{
		long len = 0;
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

	for (long i = 0; i < PP->bmiHeader.biHeight; i++)
	{
		for (long j = 0; j < PP->bmiHeader.biWidth; j++)
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
longX 变参指针:返回图片左上角的X坐标
longY 变参指针:返回图片左上角的Y坐标
*/
long DXBind::lwFindPic(long x_1, long y_1, long w_1, long h_1, LPCSTR pic_name, LPCSTR delta_color, double sim, long* longX, long* longY)
{
	//MessageBox(0, pic_name, delta_color, MB_OK);
	if (!::IsWindow(m_hwnd) || isNull(longX) || isNull(longY))
	{
		return -1;
	}
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		*(long*)longX = -1;
		*(long*)longY = -1;
		return -2;
	}
	MyPathArr FilePath = pic_name;
	if (!FilePath.GetPathFileLen())
	{
		*(long*)longX = -1;
		*(long*)longY = -1;
		return -9;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &pic, &bi))
	{
		*(long*)longX = -1;
		*(long*)longY = -1;
		return -3;
	}
	bool ret = false;
	for (size_t dx = 0; dx < FilePath.GetPathFileLen(); dx++)
	{
		PMyPath pta = FilePath.GetPathFile(dx);
		char stpath[MAX_PATH] = { 0 };
		if (!file_exist(pta->m_path))
		{
			if (!m_SetPathRet)
			{
				return -11;
			}
			sprintf(stpath, "%s%s", m_SetPath, pta->m_path);
			if (!file_exist(stpath))
			{
				return -10;
			}
		}
		else
		{
			sprintf(stpath, "%s", pta->m_path);
		}
		BITMAPINFO pbi;
		LPVOID data = 0;
		if (!loadBitmap(stpath, &data, &pbi))
		{
			continue;
		}
		long    w1 = pbi.bmiHeader.biWidth;
		long	h1 = pbi.bmiHeader.biHeight;
		long x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;
		

		for (long y = 0; y < y_len; y++)
		{
			for (size_t x = 0; x < x_len; x++)
			{
				ret = false;
				if (CmpBmpData(pic, data, delta_color, sim, x, y, &pbi))
				{
					ret = true;
					*(long*)longX = x + x_1;
					*(long*)longY = y + y_1;

					goto sEnd;
				}

			}

		}
	sEnd:
		COLORREF** fp = (COLORREF**)data;
		for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
		{
			delete fp[i];
		}
		delete[] fp;
		if (ret)
		{
			COLORREF** p = (COLORREF**)pic;
			for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
			{
				delete p[i];
			}
			delete[] pic;
			return dx;
		}

	}
	COLORREF** p = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete p[i];
	}
	delete[] pic;

	*(long*)longX = -1;
	*(long*)longY = -1;
	return -7;
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
long DXBind::lwFindPicEx(long x_1, long y_1, long w_1, long h_1, LPCSTR pic_name, LPCSTR delta_color, double sim, LPVOID otbf)
{
	if (!::IsWindow(m_hwnd) || isNull(otbf))
	{
		return  -1;
	}
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		return -2;
	}

	MyPathArr FilePath = pic_name;
	if (!FilePath.GetPathFileLen())
	{
		return -9;
	}

	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &pic, &bi))
	{
		return -3;
	}
	BOOL ret = FALSE;
	char* retStr = 0, * retStr_t = 0;
	long strdx = 0;

	for (size_t dx = 0; dx < FilePath.GetPathFileLen(); dx++)
	{
		PMyPath pta = FilePath.GetPathFile(dx);
		char stpath[MAX_PATH] = { 0 };
		if (!file_exist(pta->m_path))
		{
			if (!m_SetPathRet)
			{
				return -11;
			}
			sprintf(stpath, "%s%s", m_SetPath, pta->m_path);
			if (!file_exist(stpath))
			{
				return -10;
			}
		}
		else
		{
			sprintf(stpath, "%s", pta->m_path);
		}
		BITMAPINFO pbi;
		LPVOID data = 0;
		if (!loadBitmap(stpath, &data, &pbi))
		{
             continue;//打开图片失败找下一张图片
		}
		long    w1 = pbi.bmiHeader.biWidth;
		long	h1 = pbi.bmiHeader.biHeight;
		long x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;


		long xxx_t = 0;

		for (long y = 0; y < y_len; y++)
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
					long x1 = x, y1 = y, t_dx = strdx;
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
							sprintf(retStr, "%d,%d,%d", dx, x+x_1, y+y_1);
							strdx++;
						}
						else
						{
							t_dx += x1 + y1 + 5 + strlen(retStr);
							retStr_t = new char[t_dx];
							memset(retStr_t, 0, t_dx);
							sprintf(retStr_t, "%s|%d,%d,%d", retStr, dx, x+x_1, y+y_1);
							delete[] retStr;
							retStr = retStr_t;
							retStr_t = 0;
							strdx++;
						}
					}
					else
					{
						goto sEnd;
					}
					break;
				}
			}

		}
		COLORREF** fp = (COLORREF**)data;
		for (size_t i = 0; i < pbi.bmiHeader.biHeight; i++)
		{
			delete fp[i];
		}
		delete[] fp;
	}

	sEnd:
	
	COLORREF** p = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete p[i];
	}
	delete[] pic;


	if (strdx >= 1)
	{
		*(LPCSTR*)otbf = retStr;
		return 1;
	}
	return -6;
}

/*
x1 整形数 : 区域的左上X坐标
y1 整形数 : 区域的左上Y坐标
x2 整形数 : 区域的右下X坐标
y2 整形数 : 区域的右下Y坐标
color 字符串 : 颜色 格式为"RRGGBB-DRDGDB", 比如"123456-000000|aabbcc-202020".注意，这里只支持RGB颜色.
sim 双精度浮点数 : 相似度, 取值范围0.1 - 1.0
longX 变参指针:返回X坐标
longY 变参指针:返回Y坐标
*/
long DXBind::lwFindColor(long x1, long y1, long w1, long h1, LPCSTR color, double sim, long* longX, long* longY)
{

	if (!::IsWindow(m_hwnd) || isNull(color) || isNull(longX) || isNull(longY))
	{
		return  0;
	}
	if (!SetXy(&x1, &y1, &w1, &h1))
	{
		return 0;
	}
	MyRGBARR t_myrgb = color;
	if (t_myrgb.GetArrLen() == 0)
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

	COLORREF simColor = GetSimLen(sim);


	long loadR = 0, loadG = 0, loadB = 0;
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

			for (size_t k = 0; k < t_myrgb.GetArrLen(); k++)
			{
				PMyRGB pmy = t_myrgb.GetDxArr(k);
				//用于偏色比较
				if (abs(loadR - pmy->R) <= (pmy->Rp + simColor)
					&& abs(loadG - pmy->G) <= (pmy->Gp + simColor)
					&& abs(loadB - pmy->B) <= (pmy->Bp + simColor))
				{
					*(long*)longX = x;
					*(long*)longY = y;
					ret = TRUE;
					//break;
					goto sEnd;
				}
			}

		}

	}

sEnd:

	COLORREF** pp = (COLORREF**)pic;
	for (size_t i = 0; i < bi.bmiHeader.biHeight; i++)
	{
		delete pp[i];
	}
	delete[] pp;

	return ret;

}

//计算相似度
long DXBind::GetSimLen(double sim)
{
	if (sim <= 0.1)
	{
		sim = 0.1;
	}
	else if (sim > 1)
	{
		sim = 1;
	}

	int nsim = fractional_part_as_int(sim);//把小数部分取出变整数
	if (nsim % 100 == 0)
	{
		return 0;
	}
	nsim = (100 - nsim);
	nsim = nsim * 2.5 * 2;
	if (nsim > 255)
	{
		nsim = 255;
	}

	return nsim;
}

/*
x 整形数: 区域的左上X坐标
y 整形数: 区域的左上Y坐标
w  整形数: 区域的宽度
h  整形数: 区域的高度
color 字符串:颜色 格式为"RRGGBB-DRDGDB",比如"123456-000000|aabbcc-202020".这里只支持RGB颜色.
sim 双精度浮点数:相似度,取值范围0.1-1.0
count整形数:在宽度为width,高度为height的颜色块中，符合color颜色的最小数量.(注意,这个颜色数量可以在综合工具的二值化区域中看到)
width 整形数:颜色块的宽度
height 整形数:颜色块的高度
intX 变参指针:返回X坐标(指向颜色块的左上角)
intY 变参指针:返回Y坐标(指向颜色块的左上角)
*/
long DXBind::FindColorBlock(long x_1, long y_1, long w_1, long h_1, LPCSTR color, double sim, long count, long width, long height, long* intX, long* intY)
{
	if (!::IsWindow(m_hwnd) || isNull(color) || isNull(intX) || isNull(intY) || count <= 0)
	{
		return  0;
	}
	MyRGBARR t_myrgb = color;
	if (t_myrgb.GetArrLen() == 0)
	{
		*intX = -1;
		*intY = -1;
		return 0;
	}
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		*intX = -1;
		*intY = -1;
		return 0;
	}
	LPVOID pic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &pic, &bi))
	{
		*intX = -1;
		*intY = -1;
		return 0;
	}

	long    w1 = width;
	long	h1 = height;
	long x_len = w_1 - w1 + 1, y_len = h_1 - h1 + 1;
	BOOL ret = FALSE;
	COLORREF simColor = GetSimLen(sim);
	UCHAR wndR = 0, wndG = 0, wndB = 0;
	COLORREF** p = (COLORREF**)pic;
	int xxx_t = 0;
	for (long y = 0; y < y_len; y++)
	{
		xxx_t = 0;
		for (size_t x = 0; x < x_len; x++)
		{
			xxx_t = 0;
			for (size_t y1 = 0; y1 < h1; y1++)
			{
				for (size_t x1 = 0; x1 < w1; x1++)
				{
					wndR = GetRValue(p[y + y1][x + x1]);
					wndG = GetGValue(p[y + y1][x + x1]);
					wndB = GetBValue(p[y + y1][x + x1]);
					for (size_t k = 0; k < t_myrgb.GetArrLen(); k++)
					{
						PMyRGB p1 = t_myrgb.GetDxArr(k);

						if (abs(wndR - p1->R) <= (p1->Rp + simColor) && abs(wndG - p1->G) <= (p1->Gp + simColor) && abs(wndB - p1->B) <= (p1->Bp + simColor))
						{
							xxx_t++;
							break;
						}
					}
				}
			}
			if (xxx_t >= count)
			{
				*intX = x_1 + x;
				*intY = y_1 + y;
				for (size_t z = 0; z < h_1; z++)
				{
					delete[] p[z];
				}
				delete[] p;
				return 1;
			}
		}
	}

	*intX = -1;
	*intY = -1;
	for (size_t z = 0; z < h_1; z++)
	{
		delete[] p[z];
	}
	delete[] p;
	return 0;

}

//比较指定坐标点(x,y)的颜色
long DXBind::CmpColor(long x, long y, LPCSTR color, double sim)
{
	if ((DWORD64)color <= 0x10000 || x < 0 || y < 0)
	{
		return  0;
	}

	MyRGBARR t_myrgb = color;
	if (t_myrgb.GetArrLen() == 0)
	{
		return 0;
	}
	long w_1 = 2000, h_1 = 2000;
	if (!SetXy(&x, &y, &w_1, &h_1))
	{
		return 0;
	}
	if (x > w_1 || y > h_1)
	{
		return 0;
	}


	COLORREF simColor = GetSimLen(sim);
	UCHAR wndR = 0, wndG = 0, wndB = 0;
	HDC dc = GetDC(m_hwnd);
	if (!dc)
	{
		return 0;
	};
	COLORREF p = GetPixel(dc, x, y);
	DeleteDC(dc);
	wndR = GetRValue(p);
	wndG = GetGValue(p);
	wndB = GetBValue(p);
	BOOL ret = FALSE;
	for (size_t i = 0; i < t_myrgb.GetArrLen(); i++)
	{
		PMyRGB p1 = t_myrgb.GetDxArr(i);
		if (abs(wndR - p1->R) <= (p1->Rp + simColor) && abs(wndG - p1->G) <= (p1->Gp + simColor) && abs(wndB - p1->B) <= (p1->Bp + simColor))
		{
			ret = TRUE;
			goto endsl;
		}
	}

endsl:

	return ret;
}

//获取(x,y)的颜色,颜色返回格式"RRGGBB",注意,和按键的颜色格式相反
long DXBind::GetColor(long x, long y, LPCSTR* oft)
{
	if ((DWORD64)oft <= 0x10000 || x < 0 || y < 0)
	{
		return  0;
	}
	long w_1 = 2000, h_1 = 2000;
	if (!SetXy(&x, &y, &w_1, &h_1))
	{
		return 0;
	}
	if (x > w_1 || y > h_1)
	{
		return 0;
	}

	HDC dc = GetDC(m_hwnd);
	if (!dc)
	{
		return 0;
	}
	UCHAR wndR = 0, wndG = 0, wndB = 0;
	COLORREF p = ::GetPixel(dc, x, y);
	DeleteDC(dc);
	wndR = GetRValue(p);
	wndG = GetGValue(p);
	wndB = GetBValue(p);


	char* cht = new char[11];
	memset(cht, 0, 9);
	cht[0] = '0';
	cht[1] = 'x';
	cht[2] = '0';
	cht[3] = '0';
	char chb[3] = { 0 };
	if (wndR <= 9)
	{
		sprintf(chb, "0%x", wndR);

	}
	else
	{
		sprintf(chb, "%x", wndR);
	}
	sprintf(cht + strlen(cht), "%s", chb);
	memset(chb, 0, 3);
	if (wndG <= 9)
	{
		sprintf(chb, "0%x", wndG);
	}
	else
	{
		sprintf(chb, "%x", wndG);
	}
	sprintf(cht + strlen(cht), "%s", chb);
	memset(chb, 0, 3);
	if (wndB <= 9)
	{
		sprintf(chb, "0%x", wndB);
	}
	else
	{
		sprintf(chb, "%x", wndB);
	}
	sprintf(cht + strlen(cht), "%s", chb);

	*oft = cht;

	return 1;
}

long DXBind::GetColorNum(long x_1, long y_1, long w_1, long h_1, LPCSTR color, double sim)
{
	if (!::IsWindow(m_hwnd) || (DWORD64)color <= 0x10000)
	{
		return 0;
	}
	MyRGBARR t_myrgb = color;
	if (t_myrgb.GetArrLen() == 0)
	{
		return 0;
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


	BOOL ret = FALSE;
	COLORREF simColor = GetSimLen(sim);
	UCHAR wndR = 0, wndG = 0, wndB = 0;
	COLORREF** p = (COLORREF**)pic;
	int xxx_t = 0;
	for (long y = 0; y < h_1; y++)
	{
		for (size_t x = 0; x < w_1; x++)
		{

			wndR = GetRValue(p[y][x]);
			wndG = GetGValue(p[y][x]);
			wndB = GetBValue(p[y][x]);
			for (size_t k = 0; k < t_myrgb.GetArrLen(); k++)
			{
				PMyRGB p1 = t_myrgb.GetDxArr(k);

				if (abs(wndR - p1->R) <= (p1->Rp + simColor) && abs(wndG - p1->G) <= (p1->Gp + simColor) && abs(wndB - p1->B) <= (p1->Bp + simColor))
				{
					xxx_t++;
					break;
				}
			}


		}
	}


	for (size_t z = 0; z < h_1; z++)
	{
		delete[] p[z];
	}
	delete[] p;



	return xxx_t;
}
//抓取指定区域(x1, y1, x2, y2)的图像,保存为file(24位位图)
long DXBind::Capture(long x, long y, long w, long h, LPCSTR file)
{
	if ((DWORD64)file <= 0x10000)
	{
		return 0;
	}
	if (!SetXy(&x, &y, &w, &h))
	{
		return 0;
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
	BmpTo24DataFile(file, data, &bi);//保存成本地文件
	::DeleteDC(cacheDC);
	::SelectObject(cacheDC, pOHEditmap);
	::DeleteObject(HEditBmp);




	return 0;
}


bool DXBind::IsDisplayDead_bak(DWORD x, DWORD y, DWORD w, DWORD h, LPVOID outdata, PBITMAPINFO PP)
{
	if (!::IsWindow(m_hwnd))
	{
		return false;
	}
	if (!SetXy((long*)&x, (long*)&y, (long*)&w, (long*)&h))
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

	char* data = new char[bi.bmiHeader.biSizeImage];
	if (!data)
	{
		return false;
	}
	memset(data, 0, bi.bmiHeader.biSizeImage);
	::GetDIBits(cacheDC, HEditBmp, 0, h, data, &bi, DIB_RGB_COLORS);
	::DeleteDC(cacheDC);
	::SelectObject(cacheDC, pOHEditmap);
	::DeleteObject(HEditBmp);
	::ReleaseDC(m_hwnd, pdc);
	*(char**)outdata = data;
	*PP = bi;
	return true;
}
//卡屏检测
long DXBind::IsDisplayDead(long x, long y, long w, long h, long t)
{
	if (t == 0)
	{
		return 0;
	}
	if (!::IsWindow(m_hwnd))
	{
		return  1;
	}
	if (!SetXy(&x, &y, &w, &h))
	{
		return 1;
	}
	LPVOID pic = 0, pic1 = 0;
	BITMAPINFO bi = { 0 }, bi1 = { 0 };
	if (!IsDisplayDead_bak(x, y, w, h, &pic, &bi))
	{
		return 1;
	}
	Sleep(t * 1000);
	if (!IsDisplayDead_bak(x, y, w, h, &pic1, &bi1))
	{

		delete[] pic;
		return 1;
	}

	BOOL ret = FALSE;

	char* p = (char*)pic;
	char* p1 = (char*)pic1;
	for (size_t i = 0; i < bi.bmiHeader.biWidth * bi1.bmiHeader.biHeight; i++)
	{
		if (p[i] != p1[i])
		{
			ret = TRUE;
			goto endls;
		}
	}


endls:
	delete[] p;

	delete[] p1;
	if (ret == FALSE)
	{
		return 1;
	}

	return 0;
}
/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:转换后的文件保存路径
参数3:是否覆盖原来的文件
返回值:成功返回0
*/
long DXBind::lwBmp32To24(LPCSTR Filepath, LPCSTR FilepathBak, bool ret)
{
	if (isNull(Filepath))
	{
		return 1;
	}
	if (ret == false && isNull(FilepathBak))
	{
		return 2;
	}
	HANDLE hFile = CreateFile(Filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
	{
		return 3;
	}
	DWORD fileSize = GetFileSize(hFile, NULL);    //获得文件大小的低两字节
	char* pSrcData = new char[fileSize];    //创建缓冲区
	if (!pSrcData)
	{
		return 4;
	}
	DWORD realRead = 0;

	bool ret1 = false;
	ret1 = ReadFile(hFile, pSrcData, fileSize, &realRead, NULL);    //拷贝文件的内容给缓冲区fileBuff
	CloseHandle(hFile);
	if (!ret)
	{
		delete[] pSrcData;
		return 5;
	}

	PBITMAPINFO BmpInfoHeader = (PBITMAPINFO)((DWORD64)pSrcData + BMP_FILE_HEADER_LENGTH);
	long N = 4 - ((BmpInfoHeader->bmiHeader.biWidth * 3) % 4);
	BITMAPINFOHEADER bi = { 0 };
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = BmpInfoHeader->bmiHeader.biWidth;
	bi.biHeight = BmpInfoHeader->bmiHeader.biHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BMP_24_BIT;
	bi.biCompression = 0;
	bi.biSizeImage = ((BmpInfoHeader->bmiHeader.biWidth * 3) * BmpInfoHeader->bmiHeader.biHeight) + (N * BmpInfoHeader->bmiHeader.biHeight);
	bi.biXPelsPerMeter = BmpInfoHeader->bmiHeader.biXPelsPerMeter;
	bi.biYPelsPerMeter = BmpInfoHeader->bmiHeader.biYPelsPerMeter;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	PBITMAPFILEHEADER pbi = (PBITMAPFILEHEADER)pSrcData;
	BITMAPFILEHEADER BiHeder = { 0 };
	BiHeder.bfType = pbi->bfType;
	BiHeder.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	long OffSize = BiHeder.bfSize;
	BiHeder.bfOffBits = BiHeder.bfSize;
	BiHeder.bfSize += bi.biSizeImage + 2;
	BiHeder.bfReserved1 = pbi->bfReserved1;
	BiHeder.bfReserved2 = pbi->bfReserved2;
	char* bmp24 = new char[BiHeder.bfSize];
	if (!bmp24)
	{
		delete[] pSrcData;
		return 6;
	}
	memset(bmp24, 0, BiHeder.bfSize);
	memcpy(bmp24, &BiHeder, sizeof(BITMAPFILEHEADER));
	memcpy(bmp24 + sizeof(BITMAPFILEHEADER), &bi, sizeof(BITMAPINFOHEADER));
	long w = bi.biWidth, h = bi.biHeight;
	long dx = 0, dx1 = 0;
	PCHAR p = (PCHAR)((DWORD64)bmp24 + OffSize);
	PCHAR p1 = (PCHAR)((DWORD64)pSrcData + OffSize);
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
	if (ret)
	{
		fopen_s(&fp, Filepath, "wb+");
	}
	else
	{
		fopen_s(&fp, FilepathBak, "wb+");
	}
	if (NULL == fp)
	{
		//FreeRes_ShowError("LockResource");
		delete[] bmp24;
		delete[] pSrcData;
		return 7;
	}
	long fSize = fwrite(bmp24, sizeof(char), BiHeder.bfSize, fp);
	fclose(fp);

	delete[] bmp24;
	delete[] pSrcData;

	if (fSize)
	{
		return 0;
	}
	return GetLastError();
}

/*
功能:32位位图转换24
参数1:保存文件的路径
参数2:32位位图文件缓冲区
参数3:32位位图文件信息指针
返回值:返回转换后的24位 位图缓冲区 可以直接
*/
bool DXBind::BmpTo24DataFile(const char* Filepath, const char* src, PBITMAPINFO bmp)
{
	if (isNull(src) || isNull(bmp) || isNull(Filepath))
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

string get_disk_smart_serials(int index)
{
	std::string ret;

	char physical[256]{ 0 };
	sprintf_s(physical, 256, "\\\\.\\PhysicalDrive%d", index);

	HANDLE disk = CreateFileA(physical, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (disk != INVALID_HANDLE_VALUE)
	{
		STORAGE_PROPERTY_QUERY query{ };
		query.PropertyId = StorageDeviceProperty;
		query.QueryType = PropertyStandardQuery;

		const int b_size = 1024 * 10;
		char* buf = new char[b_size];
		if (buf)
		{
			memset(buf, 0, b_size);
			DWORD r = 0;
			BOOL status = DeviceIoControl(disk, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), buf, b_size, &r, NULL);
			if (status)
			{
				STORAGE_DEVICE_DESCRIPTOR* descrip = (STORAGE_DEVICE_DESCRIPTOR*)buf;
				if (descrip->SerialNumberOffset > 0)
				{
					std::string serial = buf + descrip->SerialNumberOffset;
					serial.erase(std::remove_if(serial.begin(), serial.end(), [](unsigned char x) {return std::isspace(x); }), serial.end());
					ret = serial;
				}
			}

			delete[] buf;
		}

		CloseHandle(disk);
	}

	return ret;
}

long DXBind::GetDiskSerial(long index, LPCSTR* outbuf)
{
	char physical[256]{ 0 };
	sprintf_s(physical, 256, "\\\\.\\PhysicalDrive%d", index);

	HANDLE disk = CreateFileA(physical, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	char* serial = 0;
	if (disk != INVALID_HANDLE_VALUE)
	{
		STORAGE_PROPERTY_QUERY query{ };
		query.PropertyId = StorageDeviceProperty;
		query.QueryType = PropertyStandardQuery;

		const int b_size = 1024 * 10;
		char* buf = new char[b_size];
		if (buf)
		{
			memset(buf, 0, b_size);
			DWORD r = 0;
			BOOL status = DeviceIoControl(disk, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), buf, b_size, &r, NULL);
			if (status)
			{
				STORAGE_DEVICE_DESCRIPTOR* descrip = (STORAGE_DEVICE_DESCRIPTOR*)buf;
				if (descrip->SerialNumberOffset > 0)
				{
					serial = buf + descrip->SerialNumberOffset;
					
				}
			}

			delete[] buf;
		}

		CloseHandle(disk);
	}
	if (serial)
	{
		int len = strlen(serial);
		char* obuf = new char[len +1];
		memset(obuf, 0, len + 1);
		for (size_t i = 0; i < len; i++)
		{
			if (serial[i]!=' ')
			{
				obuf[strlen(obuf)] = serial[i];
			}
		}
		*outbuf = obuf;
		
		return 1;
	}
	return 0;
}

long DXBind::GetDisplayInfo(LPCSTR* outbuf)
{
	//代码
	LPDIRECT3D9 pD3D = NULL;
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);//创建Direct 3D对象
	DWORD m_dwNumAdapters = pD3D->GetAdapterCount();//获得显卡数量
	char* str=0, *str1=0;
	for (UINT iAdapter = 0; iAdapter < m_dwNumAdapters; iAdapter++)
	{
		D3DADAPTER_IDENTIFIER9 di;
		pD3D->GetAdapterIdentifier(iAdapter, 0, &di);//获得显卡信息
		char  szBuf[256] = { 0 };
		sprintf(szBuf, "%s", di.Description);//  
		int len = strlen(szBuf);
		if (iAdapter ==0)
		{
			str = new char[len + 1];
			memset(str, 0, len + 1);
			sprintf(str, "%s",szBuf);
		}
		else
		{
			str1 = new char[strlen(str)+len + 2];
			memset(str1, 0, strlen(str) + len + 2);
			sprintf(str1, "%s|%s",str, szBuf);
			delete[] str;
			str = str1;
			str1 = 0;
		}
		//原文链接：https ://blog.csdn.net/yuzhongzhu/article/details/3923158
	}
	if (str)
	{
		*outbuf = str;
		return 1;
	}
	return 0;
}

long DXBind::GetDPI()
{
	//HWND hd = GetDesktopWindow();
// 获取窗口当前显示的监视器
	// 使用桌面的句柄.
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度与高度
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	//int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// 获取监视器物理宽度与高度
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	//int cxPhysical = dm.dmPelsWidth;
	int cyPhysical = dm.dmPelsHeight;

	// 缩放比例计算  实际上使用任何一个即可
	//double horzScale = ((double)cxPhysical / (double)cxLogical);
	double vertScale = ((double)cyPhysical / (double)cyLogical);
	//assert(horzScale == vertScale); // 宽或高这个缩放值应该是相等的
	int zoom = vertScale * 100;
	switch (zoom) {
	case 100:
	
		return 100;
	case 125:
		return 125;
	case 150:

		return 150;
	case 175:
		return 175;		
	case 200:
		return 200;
	default:

		break;
	}


		//原文链接：https ://blog.csdn.net/yp18792574062/article/details/88351342
	return 0;
}

long DXBind::RunApp(LPCSTR path,  long type)
{

		if (!file_exist(path))
		{
			return 0;
		}
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
	
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = TRUE;
		BOOL ret = CreateProcessA(path, NULL,
			NULL, NULL, FALSE, CREATE_NO_WINDOW,
			NULL, NULL, &si, &pi);
		if (!ret)
		{
			return 0;
		}

		switch (type)
		{
		case 0:
		{
			return pi.dwProcessId;
		}
		case 1:
		{
			return pi.dwThreadId;
		}
		case 2:
		{
			return (long)pi.hProcess;
		}
		case 3:
		{
			return (long)pi.hThread;
		}
		default:
			break;
		}
		return 0;
	
}

long long DXBind::GetHDiskCode()
{
	LONGLONG TZMM = SCSI(0);
	if (TZMM)
	{
		return TZMM;
	}
	return IDE(0);
}

long DXBind::GetCpuCode(LPCSTR* otstr)
{
	//LPVOID retp = 0;
	//GetinitCpu(&retp);
	char* buf = new char[64];
	
	try
	{
		Mycpu p;
		
	
		memset(buf, 0, 64);

#if _WIN64
		int ret = 0;
		
		LPVOID t_p = VirtualAlloc(NULL, sizeof(g_incpu), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!t_p)
		{
			return 0;
		}
		memcpy(t_p, g_incpu, sizeof(g_incpu));
		SetCpuidStr(t_p, 1, &p, &ret);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t_p,0,0,0 );
		while (1)
		{
			if (ret)
			{
				break;
			}
			Sleep(10);//延时
		}

		if (p.edx)
		{
			sprintf(buf, "%08X", p.edx);
		}
		if (p.eax)
		{
			sprintf(buf + strlen(buf), "%08X", p.eax);
		}

		ret = 0;
		memcpy(t_p, g_incpu, sizeof(g_incpu));
		SetCpuidStr(t_p, 3, &p, &ret);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t_p, 0, 0, 0);
		while (1)
		{
			if (ret)
			{
				break;
			}
			mysleep(10);//延时
		}



		if (p.ebx)
		{
			sprintf(buf + strlen(buf), "%08X", p.ebx);
		}
		if (p.eax)
		{
			sprintf(buf + strlen(buf), "%08X", p.eax);
		}

		ret=VirtualFree(t_p, 0, MEM_RELEASE);
			


#else
	initCpu(1, &p);
	if (p.edx)
	{
		sprintf(buf, "%08X", p.edx);
	}
	if (p.eax)
	{
		sprintf(buf + strlen(buf), "%08X", p.eax);
	}
	initCpu(3, &p);
	if (p.edx)
	{
		sprintf(buf + strlen(buf), "%08X", p.edx);
	}
	if (p.eax)
	{
		sprintf(buf + strlen(buf), "%08X", p.eax);
	}
#endif



		


		




		*otstr = buf;
		//SetinitCpu(&retp);
		return 1;
	}
	catch (const std::exception&)
	{
		delete[] buf;
		return 0;
	}
	
	return 0;
}

LONGLONG DXBind::GetMainBoardInfoByCmd()
{
	return ::GetMainBoardInfoByCmd();
}

long DXBind::GetMachineCode(LPCSTR* outstr)
{
	char* mac = GetMac();
	if (!mac)
	{
		return 0;
	}

	char* Disk = 0;
	GetDiskSerial(0,(LPCSTR*)&Disk);

	//MessageBox(0, mac, "lw", MB_OKCANCEL);
	PUCHAR p = (PUCHAR)Disk;
	if (!Disk)
	{
		Disk = new char[18];
		memset(Disk, 0, 18);
		for (size_t i = 0; i < 16; i++)
		{
			
			UCHAR t_ch = CharToInt_bak(Disk[i]);
			while (1)
			{
				int ret = 0;
				for (size_t j = 0; j < i; j++)
				{
					if (Disk[j] == t_ch)
					{
						t_ch += 1;
						ret = 1;
						if (t_ch == 58)
						{
							t_ch = 'a';
						}
						if (t_ch == 'f' + 1)
						{
							t_ch = '0';
						}
						break;
					}
				}

				if (ret == 0)
				{
					break;
				}
			}
			Disk[strlen(Disk)] = t_ch;
		}
	}
	else
	{
	int	len = strlen(Disk);
	for (size_t i = 0; i < len; i++)
	{
		UCHAR t_ch = CharToInt_bak(p[i]);
		while (1)
		{
			int ret = 0;
			for (size_t j = 0; j < i; j++)
			{
				if (Disk[j] == t_ch)
				{
					t_ch += 1;
					ret = 1;
					if (t_ch == 58)
					{
						t_ch = 'a';
						
					}
					if (t_ch == 'f' + 1)
					{
						t_ch = '0';
					}
					break;
				}
			}

			if (ret == 0)
			{
				break;
			}
		}
		Disk[i] = t_ch;
	}
	}

	int len = strlen(mac);
	char* macBak = new char[len+1];
	memset(macBak, 0, len+1);
	
	for (size_t i = 0; i < len; i++)
	{
		if (mac[i]!='-')
		{
			//macBak[strlen(macBak)]= CharToInt_bak(mac[i]);
			UCHAR t_ch = CharToInt_bak(macBak[i]);
			while (1)
			{
				int ret = 0;
				for (size_t j = 0; j < i; j++)
				{
					if (macBak[j] == t_ch)
					{
						t_ch += 1;
						ret = 1;
						if (t_ch == 58)
						{
							t_ch = 'a';
						}
						if (t_ch == 'f' + 1)
						{
							t_ch = '0';
						}
						break;
					}
				}

				if (ret == 0)
				{
					break;
				}
			}
			macBak[strlen(macBak)] = t_ch;
		}
	}
	delete[] mac;


	char* cpu = 0;
	GetCpuCode((LPCSTR*)&cpu);
	if (!cpu)
	{
		delete[] Disk;		
		return 0;
	}
	len = strlen(cpu);

	for (size_t i = 0; i < len; i++)
	{
		UCHAR t_ch = CharToInt_bak(cpu[i]);
		while (1)
		{
			int ret = 0;
			for (size_t j = 0; j < i; j++)
			{
				if (cpu[j] == t_ch)
				{
					t_ch += 1;
					ret = 1;
					if (t_ch == 58)
					{
						t_ch = 'a';
					}
					if (t_ch == 'f' + 1)
					{
						t_ch = '0';
					}
					break;
				}
			}

			if (ret == 0)
			{
				break;
			}
		}
		cpu[i] = t_ch;
	}

LONGLONG Diskl=GetHDiskCode();
char*  DiskHex =IntToHex(Diskl);
 len = strlen(DiskHex);
for (size_t i = 0; i < len; i++)
{
	UCHAR t_ch= CharToInt_bak(DiskHex[i]);
	while (1)
	{
		int ret = 0;
		for (size_t j = 0; j < i; j++)
		{
			if (DiskHex[j]==t_ch)
			{
				t_ch += 1;
				ret = 1;
				if (t_ch==58)
				{
					t_ch = 'a';
				}
				if (t_ch == 'f'+1)
				{
					t_ch = '0';
				}
				break;
			}
		}

		if (ret==0)
		{
			break;
		}
	}
	DiskHex[i] = t_ch;
}
len = strlen(DiskHex) + strlen(cpu) + strlen(macBak) + strlen(Disk)+1;
char* str = new char[len];
memset(str, 0, len);
sprintf(str, "%s%s%s%s", DiskHex, macBak, cpu, Disk);

if (str)
{
	*outstr = str;
	delete[] DiskHex;
	delete[] macBak;
	delete[] cpu;
	delete[] Disk;
	return 1;
}

	return 0;
}

long DXBind::GetMachineCodeNoMac(LPCSTR* outstr)
{

	char* Disk = 0;
	GetDiskSerial(0, (LPCSTR*)&Disk);

	//MessageBox(0, mac, "lw", MB_OKCANCEL);
	PUCHAR p = (PUCHAR)Disk;
	if (!Disk)
	{
		return 0;
	}
	else
	{
		int	len = strlen(Disk);
		for (size_t i = 0; i < len; i++)
		{
			UCHAR t_ch = CharToInt_bakOnMac(p[i]);
			while (1)
			{
				int ret = 0;
				for (size_t j = 0; j < i; j++)
				{
					if (Disk[j] == t_ch)
					{
						t_ch += 1;
						ret = 1;
						if (t_ch == 58)
						{
							t_ch = 'a';

						}
						if (t_ch == 'f' + 1)
						{
							t_ch = '0';
						}
						break;
					}
				}

				if (ret == 0)
				{
					break;
				}
			}
			Disk[i] = t_ch;
		}
	}




	char* cpu = 0;
	GetCpuCode((LPCSTR*)&cpu);
	if (!cpu)
	{
		delete[] Disk;
		return 0;
	}
 int	len = strlen(cpu);

	for (size_t i = 0; i < len; i++)
	{
		UCHAR t_ch = CharToInt_bakOnMac(cpu[i]);
		while (1)
		{
			int ret = 0;
			for (size_t j = 0; j < i; j++)
			{
				if (cpu[j] == t_ch)
				{
					t_ch += 1;
					ret = 1;
					if (t_ch == 58)
					{
						t_ch = 'a';
					}
					if (t_ch == 'f' + 1)
					{
						t_ch = '0';
					}
					break;
				}
			}

			if (ret == 0)
			{
				break;
			}
		}
		cpu[i] = t_ch;
	}

	LONGLONG Diskl = GetHDiskCode();
	char* DiskHex = IntToHex(Diskl);
	len = strlen(DiskHex);
	for (size_t i = 0; i < len; i++)
	{
		UCHAR t_ch = CharToInt_bakOnMac(DiskHex[i]);
		while (1)
		{
			int ret = 0;
			for (size_t j = 0; j < i; j++)
			{
				if (DiskHex[j] == t_ch)
				{
					t_ch += 1;
					ret = 1;
					if (t_ch == 58)
					{
						t_ch = 'a';
					}
					if (t_ch == 'f' + 1)
					{
						t_ch = '0';
					}
					break;
				}
			}

			if (ret == 0)
			{
				break;
			}
		}
		DiskHex[i] = t_ch;
	}

	LONGLONG may=GetMainBoardInfoByCmd();
   char*	macBak = IntToHex(may);
   if (!macBak)
   {
	   delete[] DiskHex;
	   delete[] cpu;
	   delete[] Disk;
	   return 0;
   }
   len = strlen(macBak);
   for (size_t i = 0; i < len; i++)
   {
	   UCHAR t_ch = CharToInt_bakOnMac(macBak[i]);
	   while (1)
	   {
		   int ret = 0;
		   for (size_t j = 0; j < i; j++)
		   {
			   if (macBak[j] == t_ch)
			   {
				   t_ch += 1;
				   ret = 1;
				   if (t_ch == 58)
				   {
					   t_ch = 'a';
				   }
				   if (t_ch == 'f' + 1)
				   {
					   t_ch = '0';
				   }
				   break;
			   }
		   }

		   if (ret == 0)
		   {
			   break;
		   }
	   }
	   macBak[i] = t_ch;
   }

	len = strlen(DiskHex) + strlen(cpu) + strlen(macBak) + strlen(Disk) + 1;
	char* str = new char[len];
	memset(str, 0, len);
	sprintf(str, "%s%s%s%s", DiskHex, macBak, cpu, Disk);

	if (str)
	{
		*outstr = str;
		delete[] DiskHex;
		delete[] macBak;
		delete[] cpu;
		delete[] Disk;
		return 1;
	}

	return 0;
}

char* DXBind::GetNetTime()
{
	struct tm* tim = new struct tm;
	time_t timeRecv1;
	char* bfu = new char[50];
	memset(bfu, 0, 50);
	if (get_internet_time(&timeRecv1))
	{
		sprintf(bfu, "网络连接失败!");
		return bfu;
	}


	if (timeRecv1<0)
	{
		sprintf(bfu, "获取网络时间超时!");
		return bfu;
	}
	tim = localtime(&timeRecv1);//这个函数返回了一个指向struct tm类型的地址
	tim->tm_year += 1900;
	tim->tm_mon += 1;


	int len =sprintf(bfu, "%d-%02d-%02d %02d:%02d:%02d", tim->tm_year, tim->tm_mon, tim->tm_mday, tim->tm_hour, tim->tm_min, tim->tm_sec);
	if (!len)
	{
		delete[] bfu;
		return 0;
	}

	return bfu;
}

long DXBind::GetNetTimeByIp(LPCSTR ip, LPCSTR* outstr)
{
	struct tm* tim = new struct tm;
	time_t timeRecv1;
	char* bfu = new char[50];
	memset(bfu, 0, 50);
	if (get_internet_timeip(&timeRecv1,ip))
	{
		sprintf(bfu, "网络连接失败!");
		*outstr = bfu;
		return 0;
	}


	if (timeRecv1 < 0)
	{
		sprintf(bfu, "获取网络时间超时!");
		*outstr = bfu;
		return 0;
	}
	tim = localtime(&timeRecv1);//这个函数返回了一个指向struct tm类型的地址
	tim->tm_year += 1900;
	tim->tm_mon += 1;


	int len = sprintf(bfu, "%d-%02d-%02d %02d:%02d:%02d", tim->tm_year, tim->tm_mon, tim->tm_mday, tim->tm_hour, tim->tm_min, tim->tm_sec);
	if (!len)
	{
		delete[] bfu;
		return 0;
	}
	*outstr = bfu;
	return 1;
}

BOOL DXBind::Is64BitSystem()
{
#ifdef _WIN64
	return true;
#elif _WIN32
	HMODULE hModule = LoadLibrary(TEXT("kernel32.dll"));

	typedef UINT(WINAPI* _pGetSystemWow64DirectoryA)(LPSTR, UINT);

	_pGetSystemWow64DirectoryA funcaddr = (_pGetSystemWow64DirectoryA)GetProcAddress(hModule, "GetSystemWow64DirectoryA");
	if (funcaddr == NULL)
	{
		FreeLibrary(hModule);
		return FALSE;
	}
	else
	{
		LPSTR lpBuffer = new char[MAX_PATH];
		UINT ret = funcaddr(lpBuffer, MAX_PATH);
		FreeLibrary(hModule);
		delete[] lpBuffer;
		return ret > 0;
	}
#else
#error 
#endif
}

BOOL DXBind::Is64WindowSystem(long hwnd)
{
	if (!hwnd)
	{
		return FALSE;
	}
	DWORD pid = GetWindowProcessId(hwnd);
	if (!pid)
	{
		return FALSE;
	}
	HANDLE  ha=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	if (!ha)
	{
		return FALSE;
	}
	BOOL oret = FALSE;
   ::IsWow64Process(ha,&oret);
	CloseHandle(ha);
	return !oret;
}

long DXBind::GetScreenDepth()
{
	HDC dc = GetDC(NULL);
	int ret = GetDeviceCaps(dc, BITSPIXEL);
	DeleteDC(dc);
	return ret;
}

long DXBind::SetScreenDepth(long dmBitsPerPel)
{
	if (dmBitsPerPel<0|| dmBitsPerPel>32)
	{
		return 0;
	}
	bool  bChanged = 0;
	DEVMODE dm;
	memset(&dm, 0, sizeof(DEVMODE));
	EnumDisplaySettings(NULL, ENUM_REGISTRY_SETTINGS, &dm);
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = dmBitsPerPel;
	//dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	int ret = ChangeDisplaySettings(&dm, DISP_CHANGE_SUCCESSFUL);
	return (ret == 0);
}

BOOL DXBind::SetDict(LPCSTR file)
{
	if ((ULONG64)file<=0x10000)
	{
		return 0;
	}
	int ret=m_Dict.OpenFile(file,m_SetPath);

	return ret;
}

long DXBind::FindStr(long x_1, long y_1, long w_1, long h_1, LPCSTR str, LPCSTR color_format, double sim, long* intX, long* intY)
{
	if (!::IsWindow(m_hwnd) || isNull(intX) || isNull(intY) || !m_Dict.GetDirLen())
	{
		return -1;
	}
	*(long*)intX = -1;
	*(long*)intY = -1;
	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		return -1;
	}

	MyRGBARR color = color_format;
	MyPathArr str1 = str;
	if (color.GetArrLen() == 0 || str1.GetPathFileLen() == 0)
	{
		return -1;
	}


	COLORREF t_sim = GetSimLen(sim);//计算相似度
	LPVOID dpic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &dpic, &bi))
	{
		return -1;
	}
	bool ret = false;
	char** pic = new char* [h_1];
	for (size_t i = 0; i < h_1; i++)
	{
		pic[i] = new char[w_1];
		memset(pic[i], 0, w_1);
	}

	COLORREF** pp = (COLORREF**)dpic;
	UCHAR R = 0, G = 0, B = 0;
	for (size_t y = 0; y < h_1; y++)
	{
		for (size_t x = 0; x < w_1; x++)
		{
			COLORREF t_coo = pp[y][x];
			R = GetRValue(t_coo);
			G = GetGValue(t_coo);
			B = GetBValue(t_coo);
			ret = false;
			for (size_t k = 0; k < color.GetArrLen(); k++)
			{
				PMyRGB p1 = color.GetDxArr(k);
				if (abs(R - p1->R) <= p1->Rp + t_sim && abs(G - p1->G) <= p1->Gp + t_sim && abs(B - p1->B) <= p1->Bp + t_sim)
				{
					ret = true;
					break;
				}
			}
			if (ret)
			{
				pic[y][x] = 1;
				continue;
			}
			pic[y][x] = 0;
		}
	}

	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pp[i];
	}
	delete[] pp;
	int t_dx = 0;
	for (size_t dx = 0; dx < str1.GetPathFileLen(); dx++)
	{
		PMyPath p = str1.GetPathFile(dx);
		int stlen = 0;
		while (1)
		{
			ret = false;
			char t_ch[MAX_PATH] = { 0 };
			if (p->m_path[stlen] < 0)
			{
				t_ch[0] = p->m_path[stlen];
				stlen++;
				t_ch[1] = p->m_path[stlen];
				stlen++;
			}
			else
			{
				t_ch[0] = p->m_path[stlen];
				stlen++;
			}
			for (size_t i = 0; i < m_Dict.GetDirLen(); i++)
			{
				PMyDict pdis = m_Dict.GetDirDx(i);
				if (strcmp(t_ch, pdis->m_dirChar) == 0)
				{
					t_dx += pdis->m_linek;
					break;
				}
			}
			if (stlen >= strlen(p->m_path))
			{
				break;
			}

		}
		if (!t_dx)
		{
			goto endsl;
		}
		stlen = w_1 - t_dx + 1;
		t_dx = 0;
		//0123456

		for (size_t y = 0; y < h_1 - 10; y++)
		{
			ret = false;
			int chlen = 0;
			for (size_t x = 0; x < stlen; x++)
			{

				int t_dx2 = 0;
				chlen = 0;
				while (1)
				{
					int didx = -1;
					char t_ch[MAX_PATH] = { 0 };
					while (1)
					{
						if (p->m_path[chlen] < 0)
						{
							t_ch[0] = p->m_path[chlen];
							chlen++;
							t_ch[1] = p->m_path[chlen];
							chlen++;
						}
						else
						{
							t_ch[0] = p->m_path[chlen];
							chlen++;
						}

						ret = false;
						for (size_t j = 0; j < m_Dict.GetDirLen(); j++)
						{
							PMyDict t_p = m_Dict.GetDirDx(j);
							if (strcmp(t_p->m_dirChar, t_ch) == 0)
							{
								didx = j;
								ret = true;
								break;
							}
						}
						if (didx >= 0)
						{
							break;
						}
						if (chlen >= strlen(p->m_path))
						{
							ret = false;
							goto endsl;
						}

					}


					if (didx == -1)
					{
						ret = false;
						goto endsl;
					}

					PMyDict t_p = m_Dict.GetDirDx(didx);
					if (!t_p)
					{
						ret = false;
						goto endsl;
					}
					int w = t_p->m_linek, h = 11;
					int t_dx1 = 0;
					for (size_t j = t_dx2; j < t_dx2 + w; j++)
					{
						for (size_t k = 0; k < h; k++)
						{
							if (pic[y + k][x + j] != t_p->m_dir[t_dx1] - ('0'))
							{
								ret = false;
								break;
							}
							t_dx1++;
							ret = true;
						}
						if (!ret)
						{
							break;
						}
					}
					t_dx2 += w;//12
					if (!ret)
					{
						break;
					}
					if (chlen >= strlen(t_ch))
					{
						for (size_t i = 0; i < w; i++)
						{
							int t_xx = y;
							if (y > 0)
							{
								t_xx = y - 1;
							}


							if (pic[y - 1][x + i])
							{
								ret = false;
								break;
							}
						}

						if (ret)
						{
							*intX = x_1 + x;
							*intY = y_1 + y;
							t_dx = dx;
							goto endsl;
						}
						break;
					}


				}

			}

		}
	}

endsl:

	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pic[i];
	}
	delete[] pic;
	if (ret)
	{
		return t_dx;
	}
	return -1;
}

long DXBind::FindStrEx(long x_1, long y_1, long w_1, long h_1, LPCSTR str, LPCSTR color_format, double sim, LPCSTR* outstr)
{
	if (!::IsWindow(m_hwnd) || !m_Dict.GetDirLen())
	{
		return 0;
	}

	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		return 0;
	}

	MyRGBARR color = color_format;
	MyPathArr str1 = str;
	if (color.GetArrLen() == 0 || str1.GetPathFileLen() == 0)
	{
		return -1;
	}

	int t_dx = 0;
	int strPos = 0;
	COLORREF t_sim = GetSimLen(sim);//计算相似度
	LPVOID dpic = 0;
	BITMAPINFO bi = { 0 };
	bool ret = false;

	for (size_t dx = 0; dx < str1.GetPathFileLen(); dx++)
	{
		PMyPath p = str1.GetPathFile(dx);
		int stlen = 0;
		char t_chbak[MAX_PATH] = { 0 };
		while (1)
		{
			ret = false;
			char t_ch[3] = { 0 };
			if (p->m_path[stlen] < 0)
			{
				t_ch[0] = p->m_path[stlen];
				stlen++;
				t_ch[1] = p->m_path[stlen];
				stlen++;
			}
			else
			{
				t_ch[0] = p->m_path[stlen];
				stlen++;
			}

			strPos++;
			for (size_t i = 0; i < m_Dict.GetDirLen(); i++)
			{
				PMyDict pdis = m_Dict.GetDirDx(i);
				if (strcmp(t_ch, pdis->m_dirChar) == 0)
				{
					t_dx += pdis->m_linek;
					ret = true;
					break;
				}
			}
			if (ret == false)
			{
				return -1;
			}
			if (stlen >= strlen(p->m_path))
			{
				break;
			}

		}
	}


	if (!GetDcPic(x_1, y_1, w_1, h_1, &dpic, &bi))
	{
		return -1;
	}

	char** pic = new char* [h_1];
	for (size_t i = 0; i < h_1; i++)
	{
		pic[i] = new char[w_1];
		memset(pic[i], 0, w_1);
	}

	COLORREF** pp = (COLORREF**)dpic;
	UCHAR R = 0, G = 0, B = 0;
	for (size_t y = 0; y < h_1; y++)
	{
		for (size_t x = 0; x < w_1; x++)
		{
			COLORREF t_coo = pp[y][x];
			R = GetRValue(t_coo);
			G = GetGValue(t_coo);
			B = GetBValue(t_coo);
			ret = false;
			for (size_t k = 0; k < color.GetArrLen(); k++)
			{
				PMyRGB p1 = color.GetDxArr(k);
				if (abs(R - p1->R) <= p1->Rp + t_sim && abs(G - p1->G) <= p1->Gp + t_sim && abs(B - p1->B) <= p1->Bp + t_sim)
				{
					ret = true;
					break;
				}
			}
			if (ret)
			{
				pic[y][x] = 1;
				continue;
			}
			pic[y][x] = 0;
		}
	}

	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pp[i];
	}
	delete[] pp;


	char* t_nstr = 0, * t_nstr1 = 0;



	POINTARR t_point;
	for (size_t dx = 0; dx < str1.GetPathFileLen(); dx++)
	{
		PMyPath p = str1.GetPathFile(dx);

		int stlen = 0;

		if (!t_dx)
		{
			goto endsl;
		}
		stlen = w_1 - t_dx + 1;
		t_dx = 0;
		//0123456
		int stmax = 0;
		int t_dx2 = 0;
		int t_dx = 0, t_dy = 0;

		int chlen = 0;
		OCRTYPEARR ocr_;
		PMyDict t_p = 0;
		int t_xxx = 0;
		while (1)
		{

			int didx = -1;
			char t_ch[MAX_PATH] = { 0 };
			if (p->m_path[stmax] < 0)
			{
				t_ch[0] = p->m_path[stmax];
				stmax++;
				t_ch[1] = p->m_path[stmax];
				stmax++;
			}
			else
			{
				t_ch[0] = p->m_path[stmax];
				stmax++;
			}
			if (stmax >= p->m_len)
			{
				stmax = 0;
				t_xxx = 0;
			}
			ret = false;

			for (size_t j = 0; j < m_Dict.GetDirLen(); j++)
			{
				PMyDict t_p = m_Dict.GetDirDx(j);
				if (strcmp(t_p->m_dirChar, t_ch) == 0)
				{
					t_xxx += t_p->m_linek;
					didx = j;
					ret = true;
					break;
				}
			}
			if (didx < 0)
			{
				ret = false;
				goto endsl;
			}

			if (t_dy >= h_1 - 10)
			{
				break;
			}

			t_p = m_Dict.GetDirDx(didx);
			if (!t_p)
			{
				ret = false;
				goto endsl;
			}



			for (size_t y = chlen; y < h_1 - 10; y++)
			{
				ret = false;
				t_dy++;
				for (size_t x = t_dx2; x < stlen; x++)
				{
					t_dx++;

					int w = t_p->m_linek;
					int t_dx1 = 0;
					for (size_t j = 0; j < w; j++)
					{
						for (size_t k = 0; k < 11; k++)
						{
							if (t_point.GetPos(x + j, y + k))
							{
								continue;
							}

							if (pic[y + k][x + j] != t_p->m_dir[t_dx1] - '0')
							{
								ret = false;
								break;
							}
							t_dx1++;
							ret = true;
						}
						if (!ret)
						{
							break;
						}
					}
					if (ret)
					{
						t_dx2 += w + 1;
						chlen = y;
						ocr_.AddOcr(t_p->m_dirChar, x, y);
						break;
					}

				}
				if (ret)
				{
					break;
				}
			}
			int polen = ocr_.GetLen();
			if (polen >= strPos)
			{
				t_dx += ocr_.GetOcr(0)->x;
				t_dx += t_xxx;



				ret = true;

				if (t_point.GetPos(ocr_.GetOcr(0)->x, ocr_.GetOcr(0)->y))
				{
					ocr_.Clear();
					continue;
				}

				char cc_th[50] = { 0 };
				sprintf(cc_th, "%d,%d,%d", dx, ocr_.GetOcr(0)->x, ocr_.GetOcr(0)->y);
				if (t_nstr == 0)
				{
					int tstrlen = strlen(cc_th) + 1;
					t_nstr = new char[tstrlen];
					memset(t_nstr, 0, tstrlen);
					sprintf(t_nstr, "%s", cc_th);
				}
				else
				{
					int tstrlen = strlen(cc_th) + strlen(t_nstr) + 2;
					t_nstr1 = new char[tstrlen];
					memset(t_nstr1, 0, tstrlen);
					sprintf(t_nstr1, "%s|%s", t_nstr, cc_th);
					delete[] t_nstr;
					t_nstr = t_nstr1;
					t_nstr1 = 0;
				}

				t_point.AddPoint(ocr_.GetOcr(0)->x, ocr_.GetOcr(0)->y, t_xxx + 1);
				t_xxx = 0;
				ocr_.Clear();

			}

		}


	}

endsl:
	t_point.Clear();
	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pic[i];
	}
	delete[] pic;

	if (t_nstr)
	{
		*outstr = t_nstr;
		return 1;
	}

	return -1;
}

long DXBind::Ocr(long x_1, long y_1, long w_1, long h_1, LPCSTR color_format, double sim, LPCSTR* outstr)
{
	if (!::IsWindow(m_hwnd) || !m_Dict.GetDirLen())
	{
		return 0;
	}

	if (!SetXy(&x_1, &y_1, &w_1, &h_1))
	{
		return 0;
	}

	MyRGBARR color = color_format;
	if (color.GetArrLen() == 0 )
	{
		return -1;
	}


	COLORREF t_sim = GetSimLen(sim);//计算相似度
	LPVOID dpic = 0;
	BITMAPINFO bi = { 0 };
	if (!GetDcPic(x_1, y_1, w_1, h_1, &dpic, &bi))
	{
		return -1;
	}
	bool ret = false;
	char** pic = new char* [h_1];
	for (size_t i = 0; i < h_1; i++)
	{
		pic[i] = new char[w_1];
		memset(pic[i], 0, w_1);
	}

	COLORREF** pp = (COLORREF**)dpic;
	UCHAR R = 0, G = 0, B = 0;
	for (size_t y = 0; y < h_1; y++)
	{
		for (size_t x = 0; x < w_1; x++)
		{
			COLORREF t_coo = pp[y][x];
			R = GetRValue(t_coo);
			G = GetGValue(t_coo);
			B = GetBValue(t_coo);
			ret = false;
			for (size_t k = 0; k < color.GetArrLen(); k++)
			{
				PMyRGB p1 = color.GetDxArr(k);
				if (abs(R - p1->R) <= p1->Rp + t_sim && abs(G - p1->G) <= p1->Gp + t_sim && abs(B - p1->B) <= p1->Bp + t_sim)
				{
					ret = true;
					break;
				}
			}
			if (ret)
			{
				pic[y][x] = 1;
				continue;
			}
			pic[y][x] = 0;
		}
	}

	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pp[i];
	}
	delete[] pp;


	int hlen = h_1 / m_Dict.m_size;
	int xlen = 0;

	MyOcrArr  t_Ocr;//Ocr保存类
	for (size_t y = 0; y < h_1 - 1; y++)
	{
		xlen = 0;
		int charlen = 0;
		for (size_t x = 0; x < w_1 - 1; x++)
		{
			if (x < xlen)
			{
				continue;
			}
			for (size_t dx = 0; dx < m_Dict.GetDirLen(); dx++)
			{
				PMyDict pdx = m_Dict.GetDirDx(dx);

				//0123456789
				if ((x + pdx->m_linek > w_1 - 1))
				{
					continue;
				}

				charlen = 0;
				for (size_t w = 0; w < pdx->m_linek; w++)
				{
					for (size_t h = 0; h < 11; h++)
					{
						if (y + h >= h_1)
						{
							ret = true;
							charlen++;
							continue;
						}

						if (pdx->m_dir[charlen] - '0' != pic[y + h][x + w])
						{
							ret = false;
							break;
						}
						
						ret = true;
						charlen++;
					}
					if (!ret)
					{
						break;
					}
				}

				if (!ret)
				{
					continue;
				}
				t_Ocr.AddOcrChar(pdx->m_dirChar, x, y, m_Dict.m_size);

				xlen = x + pdx->m_linek;

				break;

			}
		}
	}


	//endls:

	for (size_t i = 0; i < h_1; i++)
	{
		delete[] pic[i];
	}
	delete[] pic;
	

	if (t_Ocr.GetOcrLen())
	{
		*outstr = t_Ocr.GetOcrStr();
		return 1;
	}
	return 0;
}

