#ifndef _ADAPTER_H_
#define  _ADAPTER_H_

#include "iostream"
class Target
{
public:
	Target() {};
	virtual ~Target() {};
	virtual void Request();
};

class Adaptee
{
public:
	Adaptee() {};
	~Adaptee() {};
	void SpecificRequest();
};

class Adapter :public Target, private Adaptee {
public:
	Adapter() {};
	~Adapter() {};
	void Request();
};

class Adapter2 :public Target
{
public:
	Adapter2(Adaptee* pAd);
	~Adapter2() {};
	void Request();
private:
	Adaptee* _ade = nullptr;
};
#endif