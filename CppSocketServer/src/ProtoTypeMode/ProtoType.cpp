#include "ProtoType.h"

ProtoType::~ProtoType() {};
ProtoType::ProtoType() {};

ConcretePrototype::ConcretePrototype() {};
ConcretePrototype::~ConcretePrototype() {};

// ���漰����㿽��
ConcretePrototype::ConcretePrototype(const ConcretePrototype& cp)
{
	std::cout << "ConcretePrototype copy..." << std::endl;
}

ProtoType* ConcretePrototype::Clone() const
{	
	return new ConcretePrototype(*this);
}