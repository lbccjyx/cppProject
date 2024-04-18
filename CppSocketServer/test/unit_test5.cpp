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

//����Ԥ���˳�����Χ   ----------------�������---------------
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
	ConcreteColleageA* c1 = new ConcreteColleageA(m); // ��ConcreteMediator תΪ Mediator ������Colleage�б���Mediator��ָ��
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
	delete m;
	delete c1;
	delete	c2;
}

BOOST_AUTO_TEST_CASE(my_test24)
{
	std::cout << "\n\n test24 int����Χ����\n";

	U32 u32A = 1861152495;
	myTemplateClass<U32, I32> myTmpObj(u32A);
	std::cout<<"myTmpObj * 30 = "<< myTmpObj * 30 << std::endl;

	U32 x = u32A * 30;
	I64 x1 = u32A * (I64)30;
	std::cout << "x = " << x << std::endl;
	std::cout << "x1 = " << x1 << std::endl;

}

BOOST_AUTO_TEST_CASE(my_test25)
{
	std::cout << "\n\n test25 lambda\n";
	int num = 100;
	int num2 = 200;

	// �޲ξͿ��Բ�Ҫ��()  ��β��()���Ǳ�ʾ���ô�lambda����
	[] {std::cout << "no params\n"; }();
	[num] {std::cout << "one param by name:" << num << "\n"; }();
	// ��׽���������ĳ�Ա���ֵ����
	[=] {std::cout << "all params pass by value: num1: " << num <<"\tnum2:"<<num2 << "\n"; }();
	std::cout << "num&:" << &num << std::endl;
	[&num] {std::cout << "pass one param by reference, num&:" << &num<<std::endl; }();
	// ��׽���������ĳ�Ա������ô���
	[&] {std::cout << "pass all params by reference, num&:" << &num << std::endl; }();
	// ����׽ ͨ��������������
	[](int a, int b) {std::cout << "a+b:" << a + b << std::endl; }(1, 2);
	// ֻҪ�ǲ������� ��ʹû��mutableһ����
	[&num] {std::cout << "add one by reference, num:" << ++num << std::endl; }();
	std::cout << "num:" << num << std::endl;
	// ��ʹ��() ���� �����mutable Ҳ��Ҫ��() ����������п�����mutable������
	[&num]() mutable {std::cout << "add one by reference, num:" << ++num << std::endl; }();
	std::cout << "num:" << num << std::endl;

	std::vector<int> Arr{ 1,2,4,9,5,3 };
	std::sort(Arr.begin(), Arr.end(), [=](int x, int y) {return x < y; });
	int arr[6]{ 1,2,4,9,5,3 };
	std::sort(arr, arr + 6, [=](int x, int y) {return x < y; });
	for (auto i : arr)
		std::cout << i << "\t";
	std::cout<<std::endl;
	for (auto i : Arr)
		std::cout << i << "\t";
	
}
BOOST_AUTO_TEST_SUITE_END()