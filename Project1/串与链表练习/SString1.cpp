#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct
{
	char ch[100];
	int len;
}SString;

int StrInsert(SString* s, int pos, SString t)
{/*在串s中下标为pos的字符之前插入串t */
	int i;
	if (pos < 0 || pos > s->len)
		return 0;	/*插入位置不合法*/
	if (s->len + t.len <= 100)
	{	/*插入后串长≤MAXLEN*/
		for (i = s->len + t.len - 1; i >= t.len + pos; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = s->len + t.len;
	}
	else if (pos + t.len <= 100)
	{	/*插入后串长>MAXLEN,但串t的字符序列可以全部插入*/
		for (i = 100 - 1; i > t.len + pos - 1; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	else
	{	/*插入后串长>MAXLEN,并且串t的部分字符也要舍弃*/
		for (i = 0; i < 100 - pos; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	return 1;
}

int StrIndex(SString s, int pos, SString t)
{	/*求从主串s的下标pos起，串t第一次出现的位置，成功返回位置序号，不成功返回-1*/
	int i, j, start;
	if (t.len == 0)
		return 0;	/* 模式串为空串时，是任意串的匹配串 */
	start = pos;	/* 主串从pos开始，模式串从头（0）开始 */
	i = start;
	j = 0;
	while (i < s.len && j < t.len)
	{
		if (s.ch[i] == t.ch[j])
		{
			i++;
			j++;
		}	/* 当前对应字符相等时推进 */
		else
		{
			start++;	/* 当前对应字符不等时回溯 */
			i = start;	/* 主串从start+1开始，模式串从头（0）开始*/
			j = 0;
		}
		if (j >= t.len)
			return start;	/* 匹配成功时，返回匹配起始位置 */
		else
			return -1;	/* 匹配不成功时，返回-1 */
	}
}