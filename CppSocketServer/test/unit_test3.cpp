// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include <vector>
#include <boost/assign.hpp>
#include "FactoryMode/Product.h"
#include "factoryMode/Factory.h"
#include "Singleton/Singleton.h"
#include "BuilderMode/BuilderDirector.h"
#include "BuilderMode/BuilderMode.h"
#include "BuilderMode/BuilderProduct.h"
#include "ProtoTypeMode/ProtoType.h"

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

BOOST_AUTO_TEST_CASE(my_test12)
{
	std::cout << "\n\n test12 Factory Mode\n";
	Factory* pFac = new ConcreteFactory();
	//在这里 factoryMode 的好处是不需要知道ConcreteProduct的名字
	Product* pProd = pFac->CreateProduct();
	delete pFac;
	delete pProd;
}

BOOST_AUTO_TEST_CASE(my_test13)
{
	std::cout << "\n\n test13 SingletonMode: Create One Object\n";
	Singleton* sgn = Singleton::instance();
}

BOOST_AUTO_TEST_CASE(my_test14)
{
	std::cout << "\n\n test14 DirectorMode: Create Complex Object\n";
	// BuildDirector 类里面有个基类指针  给指针赋值派生类 
	ConcreteBuilderMode* pCB = new ConcreteBuilderMode();
	BuildDirector* d = new BuildDirector(pCB);
	// 一般来说：ConcreteBuilderMode 类应该初始化很复杂
	d->Construct();
	
	delete d;
	delete pCB;
}


BOOST_AUTO_TEST_CASE(my_test15)
{
	std::cout << "\n\n test15 ProtoType Mode\n";
	ProtoType* pPt = new ConcretePrototype();
	ProtoType* pPt2 = pPt->Clone();
	delete pPt;
	delete pPt2;
}

BOOST_AUTO_TEST_SUITE_END()