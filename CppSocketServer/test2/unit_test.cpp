// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_testA1) {
	std::cout << "基础类型 \n";
	// ~((ULONG64)0)：64(1) -> 0+63(1)
	long long a = ~(0uLL)>> 1; // 64位 8字节
	std::cout << a << std::endl;
	// 2 ^ 63 - 1  = 9223372036854775808 - 1 
	std::cout << (1uLL << 63) - 1 << std::endl;
	// 1 + 63(0) 的取反 0 + 63(1)
	std::cout << ~(1uLL << 63)<< std::endl;

	// 遇到w_char 可以改成 char16_t 或 char32_t
	char16_t b = u'a'; // 16位 2字节
	char32_t c = U'a'; // 32位 4字节
	char8_t d = u8'a'; // 8位 1字节   这个是utf8
}

namespace MYN_A
{
	namespace MYN_B
	{
		void func() { std::cout << "Old Function MYN_B\n"; };
	}


	inline namespace MYN_C
	{
		void func() { std::cout << "New Function MYN_C\n"; };
	}
}

BOOST_AUTO_TEST_CASE(my_testA2) {
	std::cout << " \n my_testA2 命名空间中 inline 用法 \n";
	//MYN_A::MYN_B::func();
	MYN_A::func(); // inline 命名空间中可以直接调用
}

// 推导返回类型 要求返回类型一致  函数内部如果if导致返回类型不一致 则会报错
// C++14 中 lambda 形参也可以使用 auto
auto sum(auto a, auto b) { return a + b; }

// 后置声明函数 C++14 可以自动推导函数返回类型 auto sumb(T1 a, T2 b)->decltype(a+b) { return a + b; }
auto sumb(int a, int b)->int { return a + b; }

// C++11标准的万能引用 -使用了引用折叠的规则
template <class T>
void bar(T&& t) {
	// std::forward(t) 完美转发
} 

class CommConstrutor {
public:
	// C++11 引入的委托构造函数  相当于构造函数调用构造函数
	CommConstrutor(int a) :CommConstrutor(a, 0) {};
	CommConstrutor(int a, double b): a_(a), b_(b) { CommonInit(); }

private:
	void CommonInit() {};
	int a_;
	double b_;
};

BOOST_AUTO_TEST_CASE(my_testA3) {
	std::cout << " \n my_testA3 auto 规则 \n";
	
	//volatile  易变的、不可优化的、顺序执行的 直接从内存地址中读取数据，不经过寄存器

	// 按值初始化		推导将忽略CV限定符  const volatile
	const int a = 10;
	auto b = a;				// int


	// 按引用初始化		推导将忽略引用
	int i = 10;
	int &jj = i;
	auto k = jj;			// int

	// 万能引用
	int i1 = 10;
	auto&& mmm = i;			// int&		m -> int& &&
	auto&& jjj = 10;		// int      j -> int&&

	// 数组或函数
	int arri[2]{0,1};  // C++ 11 开始 只要是非静态数据成员都可以直接用=或者{}初始化 ==> 默认初始化

	auto arrm = arri;		// int*

	// decltype(e) 推导规则
	// 如果e是函数调用或者仿函数，则推导结果为函数的返回类型
	// 如果e是类型为T的左值，则推导结果为T&
	// 如果e是类型为T的右值，则推导结果为const T&&
	// 会同步CV限定符
	// 如果是成员变量，则推导结果无CV限定符

	// 位域的默认初始化
	struct A {
		int a : 3 = 11;
		int b : 2 {7};
	};

	// 使用括号的初始化 叫 直接初始化
	// 使用等号的初始化 叫 拷贝初始化(而不是拷贝运算符)
	// C++11引入列表初始化 {} 拥有一个形参为 initializer_list<T> 的构造函数

	// C++11 新增移动构造函数和移动赋值运算符 -> 类的特殊成员函数
	// C++11 前, 如果定义了构造函数 那么不会生成默认的构造函数 C++11后可以通过 xxx() = default; 来生成默认构造函数
	// C++20 三向比较  如果比较耗费很大的时候适用
	std::strong_ordering res = 1 <=> 2;
	if (res == std::strong_ordering::less) {
		std::cout << "1 is less than 2" << std::endl;
	}
	else if (res == std::strong_ordering::equal) {
		std::cout << "1 is equal to 2" << std::endl;
	}
	else {
		std::cout << "1 is greater than 2" << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()

