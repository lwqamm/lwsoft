// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
#pragma warning(disable:4996)


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