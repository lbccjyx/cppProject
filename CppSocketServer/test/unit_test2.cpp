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

BOOST_AUTO_TEST_CASE(my_test6)
{
	std::cout << "\n\n test7 boost::scoped_ptr\n";
	ThreadPrintManager ctpm;

	// 1: scoped_ptr 不允许拷贝, 赋值  无需delete  -也就是只能在声明的作用域内使用
	boost::scoped_ptr<std::string> sp(new std::string("text"));
	XXPrint("X thread:", *sp);

	std::cout << "\n\n test7 boost::shared_ptr\n";
	boost::shared_ptr<std::string> spStr(new std::string("share text"));
	XXPrint("X thread:", *spStr);

}
BOOST_AUTO_TEST_SUITE_END()

