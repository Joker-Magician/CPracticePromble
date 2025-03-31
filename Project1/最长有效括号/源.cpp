#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
/*给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。*/
#define Maxstk 100
int longestValidParentheses(char* s) {
	int maxans = 0, n = strlen(s);
	int stk[Maxstk], top = -1;		//注意：在部分支持未定义具体空间中的编译器中可使用stk[n+1]来开空间
	stk[++top] = -1;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			stk[++top] = i;
		}
		else {
			--top;
			if (top == -1) {
				stk[++top] = i;
			}
			else {
				maxans = fmax(maxans, i - stk[top]);
			}
		}
	}
	return maxans;
}