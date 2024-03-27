// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include "BridgeMode/AbstractionImp.h"
#include "BridgeMode/Abstraction.h"
BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test16)
{
	std::cout << "\n\n test16 Bridge Mode\n";
	AbstractionImp* pImpA = new ConcreteAbstractionImpA();
	Abstraction* pRAs = new RefinedAbstraction(pImpA);
	pRAs->Operation();
}
BOOST_AUTO_TEST_SUITE_END()