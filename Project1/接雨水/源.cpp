#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
/*���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��*/
#define Maxstk 999

int trap(int* height, int heightSize)
{
    int n = heightSize;
    if (n == 0) {
        return 0; // ���û�����ӣ�ֱ�ӷ���0
    }
    int ans = 0; // ���ڴ洢���ս��
    int stk[Maxstk], top = 0; // ջ���ڴ洢���ӵ�������top��ʾջ��
    for (int i = 0; i < n; i++) { // ����ÿ������
        while (top && height[i] > height[stk[top - 1]]) { // ��ǰ���Ӹ߶ȴ���ջ�����Ӹ߶�ʱ
            int stk_top = stk[--top]; // ����ջ��Ԫ��
            if (!top) {
                break; // ���ջΪ�գ�����ѭ��
            }
            int left = stk[top - 1]; // ��ȡ��߽����ӵ�����
            int currWidth = i - left - 1; // ���㵱ǰ���
            int currHeight = fmin(height[left], height[i]) - height[stk_top]; // ���㵱ǰ�߶�
            ans += currWidth * currHeight; // ���㵱ǰ�ܽӵ���ˮ�����ۼӵ������
        }
        stk[top++] = i; // ����ǰ���ӵ�������ջ
    }
    return ans; // �������ս��
}