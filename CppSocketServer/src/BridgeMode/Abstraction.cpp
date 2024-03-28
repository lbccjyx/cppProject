#include "Abstraction.h"
#include "AbstractionImp.h"
RefinedAbstraction::RefinedAbstraction(AbstractionImp* pImp)
{
	if (pImp)
		_pImp = pImp;
}

void RefinedAbstraction::Operation()
{
	_pImp->Operation();
}
