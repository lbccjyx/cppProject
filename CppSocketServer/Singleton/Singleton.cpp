#include "Singleton.h"

Singleton* Singleton::_instance = 0;

Singleton::Singleton() {
	std::cout << "Singleton..." << std::endl;
};
Singleton* Singleton::instance()
{
	if (_instance == 0)
	{
		_instance = new Singleton();
	}
	return _instance;
}