#pragma once


#pragma pack(1)
typedef struct _Mycpu
{
	//´æ4¸ö¼Ä´æÆ÷Öµ
	DWORD  eax = 0;
	DWORD  ebx = 0;
	DWORD  ecx = 0;
	DWORD  edx = 0;
}Mycpu, * PMycpu, * LPMycpu;


//typedef  void( *stmypoc)();

#pragma pack(1)
extern PMSG t_msg ;
extern LPVOID g_peek ;
 extern BOOL procmsg();

#if _WIN64
extern "C" void initCpu(DWORD veax, PMycpu P);
extern "C" void   myProc1(PMSG* p,LPVOID mpj,LPVOID allc);
extern "C" __declspec() void  __stdcall myProc();

#else
void initCpu(DWORD veax, PMycpu P);


#endif
