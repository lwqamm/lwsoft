// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include <powersetting.h>
#include <	powrprof.h>
#include <io.h>
#include <Pdh.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>
#include <io.h>
#include "dbghelp.h"
#include <windows.h>
#include <winternl.h>
#include <psapi.h>
#include <string>
#include <map>
#include <shlwapi.h>
using namespace std;
#pragma warning(disable:4312)  
#pragma warning(disable:4996)

#pragma comment(lib,"Advapi32.lib")//
#pragma comment(lib,"Shlwapi.lib")
typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName
}MEMORY_INFORMATION_CLASS;

#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "Dbghelp.lib")
// 当使用预编译的头时，需要使用此源文件，编译才能成功。

#pragma warning(disable:4996)

#pragma comment(lib,"PowrProf.lib")
using namespace std;

//提升进程权限
BOOL UpdateProcessPrivilege(HANDLE hProcess) {
	HANDLE hToken;
	TOKEN_PRIVILEGES TokenPrivileges;
	if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
		printf("OpenProcessToken 成功\n");
		LUID destLuid;
		if (LookupPrivilegeValue(NULL, SE_SECURITY_NAME, &destLuid)) {
			printf("LookupPrivilegeValue 成功\n");
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL)) {
				printf("AdjustTokenPrivileges 成功\n");
				return TRUE;
			}
		}
	}
	return FALSE;
}

