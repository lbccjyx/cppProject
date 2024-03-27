#include "BuilderDirector.h"
#include "BuilderMode.h"
#pragma once
BuildDirector::BuildDirector(BuilderMode* pBm)
{
	if (pBm)
		_pBM = pBm;
}

BuildDirector::~BuildDirector() {
	if(_pBM)
		delete _pBM;
};

void BuildDirector::Construct()
{
	if (!_pBM)
		return;

	_pBM->BuildPartA("user_defined");
	_pBM->BuildPartB("user_defined");
	_pBM->BuildPartC("user_defined");
	_pBM->GetProduct();
}