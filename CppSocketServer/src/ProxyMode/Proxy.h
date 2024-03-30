#ifndef _PROXY_H_
#define _PROXY_H_

class Subject
{
public:
	virtual ~Subject() {};
	virtual void Request() = 0;
protected:
	Subject() {};
private:
};
class ConcreteSubject :public Subject
{
public:
	ConcreteSubject() {};
	~ConcreteSubject() {};
	void Request() { std::cout << "ConcreteSubject:Request\n"; };
};
class Proxy
{
public:
	Proxy() {};
	Proxy(Subject* sub) :_sub(sub) {};
	~Proxy() {};
	void Request() { _sub->Request(); };
private:
	Subject* _sub = nullptr;
};

#endif