//文件是否存在
int  file_exist(const char* str)
{

	if (access(str, 0) == NULL)
	{
		return 1;
	}
	return 0;
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
功能：寻找文本
参数：待查找文本
参数：文本
返回值：BOOL
*/
BOOL FindStrRightEXS(LPCSTR str0, LPCSTR str11)
{
	if (DWORD64(str0)<=0x10000|| DWORD64(str11) <= 0x10000)
	{
		return FALSE;
	}
	
	DWORD st1len = strlen(str0);
	DWORD st2len = strlen(str11);
	if (st2len>st1len)
	{
		return FALSE;
	}
	PUCHAR p = (PUCHAR)str0, p1 = (PUCHAR)str11;
	int   plen = 0;
	for (int i = 0; i < st1len; i++)
	{
		for (int j = 0; j < st2len; j++)
		{
			if (p[i + j] != p1[j])
			{
				plen = 0;
				break;
			}
			plen++;
		}
		if (plen == st2len)
		{
			//plen = i;
			break;
		}
		plen = 0;
	}


	if (plen > 0)
	{
		return TRUE;
	}
	return FALSE;
}

wchar_t* AStrToWstr(LPCSTR DllFile)
{
	if (!DllFile )
	{
		return 0;
	}
	//2、获取该字符串的长度
	int str_len = strlen(DllFile);
	//3、通过设置转换函数第六个参数为0，获取到该字符串转换成宽字符数时需要的宽字符数（这次只要宽字节数故第5个参数可以设置为NULL）
	DWORD w_strlen = MultiByteToWideChar(CP_ACP, 0, DllFile, -1, NULL, 0);
	if (!w_strlen)
	{
		return 0;
	}
	//4、开辟内存空间，用于存储转换成功后的宽字符串，开辟空间为上面获取的宽字符数
	wchar_t* dBuf = new wchar_t[w_strlen];
	memset(dBuf, 0, w_strlen);
	//5、转换宽字符串，本次为全部转换。返回值为本次写入的宽字符数
	int nRet = MultiByteToWideChar(CP_ACP, 0, DllFile, str_len, dBuf, w_strlen);
	if (!nRet)
	{
		return 0;
	}
	dBuf[nRet] = '\0';
	return  dBuf;
}

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

BOOL MySystemShutdown(ULONG type )
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process. 

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return(FALSE);

	// Get the LUID for the shutdown privilege. 

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get the shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	// Shut down the system and force all applications to close. EWX_LOGOFF
	if (type == 0)
	{
		if (!ExitWindowsEx(EWX_LOGOFF | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;
	}

	if (type==1)
	{
		if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;
	}
	if (type == 2)
	{
		if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;
	}

	//shutdown was successful
	return TRUE;
}

long ClosePowers()
{
	//UINT id = 100; return CString(vResult.bstrVal);
	////create
	//PPOWER_POLICY policy = new POWER_POLICY();
	////read
	//ReadPwrScheme(0, policy);
	////write
	//policy->user.IdleTimeoutAc = 0; //待机
	//policy->user.IdleTimeoutDc = 0;
	//policy->user.SpindownTimeoutAc = 0; //关闭硬盘
	//policy->user.SpindownTimeoutDc = 0;
	//policy->user.VideoTimeoutAc = 0; //关闭显示器
	//policy->user.VideoTimeoutDc = 0;
	//policy->mach.DozeS4TimeoutAc = 0; //休眠
	//policy->mach.DozeS4TimeoutDc = 0;

	//BOOLEAN result = WritePwrScheme(&id, L"新计划", L"新计划1", policy);
	//SetActivePwrScheme(100, 0, 0);
	//return result;
		//原文链接：https ://blog.csdn.net/zhouguangcai8/article/details/41119537
		// 获取当前活动的电源计划
	GUID* id = 0;
	PowerGetActiveScheme(NULL, &id);

	// 设置显示器从不关闭
	PowerWriteACValueIndex(NULL, id, &GUID_VIDEO_SUBGROUP, &GUID_VIDEO_POWERDOWN_TIMEOUT, 0);


	// 使设置生效
return	PowerSetActiveScheme(NULL, id);

		//原文链接：https ://blog.csdn.net/zhouguangcai8/article/details/41119537
}

//反向查找文本
DWORD ReverseFind(LPVOID ps, LPVOID ps1)
{
	if (DWORD64(ps) <= 0x10000 || DWORD64(ps1) <= 0x10000)
	{
		return -1;
	}
	int len = strlen((LPCSTR)ps);
	int lenbak = len;
	int len1 = strlen((LPCSTR)ps1);
	if (len1 > len)
	{
		return -1;
	}
	len = len - len1 + 1;
	PUCHAR p = (PUCHAR)ps;
	PUCHAR p1 = (PUCHAR)ps1;

	int Edn = 0;
	for (size_t i = 0; i < len; i++)
	{
		Edn = 0;
		for (size_t j = 0; j < len1; j++)
		{
			if (p[len - 1 - i + j] != p1[j])
			{
				Edn = 0;
				break;
			}

			Edn++;
		}
		//0123456789
		//012
		if (Edn >= len1)
		{
			Edn = i;
			break;
		}
	}
	if (!Edn)
	{
		return  -1;
	}
	//Edn = Edn;
	lenbak = len - (Edn + 1);
	return lenbak;
}

typedef struct _Mycpuxx
{
public:
	_Mycpuxx(){}
	~_Mycpuxx() { CloseCPUQuery(); }
	void InitStart(bool& res)
	{
		PDH_STATUS status = PdhOpenQuery(NULL, NULL, &cpuQuery);
		if (status == ERROR_SUCCESS) {
			status = PdhAddCounterA(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);

			if (status == ERROR_SUCCESS) {
				status = PdhCollectQueryData(cpuQuery);
				if (status == ERROR_SUCCESS) {
					res = true;
				}
			}
		}
	}

	double GetCurrentCpuValue()
	{
		bool flag = false;
		InitStart(flag);
		double resValue = 0;
		Sleep(100);
		PDH_FMT_COUNTERVALUE counterVal;

		PDH_STATUS status = PdhCollectQueryData(&cpuQuery);
		if (status == ERROR_SUCCESS) {

			status = PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
			if (status == ERROR_SUCCESS) {
				resValue = counterVal.doubleValue;
			}
		}
		return resValue;
	}
	void CloseCPUQuery()
	{
		PdhRemoveCounter(cpuTotal);
		PdhCloseQuery(cpuQuery);
	}
private:
	PDH_HQUERY cpuQuery = 0;
	PDH_HCOUNTER cpuTotal = 0;
}Mycpuxx,*PMycpuxx;


//原文链接：https ://blog.csdn.net/qq_44606630/article/details/127880453

LONGLONG GetMainBoardInfoByCmd()
{
	char* lpszBaseBoard = NULL;
	const long COMMAND_SIZE = 1020; // Command line output buffer
	const DWORD WAIT_TIME = 500; // INFINITE

	// The command to get mainboard serial number
	TCHAR szFetCmd[] = ("wmic bios get releasedate");

	// Pre- information of mainboard serial number
	const std::string strEnSearch = " ";

	BOOL fReturnCode = FALSE;
	HANDLE hReadPipe = NULL;  // Pipeline for READ
	HANDLE hWritePipe = NULL; // Pipeline for WRITE
	PROCESS_INFORMATION pi;   // Process information
	STARTUPINFO			si;   // Control-command window info
	SECURITY_ATTRIBUTES sa;   // Security attributes

	char szBuffer[COMMAND_SIZE + 1] = { 0 }; // Command line output buffer
	std::string strBuffer;
	DWORD count = 0;
	size_t pos = 0;
	size_t i = 0;
	size_t j = 0;

	lpszBaseBoard = (char*)malloc((COMMAND_SIZE + 1) * sizeof(char));
	memset(lpszBaseBoard, 0x00, (COMMAND_SIZE + 1) * sizeof(char));

	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	memset(&sa, 0, sizeof(sa));

	pi.hProcess = NULL;
	pi.hThread = NULL;
	si.cb = sizeof(STARTUPINFO);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// Step 1: Create pipeline
	fReturnCode = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!fReturnCode)
	{
		goto EXIT;
	}

	// Step 2: Set command line window to be specific READ / WRITE pipeline
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; // hide command line window
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	// Step 3: Create process to get command line handle
	fReturnCode = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (!fReturnCode)
	{
		goto EXIT;
	}

	// Step 4: Get return back data
	WaitForSingleObject(pi.hProcess, WAIT_TIME);
	fReturnCode = ReadFile(hReadPipe, szBuffer, COMMAND_SIZE, &count, 0);
	if (!fReturnCode)
	{
		goto EXIT;
	}

	// Step 5: Search for mainboard serial number
	fReturnCode = FALSE;
	strBuffer = szBuffer;
	pos = strBuffer.find(strEnSearch);

	if (pos < 0) // NOT FOUND
	{
		goto EXIT;
	}
	else
	{
		strBuffer = strBuffer.substr(pos + strEnSearch.length());
	}

	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());

	// Get ride of <space>, \r, \n
	j = 0;
	for (i = 0; i < strlen(szBuffer); i++)
	{
		if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r')
		{
			lpszBaseBoard[j] = szBuffer[i];
			j++;
		}
	}

	fReturnCode = TRUE;

EXIT:
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (lpszBaseBoard)
	{
		lpszBaseBoard[8] = '\0';
	}
	LONGLONG rett = StrToInt(lpszBaseBoard);
	free(lpszBaseBoard);

	return rett;
}


