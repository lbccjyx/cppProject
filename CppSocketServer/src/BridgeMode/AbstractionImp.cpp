#include "AbstractionImp.h"

void AbstractionImp::Operation()
{
	std::cout << "AbstractionImp ... operation" << std::endl;
}

void ConcreteAbstractionImpA::Operation()
{
	std::cout << "ConcreteAbstractionImpA ... operation" << std::endl;
}

void ConcreteAbstractionImpB::Operation()
{
	std::cout << "ConcreteAbstractionImpB ... operation" << std::endl;
}