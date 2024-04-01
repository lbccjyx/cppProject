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
	AllStruct() {
		std::cout << "Constructor\n";
	};

	~AllStruct() {
		std::cout << "Destructor\n";
	}; 

	AllStruct(const AllStruct& other) : data(other.data),nType(other.nType), bNeedDeleteFlag(other.bNeedDeleteFlag){
		std::cout << "Copy Constructor\n";
	}

	AllStruct& operator=(AllStruct& allIn) {

		std::cout << "Operator\n";
		if (this != &allIn)
		{
			this->nType = allIn.nType;
			this->data = allIn.data;
		}
		return *this;
	};
};

static std::mutex threadPrintMtx;
static std::queue<std::function<void()>> threadPrintTasks;
static std::condition_variable threadPrintCv;
static bool threadPrintDone = false;

static std::mutex threadPrintMtxB;
static std::queue<std::function<void()>> threadPrintTasksB;
static std::condition_variable threadPrintCvB;
static bool threadPrintDoneB = false;

class threadPrintB
{
public:
	static threadPrintB* instance;
	threadPrintB() { instance = this; };

	template <typename T, typename... Types>
	void NewPrintB(T&& firstArg, Types&&... args)
	{
		// 捕捉&firstArg 否则会导致拷贝构造
		auto task = [this, &firstArg] {
			DetailPrintB(firstArg);
			};
		{
			std::lock_guard<std::mutex> lock(threadPrintMtxB);
			threadPrintTasksB.push(task);
			threadPrintCvB.notify_one();
		}
		// recursive tuple
		NewPrintB(std::forward<Types>(args)...);
	};

	void NewPrintB() {};
	void workerB() {
		while (true) {
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(threadPrintMtxB);
				threadPrintCvB.wait(lock, [] { return !threadPrintTasksB.empty() || threadPrintDoneB; });
				if (threadPrintDoneB && threadPrintTasksB.empty()) return;
				task = std::move(threadPrintTasksB.front());
				threadPrintTasksB.pop();
			}
			task();
		}
	};

	void overB()
	{
		std::lock_guard<std::mutex> lock(threadPrintMtxB);
		threadPrintDoneB = true;
		threadPrintCvB.notify_one();
	}
private:
	template <typename T>
	void DetailPrintB(T&& arg)
	{
		if constexpr (std::is_same<std::decay_t<T>, AllStruct>::value)
		{
			auto&& allStruct = std::forward<T&&>(arg);
			switch (allStruct.nType)
			{
			case MSGACT_SENDAI:
			{
				SendaiCSBattleSignUpReportUpdate* p = allStruct.data.pSendai;
				std::cout << "SendaiCSBattleSignUpReportUpdate: i = " << p->i << ", d = " << p->d << "\n";
				if (allStruct.bNeedDeleteFlag)
					delete p;
				break;
			}
			}
			delete &allStruct;
		}
		else
		{
			// 其他类型的参数直接输出
			std::cout << std::forward<T&&>(arg) << "\n";
		}
	};

};


class threadPrint
{
public:
	static threadPrint* instance;
	threadPrint() { instance = this; };

	template <typename T, typename... Types>
	void NewPrint(T firstArg, Types... args)
	{
		auto task = [this, firstArg] {
			std::cout << firstArg << "\n";
			};
		{
			std::lock_guard<std::mutex> lock(threadPrintMtx);
			threadPrintTasks.push(task);
			threadPrintCv.notify_one();
		}
		// recursive tuple
		NewPrint(std::forward<Types>(args)...);
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
};

class ThreadPrintManager {
public:
	ThreadPrintManager() {
		a = new threadPrint();
		tPrint = std::thread([this] { a->worker(); });
	}

	~ThreadPrintManager() {
		a->over();
		tPrint.join();
		delete a;
	}

private:
	threadPrint* a;
	std::thread tPrint;
};

class ThreadPrintManagerB {
public:
	ThreadPrintManagerB() {
		a = new threadPrintB();
		tPrint = std::thread([this] { a->workerB(); });
	}

	~ThreadPrintManagerB() {
		a->overB();
		tPrint.join();
		delete a;
	}

private:
	threadPrintB* a;
	std::thread tPrint;
};
// std::forward：用于在模板函数中正确地转发参数。它可以将左值引用转发为左值引用，将右值引用转发为右值引用，同时保留参数的值类别（value category）。
// std::move：用于将对象转换为右值引用，通常用于移动语义。移动语义允许将资源（如堆上分配的内存或文件句柄）从一个对象“移动”到另一个对象，而不是进行昂贵的拷贝操作。
// 
// 
// threadPrint* MyThreadPrint = threadPrint::instance;
#define XXPrint(...) threadPrint::instance->NewPrint(__VA_ARGS__)
#define XXXPrint(...) threadPrintB::instance->NewPrintB(__VA_ARGS__)