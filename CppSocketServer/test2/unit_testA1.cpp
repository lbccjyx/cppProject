﻿// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>
#include <set>
using namespace std;

BOOST_AUTO_TEST_SUITE(tests_suit)

// 求最大公约数  
// 例子 15, 18 -> (15,18)->(18,15%18) (18, 15) -> (15, 18%15) (15, 3) -> (3, 3%15) (3,3)->(3, 0%3) (3, 0) -> 3 
// 例子 4, 6  ->  (4, 6) -> (6, 4%6) (6, 4) -> (4, 6%4) (4, 2) -> (2, 4%2) (2, 2) -> (2, 0) ->2
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}


BOOST_AUTO_TEST_CASE(my_testA4) {
	std::cout << "\n\n1:勾股数 \n";
/*
如果三个正整数A、B、C ，A² + B² = C² 则为勾股数，
如果ABC之间两两互质，即A与B，A与C，B与C均互质没有公约数，则称其为勾股数元组。
请求出给定 n ~ m 范围内所有的勾股数元组

1：sqrt计算开根号2
2：gcd函数是取最大公因数 只要是1 那就没有公约数
*/
	int n = 1, m = 20;
	int found = 0;

	for (int i = n; i <= m; i++) {
		for (int j = i + 1; j <= m; j++) {

			double k = sqrt(i * i + j * j);
			// 判断k是否整数
			if (k > m ) {
				// 这里跳出可以省略很多后面的越界
				break;
			}

			// 只取整数的勾股数
			if(k != int(k))
				continue;

			// 找到C^2 再找两两的公因数为1即互质
			if (gcd(i, j) == 1 && gcd(j, k) == 1) {
				cout << i << " " << j << " " << k << endl;
				found = 1;
			}
		}
	}
	if (!found) {
		cout << "Na" << endl;
	}
	
}

// 2 整数对最小和
// 3 TLV编码
// 6 身高排序 
// 题目0007-单词反转 
// 题目0010-数据分类
// 最小步骤数



BOOST_AUTO_TEST_CASE(my_testA5) {
	std::cout << "\n\n4:猴子爬山 \n";
	/*
	* 途中经过一个有n个台阶的阶梯， 每一次只跳1步或3步。试问？猴子通过这个阶梯有多少种不同的跳跃方式
	*/
	int n = 50;
	// 列出前n种可能后 找到规律。规律 f(n) = f(n-1) + f(n-3)
	int step1 = 1, step2 = 1, step3 = 2, step4 = 0;	
	for (int i = 4; i <= n; i++) {
		step4 = step3 + step1; // f(n) = f(n-1) + f(n-3)
		step1 = step2;
		step2 = step3;
		step3 = step4;
	}
	std::cout << "50级台阶共有 "<<step4 << std::endl;

}


BOOST_AUTO_TEST_CASE(my_testA6) {
	std::cout << "\n\n5:任务调度 \n";
	// 最大任务数
	int nMax = 4;
	
	//每秒新增任务数组，
	int arrTask[] = { 5, 4, 1, 1, 1 };

	int arrLen = sizeof(arrTask) / sizeof(arrTask[0]);
	//执行完所有任务需要多少秒
	int nTmp = 0;
	int nTime = 0;
	for (int i = 0; i< arrLen; i++)
	{
		nTime++;
		if (arrTask[i] > nMax)
		{
			nTmp += (arrTask[i] - nMax);
			continue;
		}
		
		if(nTmp > 0 && arrTask[i] < nMax)
		{
			nTmp += (arrTask[i] - nMax);
		}
	}
	if(nTmp > 0)
		nTime += nTmp/nMax;

	cout<<"执行完所有任务需要"<<nTime<<"秒" << endl;
}

// 参数1 数组 
// 参数2 最大资金
// 参数3 选取的商品数量
pair<int, vector<int>> getMaxSum(vector<int>& arrCost, int nMoney, int selectCount) {
	int n = arrCost.size();

	// 创建一个三维数组来存储动态规划的结果
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(nMoney + 1, vector<int>(selectCount + 1, 0)));
	vector<vector<vector<vector<int>>>> selectedItems(n + 1, vector<vector<vector<int>> > (nMoney + 1, vector<vector<int>>(selectCount + 1)));

	// 填充动态规划数组
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= nMoney; ++j) {
			for (int k = 1; k <= min(i, selectCount); ++k) {
				// 如果当前商品的价格小于等于当前的资金，考虑是否选择当前商品
				if (arrCost[i - 1] <= j) {
					// 选择当前商品和不选择当前商品的两种情况，取最大值
					if (dp[i - 1][j][k] < dp[i - 1][j - arrCost[i - 1]][k - 1] + arrCost[i - 1]) 
					{
						dp[i][j][k] = dp[i - 1][j - arrCost[i - 1]][k - 1] + arrCost[i - 1];
						selectedItems[i][j][k] = selectedItems[i - 1][j - arrCost[i - 1]][k - 1];
						selectedItems[i][j][k].push_back(arrCost[i - 1]);
					}
					else 
					{
						dp[i][j][k] = dp[i - 1][j][k];
						selectedItems[i][j][k] = selectedItems[i - 1][j][k];
					}
				}
				else 
				{
					// 当前商品的价格大于当前的资金，不能选择当前商品
					dp[i][j][k] = dp[i - 1][j][k];
					selectedItems[i][j][k] = selectedItems[i - 1][j][k];
				}
			}
		}
	}

	// 获取构成最大和的商品价格列表
	vector<int> items = selectedItems[n][nMoney][selectCount];

	return make_pair(dp[n][nMoney][selectCount], items);
}

