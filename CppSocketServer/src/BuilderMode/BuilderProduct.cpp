#include "BuilderProduct.h"
#pragma once
BuildProduct::BuildProduct() {};
BuildProduct::~BuildProduct() {};
void BuildProduct::ProducePart()
{

}

BuildProductPart::BuildProductPart() {};
BuildProductPart::~BuildProductPart() {};
BuildProductPart* BuildProductPart::BuildPart()
{
	return this;
}