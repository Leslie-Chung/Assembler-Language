#include<stdio.h>
//����������������бȽ�
int sign()
{
	int a, b, max;
	printf("����������������");
	scanf_s("%d %d", &a, &b);
	max = a;
	_asm {
		mov eax, a
		mov ebx, b
		cmp eax, ebx
		jle SHORT choose1
		mov max, eax
		jmp choose2          //��������ת��������֧��ֹ˳��ִ���޸���ȷ��ֵ
		choose1 :
		mov max, ebx
		choose2 :
	}
	printf("�����з��űȽϵ����ֵΪ��%d", max);
	return 0;
}
int unsign()
{
	unsigned a, b ;
	int max;
	printf("����������������");
	scanf_s("%u %u", &a, &b);
	_asm {
		mov eax, a
		mov ebx, b
		cmp eax, ebx
		jbe SHORT choose1
		mov max, eax
		jmp choose2          //��������ת��������֧��ֹ˳��ִ���޸���ȷ��ֵ
			choose1 :
		mov max, ebx
			choose2:
	}
	printf("�޷��űȽϵ����ֵΪ��%d", max);
	return 0;
}
int main()
{
	char ch;
	printf("�����з��Ż����޷��űȽϣ�y�����з��ţ�n�����޷��ţ���");
	ch = getchar();
	if(ch == 'y')
	{//�з������Ƚ�
		sign();  
	}
	else if (ch == 'n')
	{//�޷������Ƚ�
		unsign();
	}
	return 0;
}