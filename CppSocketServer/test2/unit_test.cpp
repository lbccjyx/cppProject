// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_testA1) {
	std::cout << "�������� \n";
	// ~((ULONG64)0)��64(1) -> 0+63(1)
	long long a = ~(0uLL)>> 1; // 64λ 8�ֽ�
	std::cout << a << std::endl;
	// 2 ^ 63 - 1  = 9223372036854775808 - 1 
	std::cout << (1uLL << 63) - 1 << std::endl;
	// 1 + 63(0) ��ȡ�� 0 + 63(1)
	std::cout << ~(1uLL << 63)<< std::endl;

	// ����w_char ���Ըĳ� char16_t �� char32_t
	char16_t b = u'a'; // 16λ 2�ֽ�
	char32_t c = U'a'; // 32λ 4�ֽ�
	char8_t d = u8'a'; // 8λ 1�ֽ�   �����utf8
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
	std::cout << " \n my_testA2 �����ռ��� inline �÷� \n";
	//MYN_A::MYN_B::func();
	MYN_A::func(); // inline �����ռ��п���ֱ�ӵ���
}

// �Ƶ��������� Ҫ�󷵻�����һ��  �����ڲ����if���·������Ͳ�һ�� ��ᱨ��
// C++14 �� lambda �β�Ҳ����ʹ�� auto
auto sum(auto a, auto b) { return a + b; }

// ������������ C++14 �����Զ��Ƶ������������� auto sumb(T1 a, T2 b)->decltype(a+b) { return a + b; }
auto sumb(int a, int b)->int { return a + b; }

// C++11��׼���������� -ʹ���������۵��Ĺ���
template <class T>
void bar(T&& t) {
	// std::forward(t) ����ת��
} 

class CommConstrutor {
public:
	// C++11 �����ί�й��캯��  �൱�ڹ��캯�����ù��캯��
	CommConstrutor(int a) :CommConstrutor(a, 0) {};
	CommConstrutor(int a, double b): a_(a), b_(b) { CommonInit(); }

private:
	void CommonInit() {};
	int a_;
	double b_;
};

BOOST_AUTO_TEST_CASE(my_testA3) {
	std::cout << " \n my_testA3 auto ���� \n";
	
	//volatile  �ױ�ġ������Ż��ġ�˳��ִ�е� ֱ�Ӵ��ڴ��ַ�ж�ȡ���ݣ��������Ĵ���

	// ��ֵ��ʼ��		�Ƶ�������CV�޶���  const volatile
	const int a = 10;
	auto b = a;				// int


	// �����ó�ʼ��		�Ƶ�����������
	int i = 10;
	int &jj = i;
	auto k = jj;			// int

	// ��������
	int i1 = 10;
	auto&& mmm = i;			// int&		m -> int& &&
	auto&& jjj = 10;		// int      j -> int&&

	// �������
	int arri[2]{0,1};  // C++ 11 ��ʼ ֻҪ�ǷǾ�̬���ݳ�Ա������ֱ����=����{}��ʼ�� ==> Ĭ�ϳ�ʼ��

	auto arrm = arri;		// int*

	// decltype(e) �Ƶ�����
	// ���e�Ǻ������û��߷º��������Ƶ����Ϊ�����ķ�������
	// ���e������ΪT����ֵ�����Ƶ����ΪT&
	// ���e������ΪT����ֵ�����Ƶ����Ϊconst T&&
	// ��ͬ��CV�޶���
	// ����ǳ�Ա���������Ƶ������CV�޶���

	// λ���Ĭ�ϳ�ʼ��
	struct A {
		int a : 3 = 11;
		int b : 2 {7};
	};

	// ʹ�����ŵĳ�ʼ�� �� ֱ�ӳ�ʼ��
	// ʹ�õȺŵĳ�ʼ�� �� ������ʼ��(�����ǿ��������)
	// C++11�����б��ʼ�� {} ӵ��һ���β�Ϊ initializer_list<T> �Ĺ��캯��

	// C++11 �����ƶ����캯�����ƶ���ֵ����� -> ��������Ա����
	// C++11 ǰ, ��������˹��캯�� ��ô��������Ĭ�ϵĹ��캯�� C++11�����ͨ�� xxx() = default; ������Ĭ�Ϲ��캯��
	// C++20 ����Ƚ�  ����ȽϺķѺܴ��ʱ������
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

