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
	int arri[2];
	auto arrm = arri;		// int*

	// decltype(e) 推导规则
	// 如果e是函数调用或者仿函数，则推导结果为函数的返回类型
	// 如果e是类型为T的左值，则推导结果为T&
	// 如果e是类型为T的右值，则推导结果为const T&&
	// 会同步CV限定符
	// 如果是成员变量，则推导结果无CV限定符
}

BOOST_AUTO_TEST_SUITE_END()

