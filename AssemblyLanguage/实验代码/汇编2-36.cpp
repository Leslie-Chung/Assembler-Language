//�û�����һ���ַ�������ʾ����䳤��
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 100
int main()
{
	int len;
	char p[max];
	printf("������һ���ַ�����");
	scanf_s("%s", p,max);
	_asm 
	{
		xor ecx, ecx  //���㣬��������
		lea ebx, p
		then :
		mov al, BYTE PTR[ebx]
		cmp al, 0
		je case1
		inc ecx    //����
		inc ebx    //������һ���ַ���ַ
		jmp then
			case1 :
		mov len, ecx
	}
	printf("�ַ�������Ϊ��%d", len);
	len = strlen(p);

	return 0;
}