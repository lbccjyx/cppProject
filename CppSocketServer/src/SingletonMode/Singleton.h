#ifndef _SINGLETON_H_
#define  _SINGLETON_H_

#include "iostream"
class Singleton
{
public:
	static Singleton* instance();
protected:
	Singleton();
private:
	static Singleton* _instance;
};


#endif