#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PARTS 100	// �������ָ������
#define MAX_LENGTH 100	// �������ַ�������󳤶�

/*����һ���ַ��� path ����ʾָ��ĳһ�ļ���Ŀ¼�� Unix ��� ����·�� ���� '/' ��ͷ�������㽫��ת��Ϊ ���Ӽ��Ĺ淶·����
		�� Unix �����ļ�ϵͳ�й������£�
	1.һ���� '.' ��ʾ��ǰĿ¼����
	2.���⣬������ '..' ��ʾ��Ŀ¼�л�����һ����ָ��Ŀ¼����
	3.������������б�ܣ�����'//' �� '///'��������Ϊ����б�� '/'��
	4.�κ�������ʽ�ĵ㣨���磬'...' �� '....'��������Ϊ��Ч���ļ�/Ŀ¼���ơ�
		���ص� ��·�� ������ѭ������ʽ��
	1.ʼ����б�� '/' ��ͷ��
	2.����Ŀ¼��֮�����ֻ��һ��б�� '/' ��
	3.���һ��Ŀ¼����������ڣ����� �� '/' ��β��
	4.���⣬·���������Ӹ�Ŀ¼��Ŀ���ļ���Ŀ¼��·���ϵ�Ŀ¼���������� '.' �� '..'����
���ؼ򻯺�õ��� �淶·�� ��*/

//����һ(Ϊ�����������˿ɶ���)��

char** split(const char* s, char delim, int* returnSize)
{
	int n = strlen(s); // ��ȡ�ַ�������
	char** ans = (char**)malloc(sizeof(char) * n); // �����ڴ�洢���
	int pos = 0; // ��ǰ�����λ��
	int curr = 0; // ��ǰ���ַ�������ʼλ��
	int len = 0; // ���ַ���������

	while (pos < n) {
		// ���������ķָ���
		while (pos < n && s[pos] == delim) {
			++pos;
		}
		curr = pos;
		// �ҵ���һ���ָ�����λ��
		while (pos < n && s[pos] != delim) {
			++pos;
		}
		// ��ȡ���ַ������洢
		if (curr < n) {
			ans[len] = (char*)malloc(sizeof(char) * (pos - curr + 1));
			strncpy(ans[len], s + curr, pos - curr);
			ans[len][pos - curr] = '\0';
			++len;
		}
	}
	*returnSize = len; // �������ַ���������
	return ans;
}

// ��·��
char* simplifyPath_1(char* path) {
	int namesSize = 0; // ���ַ���������
	int n = strlen(path); // ·���ַ����ĳ���
	char** names = split(path, '/', &namesSize); // �� '/' �ָ�·��
	char** stack = (char**)malloc(sizeof(char*) * namesSize); // ��ջ�洢��Ч��Ŀ¼��
	int stackSize = 0; // ջ�Ĵ�С
	for (int i = 0; i < namesSize; ++i) {
		if (!strcmp(names[i], "..")) { // ���� ".." ������һ��Ŀ¼
			if (stackSize > 0) {
				--stackSize;
			}
		}
		else if (strcmp(names[i], ".")) { // ���� "."
			stack[stackSize] = names[i];
			++stackSize;
		}
	}
	char* ans = (char*)malloc(sizeof(char) * (n + 1)); // �����ڴ�洢���·��
	int curr = 0; // ��ǰ�����λ��
	if (stackSize == 0) {
		ans[curr] = '/'; // ���ջΪ�գ����ظ�Ŀ¼
		++curr;
	}
	else {
		for (int i = 0; i < stackSize; ++i) {
			ans[curr] = '/'; // ���б��
			++curr;
			strcpy(ans + curr, stack[i]); // ���Ŀ¼��
			curr += strlen(stack[i]);
		}
	}
	ans[curr] = '\0'; // �����ַ���
	for (int i = 0; i < namesSize; ++i) {
		free(names[i]); // �ͷ��ڴ�
	}
	free(names);
	free(stack);
	return ans;
}

//��������
char* simplifyPath_2(char* path) {
	char* parts[MAX_PARTS];		// ���ڴ洢�ָ���·������
	char* ans[MAX_PARTS];		// ���ڴ洢���ռ򻯺��·������
	int part_count = 0;			// ��¼�ָ���·����������
	int ans_count = 0;			// ��¼���ռ򻯺��·����������

// ʹ�� strtok ������·���� '/' �ָ�ɶ������
// strtok �������޸�ԭʼ�ַ�����ÿ�ε��÷���һ���ָ��Ĳ��֣�ֱ������ NULL ��ʾ�ָ����
	char* token = strtok(path, "/");
	while (token != NULL && part_count < MAX_PARTS) {
		parts[part_count++] = token;
		token = strtok(NULL, "/");
	}

	for (int i = 0; i < part_count; i++) {
		// �������Ϊ���ַ��������� '.'����ʾ��ǰĿ¼��ֱ������
		if (strcmp(parts[i], "") == 0 || strcmp(parts[i], ".") == 0) {
			continue;
		} // ��������� '..'����ʾ������һ��Ŀ¼
		else if (strcmp(parts[i], "..") == 0) {
			if (ans_count > 0) {
				ans_count--;
			}
		} // ������������ò�����ӵ� ans ������
		else {
			ans[ans_count++] = parts[i];
		}
	}

	char* result = (char*)malloc(MAX_LENGTH * sizeof(char));
	result[0] = '/';
	int index = 1;

	for (int i = 0; i < ans_count; i++) {	// ������ǵ�һ�����֣���ǰ����� '/'
		if (i > 0) {
			result[index++] = '/';
		}
		strcpy(result + index, ans[i]);	// ����ǰ���ָ��Ƶ�����ַ�����
		index += strlen(ans[i]);		// ���������������ո��ƵĲ���
	}
	result[index] = '\0'; // �ڽ���ַ���ĩβ����ַ���������

	return result;
}
