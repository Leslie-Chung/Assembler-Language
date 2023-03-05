#include <stdio.h>

typedef unsigned int uint32;
typedef unsigned long long uint64;

#define is2exp(x) (((x - 1) & x) == 0)//���x�Ƿ�Ϊ2����������

uint32 log2x(uint32 x)
{
	//��log2(x)�� , x>0
	//��С�ڵ���x��2Ϊ�׵Ķ������������
	int e;
	for (e = 31; e >= 0; e--) {
		if ((int)x < 0) return e;
		x <<= 1;
	}
	return -1;
}

int main()
{         //�޷�����64λ�ı������ڱ������в�û��ȷ��ֵ���ã�unit64��������      ����
	uint32 b, c, i;
	printf("���������(����1)��");
	scanf_s("%d", &b);//������b > 1
	for (i = 0; true; i++) 
	{
		c = b - ((uint64)1 << (32 + i)) % b;
		if (c == b) 
		{
			c = 0;//��ʱbΪ2����������
			break;
		}
		else if (is2exp(c))
		{
			if (log2x(c) <= i) break;
		}
		else 
		{
			if (log2x(c) < i) break;
		}
	}
	uint32 e, db;
	e = log2x(b);
	db = (((uint64)1 << (32 + i)) + c) / b;//��i = e+1ʱȡ����ĵ�32bit
	printf("������Ϊ %d ʱ��ת����ϵ����:\n", b);
	if (i <= e)
	{
		printf("�� = ((uint64)������ * 0x%x) >> %d", db, 32 + i);
	}
	else 
	{
		//i = e + 1ʱ��˵���� e <= ��log2(b)�����޷���ȫ����c*a < 2^(e+32)
		printf("t = ((uint64)������ * 0x%x) >> 32\n", db);
		printf("�� = ((((uint64)������ - t) >> 1) + t) >> %d", e);
	}
	return 0;
}

