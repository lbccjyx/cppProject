#ifndef _BUILD_MODE_H_
#define  _BUILD_MODE_H_

#include "iostream"
class BuildProduct;
class BuilderMode
{
public:
	virtual ~BuilderMode();
	virtual void BuildPartA(const std::string& str) = 0;
	virtual void BuildPartB(const std::string& str) = 0;
	virtual void BuildPartC(const std::string& str) = 0;
	virtual BuildProduct* GetProduct() = 0;
protected:
	BuilderMode();

};

class ConcreteBuilderMode :public BuilderMode
{
public:
	ConcreteBuilderMode();
	~ConcreteBuilderMode();
	void BuildPartA(const std::string& str) override;
	void BuildPartB(const std::string& str) override;
	void BuildPartC(const std::string& str) override;
	BuildProduct* GetProduct();
};

#endif