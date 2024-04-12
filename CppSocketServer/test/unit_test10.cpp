// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include <queue>
#include "Msg/Msg.h"
#include "SingletonMode/Singleton.h"
BOOST_AUTO_TEST_SUITE(tests_suit)

enum MODULE_ERR : int
{
	MODERR_SUC = 0,
	MODERR_FAIL = 1,
};
class CUser2
{
};
class ICmdHandle
{
public:
	virtual ~ICmdHandle() = default;

	virtual void Process(void* pObj, const CMsg& m) = 0;
};

template <typename PacketType>
class UserOpcmdHandle : public ICmdHandle
{
	//���� CUser2& �� PacketType& �������������� MODULE_ERR ���͵ĺ���ָ������
	using Callback = std::function<MODULE_ERR(CUser2&, PacketType&)>;
public:
	UserOpcmdHandle(Callback cb, bool bCommRet = false) : _cb(std::move(cb)) , _bCommRet(bCommRet) {}

	virtual void Process(void* pObj,const CMsg& m) override
	{
		CUser2* pUser = static_cast<CUser2*>(pObj);
		assert(pUser);

		const void* pMsg = m.GetBuf();
		MSG_INFO* pInfo = (MSG_INFO*)pMsg;
		MSGCMD rPoint(pInfo->GetBufAddr());
		PacketType* pProtoMsg = rPoint.m_pProtoReq;

		// ����һ������ָ��cb��������pUser �� pProtoMsg����������ֵ�������� e
		MODULE_ERR e = std::invoke(_cb, *pUser, *pProtoMsg);
		if (_bCommRet)
		{
			// ͨ��proto���ͷ���ֵ
			std::cout << "����������ֵ��: "<< e << std::endl;
		}
	}
private:
	Callback _cb;
	bool	 _bCommRet = false;
};

class  COpcmdsDispath
{
public:
	void Register(int code, ICmdHandle* op) 
	{
		assert(op);
		assert(_handlers.find(code) == _handlers.end());
		_handlers[code] = op;
	};
	void Dispatch(void* pObj, const CMsg& rMsg) 
	{
		const void* pMsg = rMsg.GetBuf();
		const MSG_HEAD* pHead = (const MSG_HEAD*)pMsg;
		// ͨ��pHead->usType �ҵ�֮ǰע���nType��Ӧ����
		const auto e = pHead->usType;

		auto* op = _handlers[e];
		assert(op);
		// ����ָ��ICmdHandle ��̬��������Process
		op->Process(pObj,rMsg);
	};

	~COpcmdsDispath() { this->Clear(); };

protected:
	void Clear()
	{
		_handlers.clear();
	};

private:
	std::unordered_map<int, ICmdHandle*> _handlers;
};

#define EntityOpcmdsDispath (*TSingleton<COpcmdsDispath>::InstanceGet())

#define REG_ENTITYCMD_RET(nType, packetType, ...)                     \
	EntityOpcmdsDispath.Register( \
		nType,                                                         \
		new UserOpcmdHandle<packetType>(std::bind(__VA_ARGS__, std::placeholders::_1, std::placeholders::_2), true))

static MODULE_ERR funcTestCallBack(CUser2&, ProtoReq& Req)
{
	std::cout << "funcTestCallBack �յ�������� "<< Req.strName << std::endl;
	return MODERR_SUC;
}

BOOST_AUTO_TEST_CASE(my_test38)
{
	std::cout << "\n\n test38 ע�ắ�� �������� ���к��� ���ͷ���\n";
	// ע�ắ��
	std::cout << "ע�ắ��һ������������1 �ĺ���, ����ProtoReq��Ϣ" << std::endl;
	REG_ENTITYCMD_RET(1, ProtoReq, &funcTestCallBack);

	// �������
	char msgBuf[1024] = { 0 };
	MSG_INFO* pHead = (MSG_INFO*)msgBuf;
	ProtoReq* pBody = (ProtoReq*)pHead->GetBufAddr();
	pHead->usMsgSize = sizeof(*pHead) + sizeof(*pBody);
	// ��Ӧע��ĺ���
	pHead->usMsgType = 1;
	pHead->ucAction = 0;
	std::cout << "��������������: " << pHead->usMsgType << std::endl;
	strcpy(pBody->strName ,"hello world");
	std::cout << "�������������: " << pBody->strName << std::endl;
	CMsg msg;
	msg.Create(msgBuf, pHead->usMsgSize);

	// ֱ�Ӻ��Դ��� ���к���
	CUser2 user;
	EntityOpcmdsDispath.Dispatch(&user, msg);
}

BOOST_AUTO_TEST_SUITE_END()