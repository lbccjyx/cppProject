// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"


void TestPassArgsInFunction()
{
	SendaiCSBattleSignUpReportUpdate haha;
	haha.d = 657;
	haha.i = 2;
	std::shared_ptr<AllStruct> pAll = std::make_shared<AllStruct>();
	pAll->nType = MSGACT_SENDAI;
	pAll->data.normalP = &haha;

	XXPrint("hehehhe", 3.1456544, *pAll);
}


BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test1) {
	std::cout << "Test Passing Parameters to another thread in main \n";
	threadPrint* a = new threadPrint();
	std::thread tPrint([a] { a->worker(); });

	SendaiCSBattleSignUpReportUpdate haha;
	haha.d = 657;
	haha.i = 2;
	std::shared_ptr<AllStruct> pAll = std::make_shared<AllStruct>();
	pAll->nType = MSGACT_SENDAI;
	pAll->data.normalP = &haha;

	XXPrint("hehehhe", 3.1456544, *pAll);

	a->over();
	tPrint.join();
	std::cout << "my_test1 end\n\n";
}

BOOST_AUTO_TEST_CASE(my_test2) {
	std::cout << "\n\n Test Passing Parameters to another thread by Function\n";
	threadPrint* a = new threadPrint();
	std::thread tPrint([a] { a->worker(); });

	TestPassArgsInFunction();

	a->over();
	tPrint.join();
}

BOOST_AUTO_TEST_CASE(my_test3) {
	std::cout << "\n\n Test RadixSort\n";

	std::vector<int> arr;
	const int numElements = 20;
	// 使用随机设备和分布生成随机数
	std::random_device rd;
	std::mt19937 gen(rd());
	int a = 2147483646;
	std::uniform_int_distribution<int> distribution(1, a);

	// 将随机数插入到向量中
	for (int i = 0; i < numElements; ++i) {
		arr.push_back(distribution(gen));
	}

	std::vector<int> arrOut;
	arrOut = RadixSort(arr);

	std::cout << "Sorted array: ";
	for (int num : arrOut) {
		std::cout << num << " ";
	}
	std::cout<<std::endl;

}
BOOST_AUTO_TEST_SUITE_END()

