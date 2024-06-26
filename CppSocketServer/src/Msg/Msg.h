#pragma once
#include <vector>
#include <basetsd.h>
#include <memory>
#include <string>


#ifndef NO_COPY
#	define NO_COPY(T)                         \
		T(const T&)		 = delete;             \
		const T& operator=(const T&) = delete; \
                                               \
	public:
#endif
const unsigned int _MAX_DEFAULT_RAW_MSGSIZE = 1024;	 //原始消息默认缓冲
const int _MIN_MSGSIZE			   = 4; 
#	define PURE_VIRTUAL_0 = 0;
typedef unsigned int CID;
using USHORT = unsigned short;
using PBYTE = unsigned char*;

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
	virtual IMsg* Clone() const PURE_VIRTUAL_0;
	virtual void SetFrom(CID val) PURE_VIRTUAL_0;
	virtual void SetTo(CID val) PURE_VIRTUAL_0;

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
	virtual IMsg* Clone() const;
	virtual void SetFrom(CID val);
	virtual void SetTo(CID val);
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

struct MSG_INFO
{
	USHORT usMsgSize;
	USHORT usMsgType;

	unsigned char ucAction;
	PBYTE GetBufAddr()
	{
		// 首地址 + 头部大小 sizeof(MSG_INFO) = 6 * 1 byte
		return (PBYTE)this + sizeof(MSG_INFO);
	};
};
struct OrderQuery
{
	INT64 idUser;
	int nAnther;
};
struct ProtoReq
{
	char strName[50];
};
struct MSGCMD
{
	union
	{
		void* m_pPoint;
		OrderQuery* m_pOrderQuery;
		ProtoReq* m_pProtoReq;
	};
	MSGCMD(void* pBuf = NULL) : m_pPoint((void*)pBuf) {}
};
