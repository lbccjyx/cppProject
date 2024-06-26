// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>

void TestPassArgsInFunction()
{
	auto p = new SendaiCSBattleSignUpReportUpdate();
	p->d = 657;
	p->i = 2;

	AllStruct* pAll = new AllStruct;
	pAll->nType = MSGACT_SENDAI;
	pAll->data.normalP = p;
	pAll->bNeedDeleteFlag = true;
	XXXPrint("hehehhe", 3.1456544, std::move(*pAll));
}


BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test1) {
	std::cout << "Test Passing Parameters to another thread in main \n";
	ThreadPrintManagerB ctpm;

	SendaiCSBattleSignUpReportUpdate haha;
	haha.d = 657;
	haha.i = 2;

	AllStruct* pAll = new AllStruct;
	pAll->nType = MSGACT_SENDAI;
	pAll->data.normalP = &haha;
	XXXPrint("hehehhe", 3.1456544, std::move(*pAll));

	// 由于等待线程结束后 haha 内存才会被释放 所以不会出现异常
}

BOOST_AUTO_TEST_CASE(my_test2) {
	std::cout << "\n\nTest Passing Parameters to another thread by Function\n";
	ThreadPrintManagerB ctpm;
	// 由于存在堆栈中所以内存不会异常
	TestPassArgsInFunction();
}

BOOST_AUTO_TEST_CASE(my_test3) {
	std::cout << "\n\n Test RadixSort\n";

	std::vector<int> arr;
	const int numElements = 20;
	// 使用随机设备和分布生成随机数
	std::random_device rd;
	std::mt19937 gen(rd());
	int a = INT32_MAX;
	std::uniform_int_distribution<int> distribution(1, a);

	// 将随机数插入到向量中
	for (int i = 0; i < numElements; ++i) {
		arr.push_back(distribution(gen));
	}

	std::vector<int> arrOut;

	// boost::progress_timer的{}内计时
	{
		boost::progress_timer tt;
		arrOut = RadixSort(arr);
	}

	//std::cout << "Sorted array: ";
	//for (int num : arrOut) {
	//	std::cout << num << " ";
	//}
	//std::cout << std::endl;

}

BOOST_AUTO_TEST_CASE(my_test4) {
	std::cout << "\n\n Test func CreateProcessA\n";

#ifdef UNICODE
#define tstring std::wstring
#define tprintf wprintf
#define Tcsdup wcsdup
#else
#define tstring std::string
#define tprintf printf
#define Tcsdup _strdup
#endif
	// 初始化STARTUPINFO和PROCESS_INFORMATION结构
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.hStdOutput = NULL;

	const char* command = "cout.bat>nul";
	const char* workingDirectory = ".";
	TCHAR* commandCopy = Tcsdup(command);

	int kk = 3;
	do
	{
		if (CreateProcess(NULL, commandCopy, NULL, NULL, FALSE, 0, NULL,
			workingDirectory, &si, &pi)) {
			// 等待进程结束 1秒后直接放弃等待
			WaitForSingleObject(pi.hProcess, 500);
			// 关闭进程和线程的句柄 但是程序依旧运行
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			//std::cout << "Command executed successfully.\n";
		}
		/*	else {
				std::cout << "Failed to execute command.\n";
			}
		std::cout << kk << std::endl;*/
	} while (kk--);


}

BOOST_AUTO_TEST_CASE(my_test5)
{
	std::cout << "\n\n Test timer.hpp\n";

	// boost::timer 用于计时 但是不如boost::progress_timer 方便 同时计时有上限
	boost::timer t;
	std::cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << std::endl;
	std::cout << "min timespan:" << t.elapsed_min() << "s" << std::endl;
	std::cout << "now time elapsed:" << t.elapsed() << "s" << std::endl;

}

BOOST_AUTO_TEST_SUITE_END()

