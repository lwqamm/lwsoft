#pragma once
class Hook
{
public:
	Hook(){}
	~Hook() { UnHook(); }
	//�ж��ڴ��Ƿ���Ч
	BOOL UMS_IsExecutableAddress(LPVOID VirtualAddress);
	//ж��HOOK
	void UnHook();
	//��װHOOK
	BOOL SetHook(LPVOID myhook,LPVOID proc);
private:
	BYTE m_bak[20] = { 0 };
	BYTE m_hookby[20] = {0xE9,0x90 };
	BOOL m_hook = FALSE;
	LPVOID m_addrs = 0;
};

