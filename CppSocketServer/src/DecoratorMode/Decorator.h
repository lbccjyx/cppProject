#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <iostream>

class Component
{
public:
	virtual ~Component() {};
	virtual void Operation() = 0;
protected:
	Component() {};
};

class ConcreteComponent : public Component
{
public:
	ConcreteComponent() {};
	~ConcreteComponent() {};
	void Operation()
	{
		std::cout << "ConcreteComponent::Operation\n";	
	};
};

class Decorator : public Component
{
public:
	Decorator(Component* pC) : _pC(pC) {}
	virtual ~Decorator() { delete _pC; }
	void Operation() override {
		if (_pC)
			_pC->Operation();
	}
protected:
	Component* _pC = nullptr;
};


class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(Component* pC) : Decorator(pC) {};
	~ConcreteDecorator() {};
	void Operation()
	{
		if (_pC)
			_pC->Operation();
		AddedBehavior();
	};
	void AddedBehavior() {
		std::cout << "ConcreteDecorator::AddedBehavior\n";
	};

};

#endif
