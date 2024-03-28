#ifndef _BUILDER_PRODUCT_H_
#define  _BUILDER_PRODUCT_H_

#include "iostream"
class BuildProduct
{
public:
	BuildProduct();
	~BuildProduct();
	void ProducePart();
};

class BuildProductPart
{
public:
	BuildProductPart();
	~BuildProductPart();
	BuildProductPart* BuildPart();
};

#endif