#include <stdio.h>
#include <string.h>
#define MAX 100
int count(int type, int& m, int &n)
{
	if (type == 0)
	{
		m++;
	}
	else if (type == 1)
	{
		n++;
	}
	return 0;
}
int number(char ch)     //aΪ��ǰ�ַ�,�ж��Ƿ�Ϊ����
{
	if (ch >= '0' && ch <= '9')
	{
		return 1;
	}
	else
		return 0;
}
int alph(char ch)       //aΪ��ǰ�ַ�,�ж��Ƿ�Ϊ��ĸ
{
	if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')))
	{
		return 1;
	}
	else
		return 0;
}
int main()
{
	char ch[MAX];
	int length,i,type,m = 0, n = 0;    //type�������ͣ�m�������ָ�����n������ĸ����
	printf("������һ���ַ�����");
	scanf_s("%s", ch, MAX);
	length = strlen(ch);
	for (i = 0; i < length; i++)
	{
		type = 2;
		if (number(ch[i]))
		{
			type = 0;     //˵��������
		}
		else if (alph(ch[i]))
		{
			type = 1;    //˵������ĸ
		}
		count(type,m,n);
	}
	printf("���ָ���Ϊ��%d\n��ĸ����Ϊ��%d", m, n);
	return 0;
}