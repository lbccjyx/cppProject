// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include "Msg/Msg.h"
BOOST_AUTO_TEST_SUITE(tests_suit)
struct MSG_INFO
{
	USHORT usMsgSize;
	USHORT usMsgType;

	unsigned char ucAction;
	PBYTE		  GetBufAddr()
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

struct MSGCMD
{
	union
	{
		void* m_pPoint;
		OrderQuery* m_pOrderQuery;
	};
	MSGCMD(void* pBuf = NULL): m_pPoint((void*)pBuf){}
};

bool OnRcvCMsg(const CMsg& rMsg)
{
	const void* pMsg = rMsg.GetBuf();
	const MSG_HEAD* pHead = (const MSG_HEAD*)pMsg; 
	switch (pHead->usType)
	{
	case 1:
	{
		MSG_INFO* pInfo = (MSG_INFO*)pMsg;
		MSGCMD rPoint(pInfo->GetBufAddr());;
		switch (pInfo->ucAction)
		{
		case 1:
		{
			std::cout << "pHead->usType: "<< pHead->usType <<", pInfo->ucAction: "<<pInfo->ucAction
				<<", pPoint->m_pOrderQuery->idUser: " << rPoint.m_pOrderQuery->idUser
				<< ", pPoint->m_pOrderQuery->nAnther: " << rPoint.m_pOrderQuery->nAnther << std::endl;
			return true;
		}
		
		}

		break;
	}
	default:
		return false;
	}
}

BOOST_AUTO_TEST_CASE(my_test35)
{
	std::cout << "\n\n test35 消息的组装和解析 \n";
	char msgBuf[1024] = { 0 };
	MSG_INFO* pHead = (MSG_INFO*)msgBuf;
	OrderQuery* pBody = (OrderQuery*)pHead->GetBufAddr();
	pHead->usMsgType = 1;
	pHead->ucAction = 1;

	pBody->idUser = 10000000;
	pBody->nAnther = 2;

	pHead->usMsgSize = sizeof(*pHead) + sizeof(*pBody);

	CMsg msg;
	msg.Create(msgBuf, pHead->usMsgSize);
	OnRcvCMsg(msg);
}

BOOST_AUTO_TEST_SUITE_END()