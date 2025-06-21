#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node, * linklist;

linklist CreateList()
{
	int d;
	linklist L;
	Node* p, * s;
	L = (linklist)malloc(sizeof(Node));
	L->next = NULL;
	printf("please input the integer!(0---return): ");
	scanf("%d", &d);
	while (d != 0)
	{
		s = (Node*)malloc(sizeof(Node));
		s->data = d;
		p = L;
		while (p->next != NULL) {
			if (p->next->data < d)

				p = p->next;
			else break;
		}
		s->next = p->next;
		p->next = s;
		printf("please input the integer!(0---return): ");
		scanf("%d", &d);
	}
	return L;
}

linklist Mergelinklist(linklist LA, linklist LB)
{/*将递增有序的单链表LA和LB合并成一个递增有序的单链表LC*/
	Node* pa,* pb;
	linklist LC, r;
	/*将LC初始置空表。pa和pb分别指向两个单链表LA和LB中的第一个结点,r初值为LC*/
	pa = LA->next;
	pb = LB->next;
	LC = LA;
	LC->next = NULL;
	r = LC;										/*初始化操作*/
	/*当两个表中均未处理完时，比较选择将较小值结点插入到新表LC中。*/
	while (pa != NULL && pb != NULL)
	{
		if (pa->data <= pb->data) {
			r->next = pa; r = pa; pa = pa->next;
		}
		else {
			r->next = pb; r = pb; pb = pb->next;
		}
	}
		if (pa)	/*若表LA未完，将表LA中后续元素链到新表LC表尾*/
			r->next = pa;
		else   /*否则将表LB中后续元素链到新表LC表尾*/
			r->next = pb;

		free(LB);
		return LC;
}