/*
功能:十进制到十六进制过程函数
*/
char hexUnit(unsigned char unit)
{
	if (0 <= unit && unit <= 9)
		return unit + '0';
	else if (10 <= unit && unit <= 15)
		return unit - 10 + 'A';

	return '0';
}

/*
功能:十进制到十六进制字符串
参数:十进制整数
返回：十六进制字符串
*/
char* IntToHex(UINT64 aint)
{
	char hex[17] = { 0 };
	UCHAR sth = 0;

	sth = hexUnit((aint & 0xF000000000000000) >> 56);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF00000000000000) >> 52);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF0000000000000) >> 48);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF000000000000) >> 44);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF00000000000) >> 40);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF000000000) >> 36);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF00000000) >> 32);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0xF0000000) >> 28);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x0F000000) >> 24);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x00F00000) >> 20);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x000F0000) >> 16);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x0000F000) >> 12);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x00000F00) >> 8);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x000000F0) >> 4);
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	sth = hexUnit((aint & 0x0000000F));
	if (sth > '0')
	{
		hex[strlen(hex)] = sth;
	}
	int len = strlen(hex) + 1;
	char* oustr = new char[len];
	memset(oustr, 0, len);
	sprintf(oustr, "%s", hex);
	return oustr;
}

#if _WIN64
#else
void initCpu(DWORD veax, PMycpu P)
{
	__asm
	{
		mov eax, veax
		mov edi, P
		cpuid
		mov[edi], eax
		mov[edi + 4], ebx
		mov[edi + 8], ecx
		mov[edi + 12], edx
	}
}

#endif


/*功能：十六进制到二进制无限长
参数1：十六进制文本
参数2：返回的二进制文本
*/
BOOL HexToBin(const char* str1, char** otr)
{
	if (isNull(str1) || isNull(otr))
	{
		return FALSE;
	}
	int len = strlen(str1);
	if (!len)
	{
		return FALSE;
	}
	char* str = new char[len + 1];
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
	char* t_ch2 = new char[len * 4 + 1];
	*otr = t_ch2;
	memset(t_ch2, 0, len * 4 + 1);
	for (size_t i = 0; i < len; i++)
	{
		int syew = 0;
		if ((p[i] >= '0' && p[i] <= '9'))
		{
			syew = p[i] - 48;
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

void mysleep_bak()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, 1) != 0)
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
}

BOOL IsWow64ProcessEx(HANDLE hProcess)
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

#define X64_End_with_CS(_cs) \
    { \
    EMIT(0xE8) EMIT(0) EMIT(0) EMIT(0) EMIT(0)                                 /*  call   $+5                   */ \
    EMIT(0xC7) EMIT(0x44) EMIT(0x24) EMIT(4) EMIT(_cs) EMIT(0) EMIT(0) EMIT(0) /*  mov    dword [rsp + 4], _cs  */ \
    EMIT(0x83) EMIT(4) EMIT(0x24) EMIT(0xD)                                    /*  add    dword [rsp], 0xD      */ \
    EMIT(0xCB)                                                                 /*  retf                         */ \
    }

