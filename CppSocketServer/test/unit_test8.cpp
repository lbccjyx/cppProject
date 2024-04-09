// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test35)
{
	std::cout << "\n\n test35\n";
	double a = 80 / 100.0;
	int b = 80 / 100;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()