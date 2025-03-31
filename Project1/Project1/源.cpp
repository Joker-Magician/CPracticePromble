#define _CRT_SECURE_NO_WARNINGS
/*  给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
    有效字符串需满足：
    1.左括号必须用相同类型的右括号闭合。
    2.左括号必须以正确的顺序闭合。
    3.每个右括号都有一个对应的相同类型的左括号。*/
//知识点：栈
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

bool isValid(char* s) { //`isValid`函数用于判断字符串`s`是否是有效的括号字符串。
    int n = strlen(s);
    if (n % 2 == 1) {
        return false;
    }
    int stk[Maxstk], top = 0;
    for (int i = 0; i < n; i++) {
        char ch = pairs(s[i]);  //如果是右括号（通过`pairs`函数判断），则检查栈顶是否是对应的左括号，如果不是则返回`false`，否则弹出栈顶元素。
        if (ch) {
            if (top == 0 || stk[top - 1] != ch) {
                return false;
            }
            top--;
        }
        else {      //如果是左括号，则将其压入栈中。
            stk[top++] = s[i];
        }
    }
    return top == 0;        //最后检查栈是否为空，如果为空则返回`true`，否则返回`false`。
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