#pragma once
#include <mutex>
#include <random>
#include <algorithm>
#include <queue>
#include <functional>

enum MSGACT : int
{
	MSGACT_SENDAI = 1,
};
struct SendaiCSBattleSignUpReportUpdate
{
	int i;
	double d;

	~SendaiCSBattleSignUpReportUpdate()
	{
		std::cout << "SendaiCSBattleSignUpReportUpdate Destructor\n";
	}
	
};

class AllStruct
{
public:
	int nType = 0;
	bool bNeedDeleteFlag = false;
	union MyUnion
	{
		void* normalP;
		SendaiCSBattleSignUpReportUpdate* pSendai;
	} data;

public:
	//AllStruct() {
	//	std::cout << "Constructor\n";
	//};

	//~AllStruct() {
	//	std::cout << "Destructor\n";
	//}; 

	//AllStruct(const AllStruct& other) : data(other.data),nType(other.nType), bNeedDeleteFlag(other.bNeedDeleteFlag){
	//	std::cout << "Copy Constructor\n";
	//}

	//AllStruct& operator=(AllStruct& allIn) {

	//	std::cout << "Operator\n";
	//	if (this != &allIn)
	//	{
	//		this->nType = allIn.nType;
	//		this->data = allIn.data;
	//	}
	//	return *this;
	//};
};

static std::mutex threadPrintMtx;
static std::queue<std::function<void()>> threadPrintTasks;
static std::condition_variable threadPrintCv;
static bool threadPrintDone = false;

class threadPrint
{
public:
	static threadPrint* instance;
	threadPrint() { instance = this; };

	template <typename T, typename... Types>
	void NewPrint(const T& firstArg, const Types&... args)
	{
		auto task = [this, firstArg]() {
			DetailPrint<T>(firstArg);
			};
		{
			std::lock_guard<std::mutex> lock(threadPrintMtx);
			threadPrintTasks.push(task);
		}
		threadPrintCv.notify_one();
		// recursive   tuple
		NewPrint(args...);
	};
	void NewPrint() {};
	void worker() {
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(threadPrintMtx);
				threadPrintCv.wait(lock, [] { return !threadPrintTasks.empty() || threadPrintDone; });
				if (threadPrintDone && threadPrintTasks.empty()) return;
				task = std::move(threadPrintTasks.front());
				threadPrintTasks.pop();
			}
			task();
		}
	};

	void over()
	{
		std::lock_guard<std::mutex> lock(threadPrintMtx);
		threadPrintDone = true;
		threadPrintCv.notify_one();
	}
private:
	template <typename T>
	void DetailPrint(const T& arg)
	{
		if constexpr (std::is_same<T, AllStruct>::value)
		{
			const AllStruct& allStruct = arg;
			switch (allStruct.nType)
			{
			case MSGACT_SENDAI:
				SendaiCSBattleSignUpReportUpdate* p = allStruct.data.pSendai; 
				std::cout << "SendaiCSBattleSignUpReportUpdate: i = " << p->i << ", d = " << p->d << "\n";
				if(allStruct.bNeedDeleteFlag)
					delete p;
			}
			
		}
		else
		{
			// 其他类型的参数直接输出
			std::cout << arg << "\n";
		}
	}
};
// threadPrint* MyThreadPrint = threadPrint::instance;
#define XXPrint(...) threadPrint::instance->NewPrint(__VA_ARGS__)

