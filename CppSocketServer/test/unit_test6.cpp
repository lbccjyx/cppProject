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


#define MODULE_TIME_TYPE_DEF                            \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_CLOSE,   0    /*�ر�*/)  \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_OPEN,    1    /*���ÿ���*/ )   \
	MODULE_TIME_TYPE_ROW(MODULE_TIME_TYPE_YYMMDD,  3  /*����YYMMDD [begin,end] [��Ȼ��] [reopen_day��Ч]*/  ) \


enum MODULE_TIME_TYPE : int
{
#define MODULE_TIME_TYPE_ROW(x1, x2, ...) x1 = x2,
	MODULE_TIME_TYPE_DEF
#undef MODULE_TIME_TYPE_ROW
};

template <MODULE_TIME_TYPE e>
inline bool IsTimeFormatValidIns(const INT64 beginFmt, const INT64 endFmt) requires(e == MODULE_TIME_TYPE_OPEN )
{
	return true;
}

template <MODULE_TIME_TYPE e>
inline bool IsTimeFormatValidIns(const INT64 beginFmt, const INT64 endFmt) requires(e == MODULE_TIME_TYPE_CLOSE || e == MODULE_TIME_TYPE_YYMMDD)
{
	return true;
}

bool IsTimeFormatValid(const MODULE_TIME_TYPE eType, const INT64 beginFmt, const INT64 endFmt)
{
	switch (eType)
	{
#define MODULE_TIME_TYPE_ROW(x1, ...)                      \
	case x1:                                               \
		return IsTimeFormatValidIns<x1>(beginFmt, endFmt); \
		break;


		MODULE_TIME_TYPE_DEF	//������� ,��ȷ���Ƿ��� ��Ӧ [MODULE_TIME_TYPE]  IsTimeFormatValidIns ר�ú���

#undef MODULE_TIME_TYPE_ROW
	default:
		break;
	};
	return false;
}

BOOST_AUTO_TEST_CASE(my_test31)
{
	std::cout << "\n\n test 31\n";
	std::cout<<IsTimeFormatValidIns<MODULE_TIME_TYPE_OPEN>(0, 0);
	std::cout << IsTimeFormatValid(MODULE_TIME_TYPE_OPEN, 0, 0);
}

BOOST_AUTO_TEST_CASE(my_test32)
{
	std::cout << "\n\n test 32\n";

	//Ԥ����������� # �����ں궨���н����ַ����� ## ճ�ϲ�����
#define STRINGIFY(x) #x
#define CONCAT(x, y) x##y
	const char* str = STRINGIFY(Hello);
	std::cout << str << std::endl;
	int xy = CONCAT(10, 20);
	std::cout << xy << std::endl;
}

////////////////////////////my test 33 /////////////////
template <int id>
struct name_traits
{
	static const char* name()
	{
		return "";
	}
};

#define DEF_LUA_INT(x)             \
enum                           \
{                              \
	x = __LINE__ - id_start_xx \
};                             \
template <>                    \
struct name_traits<x>          \
{                              \
	static const char* name()  \
	{                          \
		return #x;             \
	}                          \
};

#define LUA_NAME(i) g_luaname[ i ]

enum
{
	id_start_xx = __LINE__ + 1
};
DEF_LUA_INT(AAA)

DEF_LUA_INT(BBB)
enum
{
	LUA_DEF_LIMITED = __LINE__ - id_start_xx
};
constexpr int DEPTH_MAX = 500;
static const char* g_luaname[LUA_DEF_LIMITED];

template <size_t nBegin, size_t nEnd>
struct LOOP_RANGE
{
	static void genname()
	{
		if constexpr (nBegin >= nEnd)
		{
			LOOP_RANGE<nBegin - 1, nEnd>::genname();
			g_luaname[nBegin - 1] = name_traits<nBegin - 1>::name();
			std::cout << "g_luaname["<< nBegin - 1 << "] = " << g_luaname[nBegin - 1] << std::endl;
		}
	}
};

template <size_t i>
struct LOOP_DRIVE
{
	static void genname()
	{
		if constexpr (i > DEPTH_MAX)
		{
			LOOP_DRIVE<i - DEPTH_MAX - 1>::genname();
			LOOP_RANGE<i, i - DEPTH_MAX>::genname();
		}
		else
		{
			LOOP_RANGE<i, 1>::genname();
		}
	}
};

class CLuaLogicMgr
{
public:

	INT64 GetLuaInt(int nIndex)
	{
		if (nIndex < 0 || nIndex > LUA_DEF_LIMITED)
		{
			std::cout << "���LUA�ű�ֵʧ��,�������� \n";
			return 0;
		}
		return m_LuaIntArray[nIndex];
	}

	bool Load_All_Lua_Int()
	{
		LOOP_DRIVE<LUA_DEF_LIMITED>::genname();
		m_LuaIntArray.resize(LUA_DEF_LIMITED);

		for (int i = 0; i < LUA_DEF_LIMITED; ++i)
		{
			const char* LuaName = LUA_NAME(i);

			if (LuaName == NULL || (LuaName != NULL && strlen(LuaName) == 0))
				continue;

			m_LuaIntArray[i] = i;
		}

		return true;
	}
private:
	std::vector<INT64> m_LuaIntArray;
};

BOOST_AUTO_TEST_CASE(my_test33)
{
	std::cout << "\n\n test 33\n";

	std::cout<< id_start_xx << std::endl;
	std::cout << LUA_DEF_LIMITED << std::endl;

	CLuaLogicMgr mgr;
	mgr.Load_All_Lua_Int();
	std::cout <<"AAA:" << mgr.GetLuaInt(AAA) << std::endl;
	std::cout << "BBB:" << mgr.GetLuaInt(BBB) << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()