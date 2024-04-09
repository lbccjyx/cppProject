#include "Msg.h"
#include <assert.h>
CMsg::CMsg()
{
	this->Init();  // NOLINT
}

CMsg::~CMsg()
{
	delete[] m_pBuf;
}

bool CMsg::Create(const void* pszBuf, unsigned short usBufLen)
{
    if (!pszBuf)
        return false;
    
	const MSG_HEAD* pHead = (const MSG_HEAD*)pszBuf;

	if ((unsigned short)usBufLen != pHead->usSize)
		return false;

	if (0 == pHead->usType)
		return false;

	if (GetMaxSize() < pHead->usSize)	
		return false;
	
	memcpy_s(m_pBuf, GetMaxSize(), pszBuf, usBufLen);
	return true;
}

bool CMsg::Init(int nMaxSize)
{
	if (m_pBuf == nullptr)
	{
		m_nMaxSize = _MAX_DEFAULT_RAW_MSGSIZE;
		m_pBuf = new char[GetMaxSize()]();
	}
	if(!SetMaxSize(nMaxSize))
		return false;

	std::memset(m_pBuf, 0L, GetMaxSize());
	m_nFrom = 0;
	m_nTo = 0;
	m_FromType = MSG_FROM_NONE;
	return true;
}

MSG_HEAD& CMsg::GetHead() const
{
	assert(GetMaxSize() >= _MIN_MSGSIZE);
	assert(GetBuf() != nullptr);
	MSG_HEAD& head = (MSG_HEAD&)*(MSG_HEAD*)GetBuf();
	return head;
}

bool CMsg::SetMaxSize(const int nReqNewMaxSize)
{
	const auto nOldMaxSize = GetMaxSize();
	const auto nNewMaxSize = std::max((int)_MAX_DEFAULT_RAW_MSGSIZE, nReqNewMaxSize);
	if (nReqNewMaxSize > nNewMaxSize)
		return false;

	if (nOldMaxSize >= nNewMaxSize)
		return true;
	

	//自动扩容会导致外部buf指针时效
	char* pNew = new char[nNewMaxSize]();
	if (m_pBuf != nullptr)
	{
		assert(GetHead().usSize <= nNewMaxSize);
		std::memcpy(pNew, m_pBuf, GetHead().usSize);
		delete[] m_pBuf;
	}

	m_pBuf = pNew;
	m_nMaxSize = nNewMaxSize;

	return true;
}

int CMsg::GetMaxSize(void) const
{
	return m_nMaxSize;
}

char* CMsg::GetBuf(void) const
{
	return m_pBuf;
}
