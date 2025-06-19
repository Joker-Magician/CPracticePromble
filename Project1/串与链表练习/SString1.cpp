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