#include "Adapter.h"

void Target::Request()
{
	std::cout << "target::Request\n";
}
void Adaptee::SpecificRequest()
{
	std::cout << "Adaptee::SpecificRequest\n";
}

void Adapter::Request()
{
	this->SpecificRequest();
}

Adapter2::Adapter2(Adaptee* pAd)
{
	if (pAd)
		_ade = pAd;
}

void Adapter2::Request()
{
	_ade->SpecificRequest();
}