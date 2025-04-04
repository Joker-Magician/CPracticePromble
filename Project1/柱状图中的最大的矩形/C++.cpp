#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#include<cmath>
#include<stack>
/*��״ͼ�����ľ���*/
/*	���� n ���Ǹ�������������ʾ��״ͼ�и������ӵĸ߶ȡ�ÿ�����ӱ˴����ڣ��ҿ��Ϊ 1 ��
	���ڸ���״ͼ�У��ܹ����ճ����ľ��ε���������	*/

//�ǳ��������Ŀ

using namespace std;

//����һ�������ⷨ	ֱ�Ӵ��м���������ɢ
class Solution_1 {
public:
	int largestRectangleArea(std::vector<int>& heights){
		int n = heights.size();		//��ȡԪ�ص�����
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
