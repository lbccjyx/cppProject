#pragma once

#include "Msg/Msg.h"
#include "SingletonMode/Singleton.h"
#include <queue>
typedef unsigned int CID; 

enum THREAD_TYPE : int
{
	THREAD_DB = 1,
	THREAD_TRADE = 2,
	THREAD_DB2 = 3,
};

class CModuleThreadMgr
{
	NO_COPY(CModuleThreadMgr);
public:

	CModuleThreadMgr() {};
	~CModuleThreadMgr() {};
	bool Post2ModuleThread(CID cid, const IMsg& rMsg, THREAD_TYPE nTaskType);

protected:
	//std::shared_timed_mutex m_TaskArrayMtx;

	using CMyQueue = std::queue<IMsg*>;
	CMyQueue* m_setMsgWrite = nullptr;

	using MODULETHREADMGR = TSingleton<CModuleThreadMgr>;
};