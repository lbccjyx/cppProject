// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include "BridgeMode/AbstractionImp.h"
#include "BridgeMode/Abstraction.h"
#include "AdapterMode/Adapter.h"
//#include "DecoratorMode/Decorator.h"
BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test16)
{
	std::cout << "\n\n test16 Bridge Mode\n";
	AbstractionImp* pImpA = new ConcreteAbstractionImpA();
	Abstraction* pRAs = new RefinedAbstraction(pImpA);
	pRAs->Operation();
}
BOOST_AUTO_TEST_CASE(my_test17)
{
	std::cout << "\n\n test17 Adapter Mode\n";
	Adaptee* pAd = new Adaptee;
	Target* pT1 = new Adapter2(pAd);
	pT1->Request();
	// 如果Adaptee的方法无需传参 那么可以直接通过多继承 使用 实现继承
	Target* pT2 = new Adapter();
	pT2->Request();
}
BOOST_AUTO_TEST_SUITE_END()