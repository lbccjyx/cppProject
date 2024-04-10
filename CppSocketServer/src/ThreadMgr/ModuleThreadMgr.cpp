#include "ModuleThreadMgr.h"
#include "Msg/Msg.h"
#include <shared_mutex>

bool CModuleThreadMgr::Post2ModuleThread(CID cid, const IMsg& rMsg, THREAD_TYPE nTaskType)
{
	/*
	std::unique_ptr<IMsg> pMsg(rMsg.Clone());

	std::shared_lock lk(m_TaskArrayMtx, std::defer_lock);

	pMsg->SetTo(cid);
	m_setMsgWrite->push(pMsg.release());
	*/
	return false;
}
