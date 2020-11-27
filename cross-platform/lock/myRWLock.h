/**
* @file myRWLock.h
* @brief ��ƽ̨��
* @details
* �޸�˵����
*
*/

#ifndef _MYRWLOCK_H_
#define _MYRWLOCK_H_

#ifndef  _WIN32
#include <pthread.h>
#else
#include <windows.h>
#endif

// ��д��
class  CRWLock 
{
public:	
	CRWLock();

	~CRWLock();

	int  AcquireReadLock(void);    //�����������,���󲻳ɹ�������

	int  ReleaseReadLock(void);    //�ͷŶ�������

	int  AcquireWriteLock(void);   //����д������,���󲻳ɹ�������

	int  ReleaseWriteLock(void);   //�ͷ�д������

private:	

#ifdef  _WIN32	
	SRWLOCK m_RWLock;   //��д��
#else	
	pthread_rwlock_t m_RWLock;
#endif
};


// ***************������************************
class CLock
{
public:
	CLock();
	~CLock();

	void Lock();	//����

	void UnLock();	//�ͷ���

private:
#ifdef _WIN32
	HANDLE m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif
};

// �Զ����������Զ��������˳��������Զ��ͷ�
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



