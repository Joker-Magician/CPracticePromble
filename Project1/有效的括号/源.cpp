#define _CRT_SECURE_NO_WARNINGS
/*  ����һ��ֻ���� '('��')'��'{'��'}'��'['��']' ���ַ��� s ���ж��ַ����Ƿ���Ч��
    ��Ч�ַ��������㣺
    1.�����ű�������ͬ���͵������űպϡ�
    2.�����ű�������ȷ��˳��պϡ�
    3.ÿ�������Ŷ���һ����Ӧ����ͬ���͵������š�*/
//֪ʶ�㣺ջ
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Maxstk 100
char pairs(char a) {
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}

bool isValid(char* s) { //`isValid`���������ж��ַ���`s`�Ƿ�����Ч�������ַ�����
    int n = strlen(s);
    if (n % 2 == 1) {
        return false;
    }
    int stk[Maxstk], top = 0;
    for (int i = 0; i < n; i++) {
        char ch = pairs(s[i]);  //����������ţ�ͨ��`pairs`�����жϣ�������ջ���Ƿ��Ƕ�Ӧ�������ţ���������򷵻�`false`�����򵯳�ջ��Ԫ�ء�
        if (ch) {
            if (top == 0 || stk[top - 1] != ch) {
                return false;
            }
            top--;
        }
        else {      //����������ţ�����ѹ��ջ�С�
            stk[top++] = s[i];
        }
    }
    return top == 0;        //�����ջ�Ƿ�Ϊ�գ����Ϊ���򷵻�`true`�����򷵻�`false`��
}

int main() {
    char inputs[Maxstk];
    while (1) {
        printf("s = ");
        scanf("%s", inputs);
        bool result = isValid(inputs);
        printf("%s\n", result ? "true" : "false");
    }
    return 0;
}