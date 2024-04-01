// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>
#include "ObserverMode/Observer.h"
#include "MementoMode/Memento.h"
#include "MediatorMode/Mediator.h"
#include "MediatorMode/Colleage.h"

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test21)
{
	std::cout << "\n\n test21 Observer Mode\n";
	SubjectB* sub = new ConcreteSubjectB();
	Observer* o1 = new ConcreteObserverA(sub);
	Observer* o2 = new ConcreteObserverB(sub);
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new"); // 也 可以由Observer 调用
	sub->Notify();
}

BOOST_AUTO_TEST_CASE(my_test22)
{
	std::cout << "\n\n test22 Memento Mode\n";
	Originator* o = new Originator();
	o->SetState("old"); //备忘前状态
	o->PrintState();
	Memento* m = o->CreateMemento(); //将状态存Memento类
	o->SetState("new"); //修改状态
	o->PrintState();
	o->RestoreToMemento(m); //把Memento类状态取回
	o->PrintState();
}

BOOST_AUTO_TEST_CASE(my_test23)
{
	std::cout << "\n\n test23 Mediator Mode\n";
	ConcreteMediator* m = new ConcreteMediator();
	ConcreteColleageA* c1 = new ConcreteColleageA(m); // 把ConcreteMediator 转为 Mediator
	ConcreteColleageB* c2 = new ConcreteColleageB(m);
	m->IntroColleage(c1, c2);
	c1->SetState("old");
	c2->SetState("old");
	c1->Aciton(); // 派生类ConcreteColleageA 使用了基类Colleage的成员Mediator* _mdt的 DoActionFromAtoB 函数 把C2的值设置为old
	c2->Aciton();
	cout << endl;
	c1->SetState("new");
	c1->Aciton();
	c2->Aciton();
	cout << endl;
	c2->SetState("old");
	c2->Aciton();
	c1->Aciton();
}

BOOST_AUTO_TEST_SUITE_END()