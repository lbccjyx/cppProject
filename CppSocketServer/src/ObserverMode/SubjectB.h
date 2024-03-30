//SubjectB.h 
#ifndef _SubjectB_H_ 
#define _SubjectB_H_ 
#include <list>
#include <string>
typedef std::string State;
class Observer;
class SubjectB
{
public:
	virtual ~SubjectB();
	void Attach(Observer* obv);
	void Detach(Observer* obv);
	void Notify();
	virtual void SetState(const State& st) = 0;
	virtual State GetState() = 0;
protected:
	SubjectB();
private:
	std::list<Observer* >* _obvs;
};
class ConcreteSubjectB :public SubjectB
{
public:
	ConcreteSubjectB();
	~ConcreteSubjectB();
	State GetState();
	void SetState(const State& st);
private:
	State _st;
};
#endif //~_SubjectB_H_
