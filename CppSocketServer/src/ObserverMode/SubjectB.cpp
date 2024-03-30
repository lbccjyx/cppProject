#include "SubjectB.h" 
#include "Observer.h" 
#include <iostream> 
SubjectB::SubjectB()
{
	_obvs = new std::list<Observer*>;
}
SubjectB::~SubjectB()
{ }
void SubjectB::Attach(Observer* obv)
{
	_obvs->push_front(obv);
}
void SubjectB::Detach(Observer* obv)
{
	if (obv != NULL)
		_obvs->remove(obv);
}
void SubjectB::Notify()
{
	for (auto it: *_obvs)
	{ //关于模板和 iterator 的用法
		it->Update(this);
	}
}
ConcreteSubjectB::ConcreteSubjectB()
{
	_st = '\0';
}
ConcreteSubjectB::~ConcreteSubjectB()
{ }
State ConcreteSubjectB::GetState()
{
	return _st;
}
void ConcreteSubjectB::SetState(const State& st)
{
	_st = st;
}