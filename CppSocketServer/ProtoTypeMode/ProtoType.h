#ifndef _PROTOTYPE_H_
#define  _PROTOTYPE_H_

#include "iostream"
class ProtoType
{
public:
	virtual ~ProtoType();
	virtual ProtoType* Clone() const = 0;
protected:
	ProtoType();
};

class ConcretePrototype :public ProtoType
{
public:
	ConcretePrototype();
	ConcretePrototype(const ConcretePrototype& cp);
	~ConcretePrototype();
	ProtoType* Clone() const;
};

#endif