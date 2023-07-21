
#include "LwMutexlock.h"
#include <windows.h>
TsMutex::TsMutex(char* pszEventName)
{
	//InitializeCriticalSection(&m_mutex);
	hEvent = OpenEventA(EVENT_ALL_ACCESS, false, pszEventName);
	if (hEvent == NULL)
	{
		hEvent = CreateEventA(NULL, FALSE, FALSE, pszEventName);
		::SetEvent(hEvent);
	}
}

TsMutex::~TsMutex()
{
	//DeleteCriticalSection(&m_mutex);
	CloseHandle(hEvent);
}

void TsMutex::lock()
{
	//::WaitForSingleObject(hEvent,INFINITE);
	::WaitForSingleObject(hEvent, 10000);
	//EnterCriticalSection(&m_mutex);
}

void TsMutex::unlock()
{
	::SetEvent(hEvent);
	//LeaveCriticalSection(&m_mutex);
}

LwMutexlock::LwMutexlock(TsMutex* ptcmutex)
{
	m_ptcmutex = ptcmutex;
	m_ptcmutex->lock();
}

LwMutexlock::~LwMutexlock()
{
	m_ptcmutex->unlock();
}
