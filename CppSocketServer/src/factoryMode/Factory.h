#include "iostream"

#ifndef _FACTORY_H_
#define  _FACTORY_H_

class Product;

class Factory
{
public:
	virtual ~Factory() = 0; // 如果不是virtual 基类指针的析构不会执行派生类的析构
	virtual Product* CreateProduct() = 0;
protected:
	Factory();

};

class ConcreteFactory :public Factory
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product* CreateProduct() override;
};
#endif