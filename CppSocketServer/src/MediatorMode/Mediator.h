#ifndef _MEDIATOR_H_ 
#define _MEDIATOR_H_ 
class Colleage;
class Mediator
{
public:
	virtual ~Mediator();
	virtual void DoActionFromAtoB() = 0;
	virtual void DoActionFromBtoA() = 0;
protected:
	Mediator();
};

class ConcreteMediator :public Mediator
{
public:
	ConcreteMediator();
	ConcreteMediator(Colleage* clgA, Colleage* clgB);
	~ConcreteMediator();
	void SetConcreteColleageA(Colleage* pClgA);
	void SetConcreteColleageB(Colleage* pClgB);
	Colleage* GetConcreteColleageA();
	Colleage* GetConcreteColleageB();
	void IntroColleage(Colleage* pClgA, Colleage* pClgB);
	void DoActionFromAtoB();
	void DoActionFromBtoA();
private:
	Colleage* _clgA;
	Colleage* _clgB;
};
#endif //~_MEDIATOR_H