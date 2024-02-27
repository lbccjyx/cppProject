#include <iostream>
#define GTEST_LANG_CXX11 1
#	pragma once

class A
{
public:
};

using namespace std;
int main()
{
	A a;
	cout << sizeof(a);
	return 0;
}