BOOST_AUTO_TEST_CASE(my_testA7) {
	std::cout << "\n\n7:双十一 \n";
	// 所以他决定从众多心意商品中购买3件，而且想尽可能的花完资金，
	//单个商品的价格；
	vector<int> arrCost = { 23, 26, 36, 27, 11 ,4, 5, 1, 2 };
	// 资金
	int nMoney = 109;

	//std::sort(arrCost.begin(), arrCost.end(), [](int a, int b) { return a > b; });
	//auto funcPrintInt = [](int x) { std::cout << x << " "; };
	//std::for_each(arrCost.begin(), arrCost.end(), funcPrintInt);

	// 不是找到最贵的三个 可能是找到最贵的和最便宜的合起来最贵的。

	pair<int, vector<int>> result = getMaxSum(arrCost, nMoney, 6);

	cout << "最大和为: " << result.first << endl;
	cout << "构成最大和的商品价格列表为: ";
	for (int item : result.second) {
		cout << item << " ";
	}
	cout << endl;

}


BOOST_AUTO_TEST_CASE(my_testA8) {
	std::cout << "\n\n9:找字符 \n";
	// 给定两个字符串，从字符串2中找出字符串1中的所有字符， 去重并按照ASCII码值从小到大排列
	string str1 = "fach";
	string str2 = "bbaaccedfg";
	string unique_chars;

	// 遍历字符串2，检查每个字符是否在字符串1中
	for (char ch : str2) {
		if (str1.find(ch) != string::npos && unique_chars.find(ch) == string::npos) {
			unique_chars += ch;
		}
	}

	// 按照ASCII码值从小到大排序
	sort(unique_chars.begin(), unique_chars.end());

	// 输出结果
	cout << "在字符串2中找到的字符串1中的字符并按ASCII码值排序为: " << unique_chars << endl;
}

static int nArr[] = { 7, 5, 9, 4, 2, 6, 8, 3, 5, 4, 3, 9};
static int nArrLen = sizeof(nArr) / sizeof(nArr[0]);
int nStep = 0;
int StepNext(int nCurPos, int nNextPos)
{
	int nNextStep = nArr[nCurPos];
	if (nNextPos == nArrLen - 1)
	{
		return nStep;
	}
	else if (nNextPos < nArrLen - 1)
	{
		nStep++;
		return StepNext(nNextPos, nNextPos + nNextStep);
	}
	else
	{
		return -1;
	}
}

BOOST_AUTO_TEST_CASE(my_testA9) {
	std::cout << "\n\n10:求从第一个成员开始正好走到数组最后一个成员所使用的最小步骤数 \n";
	/*
要求：

第一步，必须从第一元素起，且1 <= 第一步步长 < len / 2 (len为数组长度)
从第二步开始只能以所在成员的数字走相应的步数，不能多不能少，如果目标不可达返回-1，只输出最小的步骤数量
只能向数组的尾部走不能向回走
	*/
	for (int i = 0; i < nArrLen / 2; i++)
	{
		nStep = 1;
		std::cout<<StepNext( i, i)<<"\t";
	}

}


BOOST_AUTO_TEST_CASE(my_testA10) {

	std::cout << "\n\n11:磁盘排序 \n";
	/*
磁盘的容量单位常用的有M、G、T
他们之间的换算关系为1T =1024G，1G=1024M
现在给定n块磁盘的容量，请对他们按从小到大的顺序进行稳定排序
	*/
	std::string strArr[] = { "1T4M1T4M", "20M", "3G", "10G6T", "3M12G9M"};
	auto pureCaculateSize = [](const char* str, int nLen)->INT64
		{
			int nNum = 0;
			for (int i = 0; i<nLen; i++) {
				char ch = str[i];
				if (std::isdigit(ch))
				{
					nNum = nNum * 10 + ch - '0';
				}
				else if (ch == 'G')
				{
					nNum = nNum * 1024;
				}
				else if (ch == 'T')
				{
					nNum = nNum * 1024 * 1024;
				}
			}
			return nNum;
		};
	auto funcSeparateAndGetNum = [&](std::string& str)->INT64
		{
			INT64 nNum = 0;
			while (!str.empty())
			{
				for (int i = 0; i < str.length(); i++) {
					if (std::isalpha(str[i]))
					{
						// 截取前i个到strTmp
						std::string strTmp = str.substr(0, i + 1);
						nNum += pureCaculateSize(strTmp.c_str(), strTmp.length());
						// 删除strTmpA的前i个字符
						str = str.substr(i + 1);
						break;
					}
				}
			}
			return nNum;
		};
	auto CompareFunc = [&](const std::string& strA, const std::string& strB)
		{
			std::string strTmpA = strA;
			std::string strTmpB = strB;
			INT64 nA = 0, nB = 0;
			return (funcSeparateAndGetNum(strTmpA) < funcSeparateAndGetNum(strTmpB));
		};
	CompareFunc(strArr[0], strArr[1]);
	std::sort(strArr, strArr + 5, CompareFunc);
	for(auto str : strArr)
		std::cout << str << std::endl;
}

