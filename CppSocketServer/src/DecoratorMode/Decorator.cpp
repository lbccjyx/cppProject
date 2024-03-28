#include "Decorator.h"

void ConcreteComponent::Operation()
{
	std::cout << "ConcreteComponent::Operation\n";
}

void ConcreteDecorator::AddedBehavior()
{
	std::cout << "ConcreteDecorator::AddedBehavior\n";
}

void ConcreteDecorator::Operation()
{
	if (_pC)
		_pC->Operation();
	AddedBehavior();
}
