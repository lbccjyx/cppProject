// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include <vector>
#include <boost/assign.hpp>

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test11)
{
	std::cout << "\n\n test11 assign but only support STL\n";

	std::vector<int> v{ 1,2,3 };
	{
		using namespace boost::assign;
		// += 
		v += 4;
		v += 5, 6, 7;
		v.push_back(8);
		// push_back 
		push_back(v), 9, 10;
	}
	BOOST_CHECK_EQUAL(10 , v.size());
	for (auto i : v)
	{
		std::cout << i << std::endl;
	}
}


BOOST_AUTO_TEST_SUITE_END()