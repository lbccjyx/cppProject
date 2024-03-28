#ifndef _ABSTRACTION_H_
#define  _ABSTRACTION_H_

#include "iostream"
class AbstractionImp;
class Abstraction
{
public:
	virtual ~Abstraction() {};
	virtual void Operation() = 0;
protected:
	Abstraction() {};
};


class RefinedAbstraction : public Abstraction
{
public:
	RefinedAbstraction(AbstractionImp* pImp);
	~RefinedAbstraction() {};
	void Operation();

private:
	AbstractionImp* _pImp = nullptr;
};
#endif