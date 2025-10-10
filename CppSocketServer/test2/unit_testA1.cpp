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

		int left = 0, right = height.size() - 1;
		int left_max = 0, right_max = 0;
		int water = 0;

		while (left < right) {
			if (height[left] < height[right]) {
				// 左边较矮，处理左边
				if (height[left] >= left_max) {
					left_max = height[left];  // 更新左边最大值
				}
				else {
					water += left_max - height[left];  // 接雨水
				}
				left++;
			}
			else {
				// 右边较矮，处理右边
				if (height[right] >= right_max) {
					right_max = height[right];  // 更新右边最大值
				}
				else {
					water += right_max - height[right];  // 接雨水
				}
				right--;
			}
		}

		return water;
	}

	// 无重复字符的最长子串
	static int lengthOfLongestSubstring(string s) {
		// 	给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
		std::unordered_set<char> char_set;
		int max_len = 0;
		int nTmpStart = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (char_set.contains(s[i]))
			{
				max_len = max(max_len, (int)char_set.size());
				char_set.clear();  // 清空之前的字符

				i = nTmpStart;
			}
			else
			{
				if(char_set.empty())
					nTmpStart = i;

				char_set.insert(s[i]);
			}
		}
		max_len = max(max_len, (int)char_set.size());
		return max_len;
	}
	int lengthOfLongestSubstring2(string s) 
	{
		// 	给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
		std::unordered_set<char> char_set;
		int max_len = 0;
		int left = 0;  // 滑动窗口的左边界

		for (int right = 0; right < s.size(); right++) {
			// 如果当前字符已经在集合中，移动左边界直到移除重复字符
			while (char_set.count(s[right])) {
				char_set.erase(s[left]);
				left++;
			}

			// 将当前字符加入集合
			char_set.insert(s[right]);

			// 更新最大长度
			max_len = max(max_len, right - left + 1);
		}

		return max_len;
	}

	// 找到字符串中所有字母异位词
	vector<int> findAnagrams(string s, string p) {
		// 找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。
		vector<int> result;
		int n = s.length();
		int m = p.length();
		unordered_set<char> p_set(p.begin(), p.end());
		map<int, string> map_sub_strs;
		string pSort = p;
		sort(pSort.begin(), pSort.end());  // 排序后的p


		for (int i = 0; i < n; i++)
		{
			if (p_set.contains(s[i]))
			{
				map_sub_strs.insert(pair<int, string>(i, s.substr(i, m)));
			}
		}

		for (auto& [index, sub_str] : map_sub_strs)
		{
			sort(sub_str.begin(), sub_str.end());  // 排序后的sub_str
			if(sub_str == pSort)
				result.push_back(index);
		}

		return result;

	}
	vector<int> findAnagrams2(string s, string p)
	{
		vector<int> result;
		int n = s.length();
		int m = p.length();

		if (n < m) return result;

		// 统计 p 中每个字符的频率
		vector<int> p_count(26, 0);
		vector<int> window_count(26, 0);

		for (char c : p) {
			p_count[c - 'a']++;
		}

		// 初始化第一个窗口
		for (int i = 0; i < m; i++) {
			window_count[s[i] - 'a']++;
		}

		// 检查第一个窗口
		if (window_count == p_count) {
			result.push_back(0);
		}

		// 滑动窗口
		for (int i = m; i < n; i++) {
			// 移除左边界的字符
			window_count[s[i - m] - 'a']--;
			// 添加右边界的字符
			window_count[s[i] - 'a']++;

			// 检查当前窗口是否为异位词
			if (window_count == p_count) {
				result.push_back(i - m + 1);
			}
		}

		return result;
		
	}

	// 和为 K 的子数组
	static int subarraySum(vector<int>& nums, int k) {
		// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
		unordered_map<int, int> mp;
		mp[0] = 1;
		int count = 0, pre = 0;
		for (auto& x : nums) {
			pre += x;
			if (mp.contains(pre - k)) {
				count += mp[pre - k];
			}
			mp[pre]++;
		}
		return count;
	}

	//  滑动窗口最大值
	static vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。 返回 滑动窗口中的最大值 。

		vector<int> result;
		deque<int> dq; // 存储索引，而不是值

		for (int i = 0; i < nums.size(); i++) {
			// 移除超出窗口范围的元素
			if (!dq.empty() && dq.front() == i - k) {
				dq.pop_front();
			}

			// 维护单调递减队列
			while (!dq.empty() && nums[dq.back()] < nums[i]) {
				dq.pop_back();
			}

			dq.push_back(i);

			// 当窗口形成时，添加结果
			if (i >= k - 1) {
				result.push_back(nums[dq.front()]);
			}
		}

		return result;
	}

};

BOOST_AUTO_TEST_CASE(my_testA15) {
	vector<int> a = { 1,3,-1,-3,5,3,6,7 };
	Solution::maxSlidingWindow(a, 3);
}

BOOST_AUTO_TEST_SUITE_END()

