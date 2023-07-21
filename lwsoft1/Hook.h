#pragma once
class Hook
{
public:
	Hook(){}
	~Hook() { UnHook(); }
	//判断内存是否有效
	BOOL UMS_IsExecutableAddress(LPVOID VirtualAddress);
	//卸载HOOK
	void UnHook();
	//安装HOOK
	BOOL SetHook(LPVOID myhook,LPVOID proc);
private:
	BYTE m_bak[20] = { 0 };
	BYTE m_hookby[20] = {0xE9,0x90 };
	BOOL m_hook = FALSE;
	LPVOID m_addrs = 0;
};

