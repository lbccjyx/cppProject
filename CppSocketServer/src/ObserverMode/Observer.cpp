//Observer.cpp
#include "Observer.h" 
#include "SubjectB.h" 
#include <iostream> 
Observer::Observer()
{
	_st = '\0';
}
Observer::~Observer()
{
}
ConcreteObserverA::ConcreteObserverA(SubjectB* sub)
{
	_sub = sub;
	_sub->Attach(this);
}
ConcreteObserverA::~ConcreteObserverA()
{
	_sub->Detach(this);
	if (_sub != 0)
		delete _sub;
}
SubjectB* ConcreteObserverA::GetSubjectB()
{
	return _sub;
}
void ConcreteObserverA::PrintInfo()
{
	std::cout << "ConcreteObserverA observer...."<<_sub->GetState()<< std::endl;
}
void ConcreteObserverA::Update(SubjectB* sub)
{
	_st = sub->GetState();
	PrintInfo();
}
ConcreteObserverB::ConcreteObserverB(SubjectB* sub)
{
	_sub = sub;
	_sub->Attach(this);
}

ConcreteObserverB::~ConcreteObserverB()
{
	_sub->Detach(this);
	if (_sub != 0)
	{
		delete _sub;
	}
}
SubjectB* ConcreteObserverB::GetSubjectB()
{
	return _sub;
}

void ConcreteObserverB::PrintInfo()
{
	std::cout << "ConcreteObserverB observer...."<<_sub->GetState()<<std::endl; 
}
void ConcreteObserverB::Update(SubjectB* sub)
{
	_st = sub->GetState();
	PrintInfo();
}