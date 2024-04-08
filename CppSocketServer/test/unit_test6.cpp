// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>

BOOST_AUTO_TEST_SUITE(tests_suit)

BOOST_AUTO_TEST_CASE(my_test26)
{
	std::cout << "\n\n test26\n";
	double a = 80 / 100.0;
	int b = 80 / 100;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
}

BOOST_AUTO_TEST_CASE(my_test27)
{
	std::cout << "\n\n test std::ranges ��Χ��\n";
	
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	auto even = [](int x) { return x % 2 == 0; };
	auto square = [](int x) { return x * x; };

	// ͨ��evenȡ��ż����ͨ��square�任Ϊƽ��   std::views = std::ranges::views
	for(auto x : vec | std::views::filter(even) |  std::views::transform(square))
		std::cout << x << " ";
	std::cout << std::endl;

	// ��ͳ�� ����ʽ ����﷨ 
	for (auto x : std::views::transform(std::views::filter(vec, even), square))
		std::cout << x << " ";
	std::cout << std::endl;

	auto vi = std::ranges::begin(vec);
	BOOST_CHECK_EQUAL(*vi, vec[0]);
	// decltype ��ӡvi������
	std::cout << "decltype(*vi) = " << typeid(decltype(vi)).name() << std::endl;
	BOOST_CHECK_EQUAL(std::ranges::size(vec), vec.size());

	// ʹ�� ""s ��׺������ std::string ���������� ""sv ��׺�����ڴ��� std::string_view ������
	using std::operator""sv;
	constexpr auto words{ "Hello^_^C++^_^23^_^!"sv };
	constexpr auto delim{ "^_^"sv };

	for (const auto word : std::views::split(words, delim))
		// C++23 string_view �ķ�Χ���캯����
		std::cout << std::quoted(std::string_view(word)) << ' ';
	std::cout << '\n';

}

BOOST_AUTO_TEST_CASE(my_test28)
{
	std::cout << "\n\n test std::accumulate\n";
	
	std::vector<int> vec = { 5, 3, 2 };
	// ͨ��std::accumulate���
	int sum = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << "sum = " << sum << std::endl;
	int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
	std::cout << "product = " << product << std::endl;

	auto dash_fold = [](std::string a, int b)
		{
			return std::move(a) + '-' + std::to_string(b);
		};

	std::string s = std::accumulate(std::next(vec.begin()), vec.end(), std::to_string(vec[0]), dash_fold);
	std::cout << "dash_fold = " << s << std::endl;


	std::list<int> listA(10);
	std::iota(listA.begin(), listA.end(), -4);
	auto funcPrintInt = [](int x) { std::cout << x << " "; };
	// ͨ��һ�д���ʵ�ֱ���listA 
	std::ranges::for_each(listA, funcPrintInt);
	std::cout << std::endl;
	std::for_each(listA.begin(), listA.end(), funcPrintInt);

}

BOOST_AUTO_TEST_CASE(my_test29)
{	
// ���ȶ���X�꣬������һ������Ϊ����
#define COLOR_LIST(X) \
    X(RED) \
    X(GREEN) \
    X(BLUE) \
    X(YELLOW)

// ʹ��X�궨����ɫö��
#define GENERATE_ENUM(ENUM) ENUM,
// ʹ��X�궨���ַ�������
#define GENERATE_STRING(STRING) #STRING,

	std::cout << "\n\n test X��\n";

	enum Color {
		COLOR_LIST(GENERATE_ENUM)
	};

	const char* color_names[] = {
		COLOR_LIST(GENERATE_STRING)
	};

	// ��ӡö��ֵ����Ӧ���ַ�������
	for (auto i:color_names) {
		printf(" Name: %s\n",  i);
	}
}

BOOST_AUTO_TEST_CASE(my_test30)
{
	std::cout << "\n\n test 30\n";

#define MSG_FUNC_TABLE			\
	X_FUNC(USER_MSG1, MsgProc1)	\
	X_FUNC(USER_MSG2, MsgProc2)	\
	X_FUNC(USER_MSG3, MsgProc3)	\

	
	enum MSG_TYPE {
#define X_FUNC(a, b) a,
		MSG_FUNC_TABLE
#undef X_FUNC
	} ;

	auto MsgProc1 = []() { std::cout << "Message 1 processed\n"; };
	auto MsgProc2 = []() { std::cout << "Message 2 processed\n"; };
	auto MsgProc3 = []() { std::cout << "Message 3 processed\n"; };

	// ���庯��ָ������ Proc
	// typedef void (*Proc)();
	using Proc = void(*)();
	const Proc Proc_table[] = {
		#define X_FUNC(a, b) b,
		MSG_FUNC_TABLE
		#undef X_FUNC
	};

	auto sMessageProc = [&](MSG_TYPE msgtype) {
		(Proc_table[msgtype])();
	};

	sMessageProc(USER_MSG1);
	sMessageProc(USER_MSG2);
	sMessageProc(USER_MSG3);
}


#define MODULE_TIME_TYPE_DEF()                              \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_CLOSE,   0    /*�ر�*/)  \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_OPEN,    1    /*���ÿ���*/ )   \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_YYMMDD,  3  /*����YYMMDD [begin,end] [��Ȼ��] [reopen_day��Ч]*/  ) \


enum MODULE_TIME_TYPE : int
{
#define MODULE_TIME_TYPE_ROW(x1, x2, ...) x1 = x2,
	MODULE_TIME_TYPE_DEF()
#undef MODULE_TIME_TYPE_ROW
};

template <MODULE_TIME_TYPE e>
inline bool IsTimeFormatValidIns(const INT64 beginFmt, const INT64 endFmt) requires( e == MODULE_TIME_TYPE_OPEN)
{
	return true;
}

BOOST_AUTO_TEST_CASE(my_test31)
{
	std::cout << "\n\n test 31\n";
	std::cout<<IsTimeFormatValidIns<MODULE_TIME_TYPE_OPEN>(0, 0);
}


BOOST_AUTO_TEST_SUITE_END()