// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <string>

BOOST_AUTO_TEST_SUITE(tests_suit)

template <int id>
struct name_traits
{
	static constexpr const char* const name() { return ""; }
};

#define DEF_LUA_INT(x)                           \
	enum                                         \
	{                                            \
		x = __LINE__ - id_start_xx               \
	};                                           \
	template <>                                  \
	struct name_traits<x>                        \
	{                                            \
		static constexpr const char* const name() { return #x; } \
	};

template <std::size_t N, typename Ixs>
struct Names_impl;


template <std::size_t N, std::size_t ...Ix>
struct Names_impl<N, std::index_sequence<Ix...>>
{
	static constexpr const char* const name[N] = { name_traits<Ix>::name()... };
};

template<std::size_t N>
struct LuaNames : Names_impl<N, std::make_index_sequence<N>>
{
	using Names_impl<N, std::make_index_sequence<N>>::name;
};
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


class CLuaLogicMgr
{
public:

	INT64 GetLuaInt(int nIndex)
	{
		if (nIndex < 0 || nIndex > LUA_DEF_LIMITED)
		{
			std::cout << "获得LUA脚本值失败,索引超出 \n";
			return 0;
		}
		return m_LuaIntArray[nIndex];
	}

	bool Load_All_Lua_Int()
	{
		for (int i = 0; i < LUA_DEF_LIMITED; ++i)
		{
			const char* LuaName = LuaNames<LUA_DEF_LIMITED>::name[i];

			if (LuaName == nullptr || (LuaName != nullptr && strlen(LuaName) == 0))
				continue;

			m_LuaIntArray[i] = i;
		}

		return true;
	}
private:
	std::vector<INT64> m_LuaIntArray;
};

BOOST_AUTO_TEST_CASE(my_test34)
{
	std::cout << "\n\n test34\n";
	CLuaLogicMgr mgr;
	mgr.Load_All_Lua_Int();
	std::cout << "AAA:" << mgr.GetLuaInt(AAA) << std::endl;
	std::cout << "BBB:" << mgr.GetLuaInt(BBB) << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()