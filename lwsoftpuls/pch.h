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
UINT64 __stdcall HexToInt(const char* strhex1);
/*大写到小写*/
char toUpper_(char* src);//大写到小写
/*小写到大写*/
char _toUpper_(char* src);//大写到小写

#endif //PCH_H
