// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include <queue>

BOOST_AUTO_TEST_SUITE(tests_suit)





BOOST_AUTO_TEST_CASE(my_test36)
{
	std::cout << "\n\n test36 测试线程间通讯\n";



}

BOOST_AUTO_TEST_CASE(my_test37)
{
	std::cout << "\n\n test37 测试 std::swap\n";

	std::queue<int> qA{};
	for (int i = 1; i <= 5; ++i) {
		qA.push(i);
	}

	std::queue<int> qB{};
	std::cout<<"qA address:"<<&qA<<std::endl;
	std::cout<<"qB address:"<<&qB<<std::endl;
	std::cout << "引用是直接换内容而不是地址"<< std::endl;
	std::swap(qA, qB);
	std::cout << "qA address:" << &qA << std::endl;
	std::cout << "qB address:" << &qB << std::endl;
	std::queue<int>* pA = &qA;
	std::queue<int>* pB = &qB;
	std::swap(pA, pB);
	std::cout << "指针直接互换指向" << std::endl;
	std::cout << "pA address:" << pA << std::endl;
	std::cout << "pB address:" << pB << std::endl;

}
BOOST_AUTO_TEST_SUITE_END()