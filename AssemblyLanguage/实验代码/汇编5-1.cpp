#include <stdio.h>
int count(int num)
{
	int  r = 0, count = 0;
	while (num || r)    //�̺�������Ϊ0
	{
		r = num % 10;    //�õ�ÿһλ��ֵ
		if (r == 7)
		{
			count++;
		}
		num = num / 10;
	}
	printf("7�ڸ�λ�г��ֵĴ���Ϊ��%d",count);
	return 0;
}
int main()
{
	int num;
	printf("������һ��������");
	scanf_s("%d", &num);
	count(num);

	return 0;
}