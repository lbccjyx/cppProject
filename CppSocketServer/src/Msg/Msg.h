#pragma once
#include <vector>
#include <basetsd.h>
#include <memory>


#ifndef NO_COPY
#	define NO_COPY(T)                         \
		T(const T&)		 = delete;             \
		const T& operator=(const T&) = delete; \
                                               \
	public:
#endif
const unsigned int _MAX_DEFAULT_RAW_MSGSIZE = 1024;	 //原始消息默认缓冲
const int _MIN_MSGSIZE			   = 4;
struct MSG_HEAD
{
	unsigned short usSize;
	unsigned short usType;
};
enum MSG_FROM_SVR : int
{
	MSG_FROM_NONE,
	MSG_FROM_SVRNET,
};

enum Type : int
{
	TO_MULTI_CLIENT,
	TO_ALL_CLIENT,

	TO_MULTI_GS,
	TO_ALL_GS,
	TO_MULTI_BS,
};

class  CTo
{
public:
protected:
	using List = std::vector<INT64>;

	Type m_type;
	List m_lst;
};


class IMsg
{
public:
	NO_COPY(IMsg);

protected:
	virtual ~IMsg() = default;

protected:
	IMsg() = default;

protected:
	std::unique_ptr<CTo> m_to;
};

class CMsg : public IMsg
{
public:
	NO_COPY(CMsg);
	CMsg();
	virtual ~CMsg();
public:
	virtual bool Create(const void* pszBuf, unsigned short usBufLen);
	virtual int GetMaxSize(void) const;
	virtual char* GetBuf(void) const;

protected:
	bool Init(int nMaxSize = 0);

private:
	MSG_HEAD& GetHead() const;
	bool	  SetMaxSize(int n); 

	char* m_pBuf = nullptr;
	int			 m_nFrom = 0;
	int			 m_nTo = 0;
	int			 m_nMaxSize = 0;
	MSG_FROM_SVR m_FromType = MSG_FROM_NONE;
};