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
	sub->SetState("new"); // Ҳ ������Observer ����
	sub->Notify();
}

BOOST_AUTO_TEST_CASE(my_test22)
{
	std::cout << "\n\n test22 Memento Mode\n";
	Originator* o = new Originator();
	o->SetState("old"); //����ǰ״̬
	o->PrintState();
	Memento* m = o->CreateMemento(); //��״̬��Memento��
	o->SetState("new"); //�޸�״̬
	o->PrintState();
	o->RestoreToMemento(m); //��Memento��״̬ȡ��
	o->PrintState();
}

BOOST_AUTO_TEST_CASE(my_test23)
{
	std::cout << "\n\n test23 Mediator Mode\n";
	ConcreteMediator* m = new ConcreteMediator();
	ConcreteColleageA* c1 = new ConcreteColleageA(m); // ��ConcreteMediator תΪ Mediator
	ConcreteColleageB* c2 = new ConcreteColleageB(m);
	m->IntroColleage(c1, c2);
	c1->SetState("old");
	c2->SetState("old");
	c1->Aciton(); // ������ConcreteColleageA ʹ���˻���Colleage�ĳ�ԱMediator* _mdt�� DoActionFromAtoB ���� ��C2��ֵ����Ϊold
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