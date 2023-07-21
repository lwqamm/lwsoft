// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#define isNull(ptr)        	(NULL == (ptr))
#define isNotNull(ptr)        (NULL != (ptr))
//BMP图片的文件头，固定14字节
#define BMP_FILE_HEADER_LENGTH       (14)
//BMP图片的像素位数
#define BMP_8_BIT          (8)
#define BMP_16_BIT         (16)
#define BMP_24_BIT         (24)
#define BMP_32_BIT         (32)
#define LW_VERSION             "1.0005"
/*大写到小写*/
char toUpper_(char* src);//大写到小写
/*小写到大写*/
char _toUpper_(char* src);
BOOL FindStrRightEXS(LPCSTR str0, LPCSTR str11);
//A字符转换U字符
wchar_t* AStrToWstr(LPCSTR DllFile);
//关闭系统
BOOL MySystemShutdown(ULONG type);
//设置当前的电源设置，禁止关闭显示器，禁止关闭硬盘，禁止睡眠，禁止待机
long ClosePowers();
//文件是否存在
int  file_exist(const char* str);
//反向查找文本
DWORD ReverseFind(LPVOID ps, LPVOID ps1);
//获取BOIS制造日期
LONGLONG GetMainBoardInfoByCmd();
//
char* IntToHex(UINT64 aint);
//十六到十
UINT64 __stdcall HexToInt(const char* strhex1);
BOOL HexToBin(const char* str1, char** otr);
//处理事件
void mysleep_bak();
//资源文件和硬盘文件比较
BOOL FreeMyResource(UINT uiResouceName, const char* lpszResourceType, const char* lpszSaveFileName);
//从资源保存文件
BOOL CmpResFile(UINT uiResouceName, const char* lpszResourceType, const char* lpszSaveFileName);


#include "DXBind.h"

#endif //PCH_H
