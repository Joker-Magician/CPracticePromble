#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int largestRectangleArea_1(int* heights, int heightsSize)
{
	int ans = 0;
	for (int mid = 0; mid < heightsSize; mid++) {
		int height = heights[mid];
		int left = mid, right = mid;
		while (left - 1 >= 0 && heights[left - 1] >= height) {
			left--;
		}
		while (right + 1 < heightsSize && heights[right + 1] >= height) {
			right++;
		}
		ans = fmax(ans, (right - left + 1) * height);
	}
	return ans;
}

#define MaxSize 1000

typedef struct SNode* Stack;
struct SNode {
	int Data;
	struct SNode* Next;
};

Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

int IsEmpty(Stack S)
{
	return (S->Next == NULL);
}

void Push(int item, Stack S)
{
	Stack TmpCell;
	TmpCell = (Stack)malloc(sizeof(struct SNode));
	TmpCell->Data = item;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
}

int Pop(Stack S)
{
	Stack FirstCell;
	int TopElem;
	if (IsEmpty(S)) {
		printf("Õ»¿Õ");
		return -1;
	}
	else {
		FirstCell = S->Next;
		S->Next = FirstCell->Next;
		TopElem = FirstCell->Data;
		free(FirstCell);
		return TopElem;
	}
}

int Top(Stack S)
{
	if (IsEmpty(S)) {
		printf("Õ»¿Õ");
		return -1;
	}
	else {
		return S->Next->Data;
	}
}

int largestRectangleArea_2(int* heights, int heightsSize)
{
	int left[MaxSize], right[MaxSize];

	Stack mono_stack = CreateStack();
	for (int i = 0; i < heightsSize; i++) {
		while (!IsEmpty(mono_stack) && heights[Top(mono_stack)] >= heights[i]) {
			Pop(mono_stack);
		}
		left[i] = (IsEmpty(mono_stack) ? -1 : Top(mono_stack));
		Push(i, mono_stack);
	}

	while (!IsEmpty(mono_stack)) {
		Pop(mono_stack);
	}
	free(mono_stack);

	mono_stack = CreateStack();
	for (int i = heightsSize - 1; i >= 0; i--) {
		while (!IsEmpty(mono_stack) && heights[Top(mono_stack)] >= heights[i]) {
			Pop(mono_stack);
		}
		right[i] = (IsEmpty(mono_stack) ? heightsSize : Top(mono_stack));
		Push(i, mono_stack);
	}

	while (!IsEmpty(mono_stack)) {
		Pop(mono_stack);
	}
	free(mono_stack);

	int ans = 0;
	for (int i = 0; i < heightsSize; i++) {
		ans = fmax(ans, (right[i] - left[i] - 1) * heights[i]);
	}
	return ans;
}