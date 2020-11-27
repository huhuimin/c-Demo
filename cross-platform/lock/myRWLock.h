/**
* @file myRWLock.h
* @brief 跨平台锁
* @details
* 修改说明：
*
*/

#ifndef _MYRWLOCK_H_
#define _MYRWLOCK_H_

#ifndef  _WIN32
#include <pthread.h>
#else
#include <windows.h>
#endif

// 读写锁
class  CRWLock 
{
public:	
	CRWLock();

	~CRWLock();

	int  AcquireReadLock(void);    //请求读操作锁,请求不成功则阻塞

	int  ReleaseReadLock(void);    //释放读操作锁

	int  AcquireWriteLock(void);   //请求写操作锁,请求不成功则阻塞

	int  ReleaseWriteLock(void);   //释放写操作锁

private:	

#ifdef  _WIN32	
	SRWLOCK m_RWLock;   //读写锁
#else	
	pthread_rwlock_t m_RWLock;
#endif
};


// ***************互斥锁************************
class CLock
{
public:
	CLock();
	~CLock();

	void Lock();	//加锁

	void UnLock();	//释放锁

private:
#ifdef _WIN32
	HANDLE m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif
};

// 自动锁，构造自动加锁，退出作用域自动释放
class CAutoReleaseLock
{
public:
	CAutoReleaseLock(CLock* pLock)
	{
		m_pLock = pLock;
		if (m_pLock)
		{
			m_pLock->Lock();
		}
	}
	~CAutoReleaseLock()
	{
		if (m_pLock)
		{
			m_pLock->UnLock();
		}
	}

private:
	CLock* m_pLock;
};


#endif // !_MYRWLOCK_H_



