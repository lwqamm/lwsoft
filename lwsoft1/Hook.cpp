#include <windows.h>
#include "Hook.h"
#include "DXBind.h"
#pragma warning(disable:4996)
#pragma comment(lib,"User32.lib")

#define   PAGE_EXECUTE_FLAGES \
 (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)

BOOL Hook::UMS_IsExecutableAddress(LPVOID VirtualAddress)
{
	BOOL IsOk = FALSE;
	MEMORY_BASIC_INFORMATION MemoryBasicInfo = { 0 };


	VirtualQuery(VirtualAddress, &MemoryBasicInfo, sizeof(MEMORY_BASIC_INFORMATION));



	if ((MemoryBasicInfo.State == MEM_COMMIT &&
		(MemoryBasicInfo.Protect & PAGE_EXECUTE_FLAGES)))
	{
		IsOk = TRUE;
	}
	return IsOk;
}

void Hook::UnHook()
{
	if (m_hook)
	{
		DWORD utl = 0;
		VirtualProtect(m_addrs, sizeof(m_bak), PAGE_EXECUTE_READWRITE, &utl);
		memcpy(m_addrs, m_bak, sizeof(m_bak));
		VirtualProtect(m_addrs, sizeof(m_bak), utl, &utl);
		m_hook = FALSE;
	}

	return;
}



BOOL Hook::SetHook(LPVOID myhook, LPVOID proc)
{
	if (!UMS_IsExecutableAddress(myhook)|| !UMS_IsExecutableAddress(proc))
	{
		return FALSE;
	}
	DWORD utl = 0;
	if (!VirtualProtect(myhook, sizeof(m_bak), PAGE_EXECUTE_READWRITE, &utl))
	{
		//int eroo = GetLastError();
		MessageBox(0, "–ﬁ∏ƒƒ⁄¥Ê Ù–‘ ß∞‹", 0, 0);
		return FALSE;
	}
	memcpy(m_bak, myhook, sizeof(m_bak));
	int addr = (DWORD64)proc - (DWORD64)myhook - 5;
	memcpy(m_hookby + 1, &addr, sizeof(int));
	BOOL ret=(BOOL)memcpy(myhook, m_hookby, sizeof(m_hookby));
	VirtualProtect(myhook, sizeof(m_hookby), utl, &utl);
	m_hook = ret;
	m_addrs = myhook;
	return ret;
}
