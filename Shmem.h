#pragma once
class Objectlicense
{
public:
	Objectlicense() { objecthandle = NULL; }
	~Objectlicense() { CloseHandle(objecthandle); }
	BOOL Create(const char* str)
	{
		char ch[256] = { 0 };
		memcpy(ch, str, strlen(str));
		char ch1[] = "Event";
		memcpy(ch + strlen(ch), ch1, strlen(ch1));
		objecthandle = CreateEventA(NULL, FALSE, TRUE, ch);
		if (!objecthandle)
		{
			return FALSE;
		}
		return TRUE;
	}
	BOOL ConnEct(const char* str)
	{
		char ch[256] = { 0 };
		memcpy(ch, str, strlen(str));
		char ch1[] = "Event";
		memcpy(ch + strlen(ch), ch1, strlen(ch1));
		objecthandle = OpenEventA(EVENT_ALL_ACCESS, FALSE, ch);
		if (!objecthandle)
		{
			return FALSE;
		}
		return TRUE;
	}
	//����
	void GetInto() { WaitForSingleObject(objecthandle, -1); }
	//�˳�
	void SignOut() { SetEvent(objecthandle); }

	//�ָ�
	void Reset() { ResetEvent(objecthandle); }
private:
	HANDLE objecthandle;
};

class Shmem
{
public:
	Shmem();
	~Shmem();
	LPVOID Create(const char* PortName, const char* ControllerName, UINT64 DataSize);
	BOOL   UnBuffer();
	BOOL ConnEct(const char* PortName, const char* ControllerName, UINT64 DataSize);
	void WriteIn(LPVOID p, DWORD si);
	void Read(DWORD si, LPVOID* utp);
	// ����
	LPVOID GetBuffer() const { return  DataSpace_port; }
private:
	HANDLE DataSpace;
	LPVOID DataSpace_port = NULL;
	Objectlicense m_Object;
};

typedef struct _HookData
{
public:
	DWORD    m_hwnd = 0;               //���ھ��
	DWORD   m_pid = 0;                //����Pid
}HookData,*PHookData,*LPHookData;

