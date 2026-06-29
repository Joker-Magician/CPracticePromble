#include<stdio.h>

#include <iostream>

int fib(int n);

int fib(int x) {
    if (x == 1 || x == 2)
        return 1;
    else
        return fib(x - 1) + fib(x - 2);
}

void main()

{

    int n;

    printf("ÇëÊäÈëÏîÊı:");

    scanf("%d", &n);

    fib(n);

}