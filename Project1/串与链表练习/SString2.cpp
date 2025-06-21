#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct
{
	char ch[100];
	int len;
}SString;

int StrInsert(SString* s, int pos, SString t)
{
	int i;
	if (pos < 0 || pos > s->len)
		return 0;
	if (s->len + t.len <= 100)
	{
		for (i = s->len + t.len - 1; i >= t.len + pos; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = s->len + t.len;
	}
	else if (pos + t.len <= 100)
	{
		for (i = 100 - 1; i > t.len + pos; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	else
	{
		for (i = 0; i < 100 - pos; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	return 1;
}