string UnicodeToANSI(const wstring str)
{
	char* pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

BOOL DosPathToNtPath(const LPSTR pszDosPath, LPSTR pszNtPath)
{
	CHAR           szDriveStr[500];
	CHAR           szDrive[3];
	CHAR           szDevName[100];
	INT             cchDevName;
	INT             i;

	//检查参数  
	if (!pszDosPath || !pszNtPath)
		return FALSE;

	//获取本地磁盘字符串  
	if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
	{
		for (i = 0; szDriveStr[i]; i += 4)
		{
			if (!lstrcmpi(&(szDriveStr[i]), "A:\\") || !lstrcmpi(&(szDriveStr[i]), "B:\\"))
				continue;

			szDrive[0] = szDriveStr[i];
			szDrive[1] = szDriveStr[i + 1];
			szDrive[2] = '\0';
			if (!QueryDosDevice(szDrive, szDevName, 100))//查询 Dos 设备名  
				return FALSE;

			cchDevName = lstrlen(szDevName);
			if (strnicmp(pszDosPath, szDevName, cchDevName) == 0)//命中  
			{
				lstrcpy(pszNtPath, szDrive);//复制驱动器  
				lstrcat(pszNtPath, pszDosPath + cchDevName);//复制路径  

				return TRUE;
			}
		}
	}

	lstrcpy(pszNtPath, pszDosPath);

	return FALSE;
}

/**
* 提升当前进程权限函数("SeDebugPrivilege"读、写控制权限)
* @param void
* @return TRUE-成功；FALSE-失败
*/
BOOL EnableDebugPriv()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	LUID Luid;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = Luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	return TRUE;
}

/*
功能：资源文件和硬盘文件比较
参数1：资源ID
参数2：资源类型
参数3：硬盘文件名全路径
*/
BOOL CmpResFile(UINT uiResouceName, const char* lpszResourceType, const char* lpszSaveFileName)
{
	if (!uiResouceName || !lpszResourceType || !lpszSaveFileName)
	{
		return FALSE;
	}
	HRSRC hRsrc = ::FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	//LPTSTR szBuffer = new TCHAR[1024];//这里是定义缓冲区大小

	if (hRsrc == NULL)
	{
		//FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize)
	{
		//FreeRes_ShowError("SizeofResource");
		return FALSE;
	}

	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		//FreeRes_ShowError("LoadResource");
		return FALSE;
	}

	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		//FreeRes_ShowError("LockResource");
		return FALSE;
	}
	HANDLE hFile = CreateFile(lpszSaveFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
	{
		return FALSE;
	}
	DWORD fileSize = GetFileSize(hFile, NULL);    //获得文件大小的低两字节
	char* fileBuff = new char[fileSize];    //创建缓冲区
	DWORD realRead = 0;
	BOOL ret = false;
	ret = ReadFile(hFile, fileBuff, fileSize, &realRead, NULL);    //拷贝文件的内容给缓冲区fileBuff
	CloseHandle(hFile);
	if (!ret)
	{
		delete[] fileBuff;
		return FALSE;
	}
	if (fileSize != dwSize)
	{
		delete[] fileBuff;
		return FALSE;
	}

	PUCHAR p = (PUCHAR)fileBuff, p1 = (PUCHAR)lpVoid;
	for (size_t i = 0; i < dwSize; i++)
	{
		if (p[i] != p1[i])
		{
			delete[] fileBuff;
			return FALSE;
		}
	}
	delete[] fileBuff;
	return TRUE;
}
/*
功能：从资源保存文件
参数1：资源ID
参数2：资源类型
参数3：保存文件名全路径
*/
BOOL FreeMyResource(UINT uiResouceName, const char* lpszResourceType, const char* lpszSaveFileName)
{
	HMODULE DLL = 0;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, LW_VERSION, &DLL);
	HRSRC hRsrc = ::FindResource(DLL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	//LPTSTR szBuffer = new TCHAR[1024];//这里是定义缓冲区大小

	if (hRsrc == NULL)
	{
		//FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(DLL, hRsrc);
	if (0 >= dwSize)
	{
		//FreeRes_ShowError("SizeofResource");
		return FALSE;
	}

	HGLOBAL hGlobal = ::LoadResource(DLL, hRsrc);
	if (NULL == hGlobal)
	{
		//FreeRes_ShowError("LoadResource");
		return FALSE;
	}

	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		//FreeRes_ShowError("LockResource");
		return FALSE;
	}


	FILE* fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (NULL == fp)
	{
		//FreeRes_ShowError("LockResource");
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);

	return TRUE;
}

