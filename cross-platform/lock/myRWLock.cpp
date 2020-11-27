#include "myRWLock.h"

CRWLock::CRWLock()
{ 
#ifdef _WIN32	
	InitializeSRWLock(&m_RWLock);

#else	
	pthread_rwlock_init(&m_RWLock, NULL);
#endif 
}
CRWLock::~CRWLock() 
{ 
#ifdef _WIN32	
	// 
#else	
	pthread_rwlock_destroy(&m_RWLock);
#endif 
} 



int CRWLock::AcquireReadLock()
{ 
#ifdef _WIN32	
	AcquireSRWLockShared(&m_RWLock);
	return 0; 
#else	
	return pthread_rwlock_rdlock(&m_RWLock);
#endif 
}  
int CRWLock::ReleaseReadLock()
{ 
	int result = true;
#ifdef _WIN32	
	ReleaseSRWLockShared(&m_RWLock);
	return 0;
#else		
	return pthread_rwlock_unlock(&m_RWLock); 
#endif 
}  
int CRWLock::AcquireWriteLock()
{ 
#ifdef _WIN32
	AcquireSRWLockExclusive(&m_RWLock);
	return 0;
#else
	return pthread_rwlock_wrlock(&m_RWLock);
#endif 
} 

int CRWLock::ReleaseWriteLock()
{ 
#ifdef _WIN32	
	ReleaseSRWLockExclusive(&m_RWLock);
	return 0;
#else
	return  pthread_rwlock_unlock(&m_RWLock);
#endif 
}



// »¥³âËø
CLock::CLock()
{
#ifdef _WIN32
	m_mutex = CreateMutex(NULL, false, NULL);
#else
	pthread_mutex_init(&m_mutex, NULL);
#endif
}

CLock::~CLock()
{
#ifdef _WIN32
	CloseHandle(m_mutex);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

void CLock::Lock()
{
#ifdef _WIN32
	DWORD dw = WaitForSingleObject(m_mutex, INFINITE);
#else
	pthread_mutex_lock(&m_mutex);
#endif
}

void CLock::UnLock()
{
#ifdef _WIN32
	ReleaseMutex(m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}