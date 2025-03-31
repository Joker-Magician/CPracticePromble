#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
/*����һ��ֻ���� '(' �� ')' ���ַ������ҳ����Ч����ʽ��ȷ�������������Ӵ��ĳ��ȡ�*/
#define Maxstk 100
int longestValidParentheses(char* s) {
	int maxans = 0, n = strlen(s);
	int stk[Maxstk], top = -1;		//ע�⣺�ڲ���֧��δ�������ռ��еı������п�ʹ��stk[n+1]�����ռ�
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