std::pair<int, int> minAbsSumPair(std::vector<int>& nums) {
	// 先将数组排序
	std::sort(nums.begin(), nums.end());

	int minAbsSum = INT_MAX; // 初始最小绝对值
	std::pair<int, int> minPair; // 记录最小绝对值对应的两个数

	// 双指针
	int left = 0;
	int right = nums.size() - 1;

	while (left < right) {
		int sum = nums[left] + nums[right];
		int absSum = std::abs(sum); // 当前和的绝对值

		// 如果当前绝对值更小，则更新最小绝对值和对应的两个数
		if (absSum < minAbsSum) {
			minAbsSum = absSum;
			minPair = { nums[left], nums[right] };
		}

		// 根据当前和的正负移动指针
		if (sum < 0) {
			left++;
		}
		else if (sum > 0) {
			right--;
		}
		else {
			// 如果和为零，直接返回
			return minPair;
		}
	}

	return minPair;
}
BOOST_AUTO_TEST_CASE(my_testA11) {
	std::cout << "\n\n12:乱序整数序列两数之和绝对值最小 \n";
	std::vector<int> nums{ -1, -3, 7 ,5 ,11 ,15 };
	auto pairA = minAbsSumPair(nums);
	std::cout << "两数之和绝对值最小的数对为: " << pairA.first << " " << pairA.second << std::endl;
}


BOOST_AUTO_TEST_CASE(my_testA12) {
	std::cout << "\n\n13:最少颜色 \n";
	/*
同种颜色的所有数都可以被这个颜色中最小的那个数整除， 算算最少需要多少种颜色
	*/
	std::vector<int> nums{2, 3, 4, 7, 8, 9};
	std::vector<int> smallNums;

	for (int i = 0; i < nums.size(); i++)
	{
		if(smallNums.empty())
		{
			smallNums.push_back(nums[i]);
			continue;
		}

		int found = 0;
		for (int j : smallNums)
		{
			// 判断能否被j整除
			if ( nums[i] % j == 0)
			{
				found = 1;
				break;
			}
		}
		if(!found)
			smallNums.push_back(nums[i]);
	}

	for (int j : smallNums)
	{
		std::cout << j << " ";
	}
}


BOOST_AUTO_TEST_CASE(my_testA13) {
	
	std::cout << "\n\n14:输入法提示词 \n";
	std::string str[] = { "hello", "furthest ", "front ", "abcd", "abcde" };

	std::string prefix = "f";

	//遍历蛮没有性能的 可能用hash表
	for (auto s : str)
	{
		if(s.starts_with(prefix))
			std::cout << s << std::endl;
	}

	std::unordered_map<char, std::list<std::string>> hashTable;
	for (auto s : str) {
		hashTable[s[0]].push_back(s);
	}
	// 查找
	char prefixFirstChar = prefix[0];
	auto it = hashTable.find(prefixFirstChar);
	if (it != hashTable.end()) {
		for (auto s : it->second) {
			if (s.starts_with(prefix))
				std::cout << s << std::endl;
		}
	}
}

void printConsecutiveSum(int start, int end) {
	for (int i = start; i < end; ++i) {
		std::cout << i;
		if (i < end - 1) {
			std::cout << " + ";
		}
	}
	std::cout << std::endl;
}
int countAndPrintConsecutiveSum(int target) {
	int count = 0;
	int start = 1, end = 1;
	int sum = 0;
	// sum 没超过就加后面的 sum 超过就减前面的
	while (start <= target / 2) {
		if (sum < target) {
			sum += end;
			end++;
		}
		else if (sum > target) {
			sum -= start;
			start++;
		}
		else {
			count++;
			printConsecutiveSum(start, end);
			sum -= start;
			start++;
		}
	}

	return count;
}

BOOST_AUTO_TEST_CASE(my_testA14) {

	std::cout << "\n\n15:整数分解 \n";
	/*
一个整数可以由连续的自然数之和来表示。
给定一个整数，计算该整数有几种连续自然数之和的表达式，
	*/
	int target = 4;
	int result = countAndPrintConsecutiveSum(target);
	std::cout << "Number of expressions for " << target << ": " << result << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

