
#include <windows.h>
#include "Shmem.h"

Shmem::Shmem()
{
	DataSpace = NULL;
}

Shmem::~Shmem()
{
	//UnBuffer();
}

LPVOID Shmem::Create(const char* PortName, const char* ControllerName, UINT64 DataSize)
{
	if (m_Object.Create(ControllerName) == FALSE)
	{
		return FALSE;
	}
	DataSpace = CreateFileMappingA(GetCurrentProcess(), 0, PAGE_READWRITE, 0, DataSize, PortName);
	if (DataSpace == 0)
	{
		return FALSE;
	}
	DataSpace_port = MapViewOfFile(DataSpace, FILE_MAP_ALL_ACCESS, 0, 0, DataSize);
	if (DataSpace_port == 0)
	{
		return 0;
	}
	return DataSpace_port;
}

BOOL Shmem::UnBuffer()
{
	if (!DataSpace_port)
	{
		return FALSE;
	}
	
	BOOL ret= ::UnmapViewOfFile(DataSpace_port);
	CloseHandle(DataSpace);
	return ret;
}

BOOL Shmem::ConnEct(const char* PortName, const char* ControllerName, UINT64 DataSize)
{
	if (m_Object.ConnEct(ControllerName) == FALSE)
	{
		return FALSE;
	}
	DataSpace = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, PortName);
	if (DataSpace == 0)
	{
		return FALSE;
	}
	DataSpace_port = MapViewOfFile(DataSpace, FILE_MAP_ALL_ACCESS, 0, 0, DataSize);
	if (DataSpace_port == 0)
	{
		return FALSE;
	}
	return TRUE;
}

void Shmem::WriteIn(LPVOID p, DWORD si)
{
	m_Object.GetInto();
	memcpy(DataSpace_port, p, si);
	m_Object.SignOut();
}

void Shmem::Read(DWORD si, LPVOID* utp)
{
	m_Object.GetInto();
	memcpy(utp, DataSpace_port, si);
	m_Object.SignOut();
}