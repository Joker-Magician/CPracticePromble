#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct
{
	char ch[100];
	int len;
}SString;

int StrInsert(SString* s, int pos, SString t)
{/*�ڴ�s���±�Ϊpos���ַ�֮ǰ���봮t */
	int i;
	if (pos < 0 || pos > s->len)
		return 0;	/*����λ�ò��Ϸ�*/
	if (s->len + t.len <= 100)
	{	/*����󴮳���MAXLEN*/
		for (i = s->len + t.len - 1; i >= t.len + pos; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = s->len + t.len;
	}
	else if (pos + t.len <= 100)
	{	/*����󴮳�>MAXLEN,����t���ַ����п���ȫ������*/
		for (i = 100 - 1; i > t.len + pos - 1; i--)
			s->ch[i] = s->ch[i - t.len];
		for (i = 0; i < t.len; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	else
	{	/*����󴮳�>MAXLEN,���Ҵ�t�Ĳ����ַ�ҲҪ����*/
		for (i = 0; i < 100 - pos; i++)
			s->ch[i + pos] = t.ch[i];
		s->len = 100;
	}
	return 1;
}

int StrIndex(SString s, int pos, SString t)
{	/*�������s���±�pos�𣬴�t��һ�γ��ֵ�λ�ã��ɹ�����λ����ţ����ɹ�����-1*/
	int i, j, start;
	if (t.len == 0)
		return 0;	/* ģʽ��Ϊ�մ�ʱ�������⴮��ƥ�䴮 */
	start = pos;	/* ������pos��ʼ��ģʽ����ͷ��0����ʼ */
	i = start;
	j = 0;
	while (i < s.len && j < t.len)
	{
		if (s.ch[i] == t.ch[j])
		{
			i++;
			j++;
		}	/* ��ǰ��Ӧ�ַ����ʱ�ƽ� */
		else
		{
			start++;	/* ��ǰ��Ӧ�ַ�����ʱ���� */
			i = start;	/* ������start+1��ʼ��ģʽ����ͷ��0����ʼ*/
			j = 0;
		}
		if (j >= t.len)
			return start;	/* ƥ��ɹ�ʱ������ƥ����ʼλ�� */
		else
			return -1;	/* ƥ�䲻�ɹ�ʱ������-1 */
	}
}