#ifndef _BUILDER_DIRECTOR_H_
#define  _BUILDER_DIRECTOR_H_

#include "iostream"
class BuilderMode;
class BuildDirector
{
public:
	BuildDirector(BuilderMode* pBm);
	~BuildDirector();
	void Construct();
private:
	BuilderMode* _pBM = nullptr;
};

#endif