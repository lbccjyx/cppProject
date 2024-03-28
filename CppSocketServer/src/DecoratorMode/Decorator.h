#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <iostream>

class Component
{
public:
	virtual ~Component() {}
	virtual void Operation() = 0;
protected:
	Component() {}
};

class ConcreteComponent : public Component
{
public:
	ConcreteComponent() {}
	~ConcreteComponent() {}
	void Operation() override;
};

class Decorator : public Component
{
public:
	Decorator(Component* pC) : _pC(pC) {}
	virtual ~Decorator() { delete _pC; }
	void Operation() override {}
protected:
	Component* _pC;
};

class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(Component* pC) : Decorator(pC) {}
	~ConcreteDecorator() {}
	void Operation() override;
	void AddedBehavior();
};

#endif
