#include<stdio.h>
int Sign()
{
	char buff[10];
	int sum, i;
	char ch;
	printf("������10λʮ�������ַ�����");
	for (i = 0; i < 10; i++)
	{
		scanf_s("%c", &buff[i], 1);
	}
	_asm
	{
		xor eax, eax
		xor ecx, ecx
		xor edx, edx    //��Ž����
		lea ebx, buff
		then :
		mov al, BYTE PTR[ebx]
			add ecx, eax
			inc ebx
			inc edx
			cmp edx, 10
			jl then
			sub ecx, 480   //��10�����ݣ���ȥ0��ASCII��  48*10 = 480
			mov sum, ecx
	}
	
	printf("�з��ż���ĺ�Ϊ��%d", sum);
	return 0;
}
int unsign()
{
	char buff[10];
	int  i;
	unsigned sum;
	char ch;
	printf("������10λʮ�������ַ�����");
	for (i = 0; i < 10; i++)
	{
		scanf_s("%c", &buff[i], 1);
	}
	_asm
	{
		xor eax, eax
		xor ecx, ecx
		xor edx, edx    //��Ž����
		lea ebx, buff
		then :
		mov al, BYTE PTR[ebx]
			add ecx, eax
			inc ebx
			inc edx
			cmp edx, 10
			jl then
			sub ecx, 480   //��10�����ݣ���ȥ0��ASCII��  48*10 = 480
			mov sum, ecx
	}
	printf("�޷��ż���ĺ�Ϊ��Ϊ��%u", sum);
	return 0;
}
int main()
{
	char ch;
	printf("�����з��Ż����޷��űȽϣ�y�����з��ţ�n�����޷��ţ���");
	ch = getchar();
	if (ch == 'y')
	{//�з������������
		ch = getchar();   //���߻������Ļ��з�
		Sign();
	}
	else if (ch == 'n')
	{//�޷������������
		ch = getchar();   //���߻������Ļ��з�
		unsign();
	}

	return 0;
}
