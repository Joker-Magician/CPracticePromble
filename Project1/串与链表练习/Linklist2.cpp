#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}Node,*linklist;

linklist CreateList()
{
	int d;
	linklist L;
	Node* p, * s;
	L = (linklist)malloc(sizeof(Node));
	L->next = NULL;
	printf("please input the integer!(0---return):");
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
		printf("please input the integer!(0---return):");
		scanf("%d", &d);
	}
	return L;
}

linklist Mergelinklist(linklist LA, linklist LB)
{
	Node* pa, * pb;
	linklist LC, r;

	pa = LA->next;
	pb = LB->next;
	LC = LA;
	LC->next = NULL;
	r = LC;

	while (pa != NULL && pb != NULL)
	{
		if (pa->data <= pb->data) {
			r->next = pa; r = pa; pa = pa->next;
		}
		else {
			r->next = pb; r = pb; pb = pb->next;
		}
	}
	if (pa)
		r->next = pa;
	else
		r->next = pb;
	free(LB);
	return LC;
}