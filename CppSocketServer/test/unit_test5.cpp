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

typedef unsigned int	   U32;
typedef int		  I32;
typedef long long		  I64;

//用于预防乘除超范围
template<typename T, typename U>
class myTemplateClass {
public:
	myTemplateClass(T a) :_a(a) {}

	U operator*(T nx) {
		if (nx <= 0)
			return -2;

		if (_a * nx < _a)
		{

			return -1;
		}
		return _a * nx;
	}
private:
	T  _a;
};

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
	ConcreteColleageA* c1 = new ConcreteColleageA(m); // 把ConcreteMediator 转为 Mediator 并且在Colleage中保存Mediator的指针
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
	delete m;
	delete c1;
	delete	c2;
}

// 测试用例24
BOOST_AUTO_TEST_CASE(my_test24)
{
	std::cout << "\n\n test24 int超范围测试\n";

	U32 u32A = 1861152495;
	myTemplateClass<U32, I32> myTmpObj(u32A);
	std::cout<<"myTmpObj * 30 = "<< myTmpObj * 30 << std::endl;

	U32 x = u32A * 30;
	I64 x1 = u32A * (I64)30;
	std::cout << "x = " << x << std::endl;
	std::cout << "x1 = " << x1 << std::endl;

}
BOOST_AUTO_TEST_SUITE_END()