#include "BuilderMode.h"
#include "BuilderProduct.h"
#pragma once
BuilderMode::BuilderMode() {};
BuilderMode::~BuilderMode() {};


ConcreteBuilderMode::ConcreteBuilderMode() {};
ConcreteBuilderMode::~ConcreteBuilderMode() {};

void ConcreteBuilderMode::BuildPartA(const std::string& str)
{
	std::cout << "Step1 Build Part A: " << str<< std::endl;
}

void ConcreteBuilderMode::BuildPartB(const std::string& str)
{
	std::cout << "Step1 Build Part B: " << str << std::endl;
}
void ConcreteBuilderMode::BuildPartC(const std::string& str)
{
	std::cout << "Step1 Build Part C: " << str << std::endl;
}
BuildProduct* ConcreteBuilderMode::GetProduct()
{
	BuildPartA("pre-defined");
	BuildPartB("pre-defined");
	BuildPartC("pre-defined");
	return new BuildProduct;
}