#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#include<cmath>
#include<stack>
/*柱状图中最大的矩形*/
/*	给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
	求在该柱状图中，能够勾勒出来的矩形的最大面积。	*/

//非常经典的题目

using namespace std;

//方法一：暴力解法	直接从中间向两边扩散
class Solution_1 {
public:
	int largestRectangleArea(std::vector<int>& heights){
		int n = heights.size();		//获取元素的数量
		int ans = 0;
		for (int mid = 0; mid < n; ++mid) {
			int height = heights[mid];
			int left = mid, right = mid;
			while (left - 1 >= 0 && heights[left - 1] >= height) {
				--left;
			}
			while (right + 1 < n && heights[right + 1] >= height) {
				++right;
			}
			ans = max(ans, (right - left + 1) * height);
		}
		return ans;
	}
};

class Solution_2 {
public:
	int largestRectangleArea(vector<int>& heights) {
		int n = heights.size();
		vector<int>left(n), right(n);

		stack<int>mono_stack;
		for (int i = 0; i < n; i++) {
			while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
				mono_stack.pop();
			}
			left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
			mono_stack.push(i);
		}

		mono_stack = stack<int>();
		for (int i = n - 1; i >= 0; i--) {
			while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
				mono_stack.pop();
			}
			right[i] = (mono_stack.empty() ? n : mono_stack.top());
			mono_stack.push(i);
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
		}
		return ans;
	}
};
