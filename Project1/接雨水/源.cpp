#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
/*给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。*/
#define Maxstk 999

int trap(int* height, int heightSize)
{
    int n = heightSize;
    if (n == 0) {
        return 0; // 如果没有柱子，直接返回0
    }
    int ans = 0; // 用于存储最终结果
    int stk[Maxstk], top = 0; // 栈用于存储柱子的索引，top表示栈顶
    for (int i = 0; i < n; i++) { // 遍历每个柱子
        while (top && height[i] > height[stk[top - 1]]) { // 当前柱子高度大于栈顶柱子高度时
            int stk_top = stk[--top]; // 弹出栈顶元素
            if (!top) {
                break; // 如果栈为空，跳出循环
            }
            int left = stk[top - 1]; // 获取左边界柱子的索引
            int currWidth = i - left - 1; // 计算当前宽度
            int currHeight = fmin(height[left], height[i]) - height[stk_top]; // 计算当前高度
            ans += currWidth * currHeight; // 计算当前能接的雨水量并累加到结果中
        }
        stk[top++] = i; // 将当前柱子的索引入栈
    }
    return ans; // 返回最终结果
}