// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "threadForCout.h"
#include "radixsort.h"
#include <boost/progress.hpp>
#include <set>
#include <unordered_set>
using namespace std;

BOOST_AUTO_TEST_SUITE(tests_suit)

class Solution{
public:
	// 两数之和 
	static vector<int> twoSum(vector<int>& nums, int target)
	{
		// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
		// 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
		unordered_map<int, int> num_map; // key: num, value: index

		for (int i = 0; i < nums.size(); i++) {
			int complement = target - nums[i];

			if (!num_map.contains(complement))
			{
				num_map[nums[i]] = i;
			}
			else 
			{
				return { num_map[complement], i };
			}
		}

		return {};
	}

	// 字母异位词分组
	static vector<vector<string>> groupAnagrams(vector<string>& strs) {
		// 字母异位词是通过重新排列不同单词或短语的字母而形成的单词或短语，并使用所有原字母一次。
		// 组合在一起。可以按任意顺序返回结果列表。
		vector<vector<string>> result;
		unordered_map<string, vector<string>> hashTable;

		for (auto s : strs) {
			string sorted_s = s;
			sort(sorted_s.begin(), sorted_s.end());
			hashTable[sorted_s].push_back(s);
		}

		for (auto& [str, vec] : hashTable)
			result.push_back(vec);

		return result;
	}

	// 最长连续序列
	static int longestConsecutive(vector<int>& nums) 
	{
		// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
		std::unordered_set<int> num_set(nums.begin(), nums.end());
		int max_len = 0;

		// 遍历去重后的set
		for (int num : num_set) {
			// 如果此数字之前有数字 说明是连续的 但是无需从这个数字开始计算
			if(num_set.contains(num-1))
				continue;

			int current_num = num;
			int len = 1;

			// 明确地递增和检查
			while (num_set.count(current_num + 1)) {
				current_num++;
				len++;
			}
			
			max_len = max(max_len, len);
		}

		return max_len;
	}

	// 移动零
	void moveZeroes(vector<int>& nums) {
		// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
		// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
		int slow = 0;

		for (int fast = 0; fast < nums.size(); fast++) {
			if (nums[fast] != 0) {
				// 交换非零元素到前面
				swap(nums[slow], nums[fast]);
				slow++;
			}
		}
	}

	// 盛最多水的容器  
	int maxArea(vector<int>& height) 
	{
		// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
		// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
		// 返回容器可以储存的最大水量。
		// 说明：你不能倾斜容器。
		int x = 0;
		int y = height.size() - 1;
		int max_area = 0;

		while (x < y) {
			// 计算当前面积
			max_area = max(max_area, (y - x) * min(height[x], height[y]));

			// 移动较短的那一边
			if (height[x] < height[y]) {
				// 向右寻找更高的左边界
				x++;
			}
			else {
				// 向左寻找更高的右边界
				y--;
			}
		}

		return max_area;
	}

	// 三数之和
	vector<vector<int>> threeSum(vector<int>& nums) {
		// 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
		// 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());  // 先排序

		for (int i = 0; i < nums.size(); i++) {
			// 跳过重复的i
			if (i > 0 && nums[i] == nums[i - 1]) 
				continue;

			int left = i + 1;
			int right = nums.size() - 1;

			while (left < right) {
				int sum = nums[i] + nums[left] + nums[right];

				if (sum == 0) {
					result.push_back({ nums[i], nums[left], nums[right] });

					// 跳过重复的left和right
					while (left < right && nums[left] == nums[left + 1]) left++;
					while (left < right && nums[right] == nums[right - 1]) right--;

					left++;
					right--;
				}
				else if (sum < 0) {
					left++;
				}
				else {
					right--;
				}
			}
		}

		return result;
	}

	// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
	int trap(vector<int>& height) {

	}

};

BOOST_AUTO_TEST_CASE(my_testA15) {
	vector<int> a = { 100, 4, 200, 1, 3, 2 };
	Solution::longestConsecutive(a);
}

BOOST_AUTO_TEST_SUITE_END()

