#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PARTS 100	// 定义最大分割部分数量
#define MAX_LENGTH 100	// 定义结果字符串的最大长度

/*给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为 更加简洁的规范路径。
		在 Unix 风格的文件系统中规则如下：
	1.一个点 '.' 表示当前目录本身。
	2.此外，两个点 '..' 表示将目录切换到上一级（指向父目录）。
	3.任意多个连续的斜杠（即，'//' 或 '///'）都被视为单个斜杠 '/'。
	4.任何其他格式的点（例如，'...' 或 '....'）均被视为有效的文件/目录名称。
		返回的 简化路径 必须遵循下述格式：
	1.始终以斜杠 '/' 开头。
	2.两个目录名之间必须只有一个斜杠 '/' 。
	3.最后一个目录名（如果存在）不能 以 '/' 结尾。
	4.此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
返回简化后得到的 规范路径 。*/

//方法一(为了性能牺牲了可读性)：

char** split(const char* s, char delim, int* returnSize)
{
	int n = strlen(s); // 获取字符串长度
	char** ans = (char**)malloc(sizeof(char) * n); // 分配内存存储结果
	int pos = 0; // 当前处理的位置
	int curr = 0; // 当前子字符串的起始位置
	int len = 0; // 子字符串的数量

	while (pos < n) {
		// 跳过连续的分隔符
		while (pos < n && s[pos] == delim) {
			++pos;
		}
		curr = pos;
		// 找到下一个分隔符的位置
		while (pos < n && s[pos] != delim) {
			++pos;
		}
		// 提取子字符串并存储
		if (curr < n) {
			ans[len] = (char*)malloc(sizeof(char) * (pos - curr + 1));
			strncpy(ans[len], s + curr, pos - curr);
			ans[len][pos - curr] = '\0';
			++len;
		}
	}
	*returnSize = len; // 返回子字符串的数量
	return ans;
}

// 简化路径
char* simplifyPath_1(char* path) {
	int namesSize = 0; // 子字符串的数量
	int n = strlen(path); // 路径字符串的长度
	char** names = split(path, '/', &namesSize); // 按 '/' 分割路径
	char** stack = (char**)malloc(sizeof(char*) * namesSize); // 用栈存储有效的目录名
	int stackSize = 0; // 栈的大小
	for (int i = 0; i < namesSize; ++i) {
		if (!strcmp(names[i], "..")) { // 遇到 ".." 返回上一级目录
			if (stackSize > 0) {
				--stackSize;
			}
		}
		else if (strcmp(names[i], ".")) { // 忽略 "."
			stack[stackSize] = names[i];
			++stackSize;
		}
	}
	char* ans = (char*)malloc(sizeof(char) * (n + 1)); // 分配内存存储结果路径
	int curr = 0; // 当前处理的位置
	if (stackSize == 0) {
		ans[curr] = '/'; // 如果栈为空，返回根目录
		++curr;
	}
	else {
		for (int i = 0; i < stackSize; ++i) {
			ans[curr] = '/'; // 添加斜杠
			++curr;
			strcpy(ans + curr, stack[i]); // 添加目录名
			curr += strlen(stack[i]);
		}
	}
	ans[curr] = '\0'; // 结束字符串
	for (int i = 0; i < namesSize; ++i) {
		free(names[i]); // 释放内存
	}
	free(names);
	free(stack);
	return ans;
}

//方法二：
char* simplifyPath_2(char* path) {
	char* parts[MAX_PARTS];		// 用于存储分割后的路径部分
	char* ans[MAX_PARTS];		// 用于存储最终简化后的路径部分
	int part_count = 0;			// 记录分割后的路径部分数量
	int ans_count = 0;			// 记录最终简化后的路径部分数量

// 使用 strtok 函数将路径按 '/' 分割成多个部分
// strtok 函数会修改原始字符串，每次调用返回一个分割后的部分，直到返回 NULL 表示分割结束
	char* token = strtok(path, "/");
	while (token != NULL && part_count < MAX_PARTS) {
		parts[part_count++] = token;
		token = strtok(NULL, "/");
	}

	for (int i = 0; i < part_count; i++) {
		// 如果部分为空字符串或者是 '.'，表示当前目录，直接跳过
		if (strcmp(parts[i], "") == 0 || strcmp(parts[i], ".") == 0) {
			continue;
		} // 如果部分是 '..'，表示返回上一级目录
		else if (strcmp(parts[i], "..") == 0) {
			if (ans_count > 0) {
				ans_count--;
			}
		} // 其他情况，将该部分添加到 ans 数组中
		else {
			ans[ans_count++] = parts[i];
		}
	}

	char* result = (char*)malloc(MAX_LENGTH * sizeof(char));
	result[0] = '/';
	int index = 1;

	for (int i = 0; i < ans_count; i++) {	// 如果不是第一个部分，在前面添加 '/'
		if (i > 0) {
			result[index++] = '/';
		}
		strcpy(result + index, ans[i]);	// 将当前部分复制到结果字符串中
		index += strlen(ans[i]);		// 更新索引，跳过刚复制的部分
	}
	result[index] = '\0'; // 在结果字符串末尾添加字符串结束符

	return result;
}
