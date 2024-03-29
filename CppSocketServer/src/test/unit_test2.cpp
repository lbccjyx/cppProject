// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>
#include <boost/timer.hpp>
#include <boost/smart_ptr.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(tests_suit)

struct AmuletCreateReq
{
	INT64 arrayIdCostItem[0];
};
void PrintArray0(AmuletCreateReq& Arc)
{

	for (int i = 0; i < 5; ++i)
	{
		std::cout << Arc.arrayIdCostItem[i] << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(my_test6)
{
	std::cout << "\n\n test6 boost::scoped_ptr\n";
	ThreadPrintManager ctpm;

	// 1: scoped_ptr 不允许拷贝, 赋值  无需delete  -也就是只能在声明的作用域内使用
	boost::scoped_ptr<std::string> sp(new std::string("text"));
	XXPrint("X thread:", *sp);

	std::cout << "\n\n test6 boost::shared_ptr\n";
	boost::shared_ptr<std::string> spStr(new std::string("share text"));
	XXPrint("X thread:", *spStr);

}

BOOST_AUTO_TEST_CASE(my_test7)
{
	std::cout << "\n\n test7 Test array[0]\n";
#ifdef _WIN32

	AmuletCreateReq acr{ 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		std::cout<< acr.arrayIdCostItem[i]<<std::endl;
	}
#elif __linux__
	struct Tick 
	{
		AmuletCreateReq req;
		INT64 arr[5];
	};

	Tick tick{ {},{1,2,3,4,5} };

	auto& arc = tick.req;

	for (int i = 0; i < 5; ++i)
	{
		std::cout << acr.arrayIdCostItem[i] << std::endl;
	}
#endif
}

BOOST_AUTO_TEST_CASE(my_test8)
{
	std::cout << "\n\n test8 Test array[0]\n";
	struct Tick
	{
		INT64 arrayIdCostItem[5];
	};

	Tick tick{ {1,2,3,4,5} };
	AmuletCreateReq& arc = *  ( (AmuletCreateReq*)(&tick) );
	PrintArray0(arc);
}

BOOST_AUTO_TEST_CASE(my_test9)
{
	std::cout << "\n\n test9 Test array[0]\n";
	struct Tick
	{
		INT64 arrayIdCostItem[5];
	};

	union Req {
		AmuletCreateReq rec;
		Tick tick;
	};

	Req req;
	req.tick = {{1,2,3,4,5} };
	auto& arc = req.rec;
	req.rec.arrayIdCostItem[0] = 100000000;
	PrintArray0(arc);
}

BOOST_AUTO_TEST_CASE(my_test10)
{
	std::cout << "\n\n test10 Test array[0]\n";
	auto pArc = (AmuletCreateReq*)malloc(sizeof(AmuletCreateReq) + sizeof(int) * 5);
	memset(pArc, 0, sizeof(AmuletCreateReq) + sizeof(int) * 5);

	for (int i = 0; i < 5; ++i)
	{
		pArc->arrayIdCostItem[i] = i + 1;
	}
	PrintArray0(*pArc);
	free(pArc);
}


BOOST_AUTO_TEST_SUITE_END()