//Observer.h 
#ifndef _OBSERVER_H_ 
#define _OBSERVER_H_ 
#include "SubjectB.h" 
#include <string>

typedef std::string State;
class Observer
{
public:
	virtual ~Observer();
	virtual void Update(SubjectB* sub) = 0;
	virtual void PrintInfo() = 0;
protected:
	Observer();
	State _st;
};
class ConcreteObserverA :public Observer
{
public:
	virtual SubjectB* GetSubjectB();
	ConcreteObserverA(SubjectB* sub);
	virtual ~ConcreteObserverA();
	//���� SubjectB ��Ϊ����������������һ��View ���ڶ���� SubjectB
	void Update(SubjectB* sub);
	void PrintInfo();
private:
	SubjectB* _sub;
};
class ConcreteObserverB :public Observer
{
public:
	virtual SubjectB* GetSubjectB();
	ConcreteObserverB(SubjectB* sub);
	virtual ~ConcreteObserverB();
	//���� SubjectB ��Ϊ����������������һ��View ���ڶ���� SubjectB
	void Update(SubjectB* sub);
	void PrintInfo();
private:
	SubjectB* _sub;
};
#endif //~_OBSERVER_H_