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
#include "DecoratorMode/Decorator.h"
#include "CompositeMode/Composite.h"
#include "ProxyMode/Proxy.h"
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

BOOST_AUTO_TEST_CASE(my_test18)
{
	std::cout << "\n\n test18 Decoration Mode\n";
	Component* pC = new ConcreteComponent();
	Decorator* pD = new ConcreteDecorator(pC);
	pD->Operation();
	// 这样每要addBehavior的时候只要更改ConcreteDecorator
	// ConcreteComponent::Operation
	// ConcreteDecorator::AddedBehavior
}

BOOST_AUTO_TEST_CASE(my_test19)
{
	std::cout << "\n\n test19 Composite Mode\n";
	leaf* pL = new leaf();
	pL->Operation();
	Composite* pC = new Composite();
	pC->Add(pL);
	pC->Operation();
	
	ComponentB* pCB = pC->GetChild(0);
	if(pCB)
		pCB->Operation();
}
BOOST_AUTO_TEST_CASE(my_test20)
{
	std::cout << "\n\n test20 Proxy Mode\n";
	Subject* pS = new ConcreteSubject();
	Proxy* pProxy = new Proxy(pS);
	pProxy->Request();
}
BOOST_AUTO_TEST_SUITE_END()