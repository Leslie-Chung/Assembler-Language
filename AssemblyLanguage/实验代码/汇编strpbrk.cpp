#include<stdio.h>
#include<stdlib.h>
#define MAX1 100
#define MAX2 100
int main()
{
	char str1[MAX1];
	char control[MAX2];
	char* p = NULL;
	printf("�������ַ���1(�Ӵ�)��");
	scanf_s("%s", str1, MAX1);
	printf("�������ַ���2(ĸ��)��");
	scanf_s("%s", control, MAX2);
	_asm
	{  //׼������
		lea edx, str1
		lea ecx, control
		call strbrk1
		mov p, eax
		jmp end1
	}
	_asm 
	{      //�Լ�д��strbrk�⺯��
	strbrk1 :
		push edx
		push ecx
		push ebp
		mov ebp, esp         //������ջ���
		call strlen1
		mov ecx, eax         //ecx = ��control����
		jecxz OVER3           //control����Ϊ0������Ҫ����

		xor eax, eax
		mov edx, ecx           //���洮2����
		mov ebx, [ebp+8]       //ȡ��1�׵�ַ
	for1 :
		mov esi, ebx           //ESI=��ʼ������1����ʼ��ַ
		mov edi, [ebp+4]       //EDI=��2�׵�ַ
		mov ecx, edx           //ECX=��2����
		mov al, [esi]          //ȡ����1��һ��Ԫ��
	for2 :
		cmp al, [edi]
		jz  OVER2               //˵���ҵ�
		inc edi                  //û�ҵ��ͼ�������
		loop for2
		inc ebx                  //�����껹���ڣ���Ӵ�1����һ��Ԫ�ؿ�ʼ
		or al, al
		jnz for1

	OVER1 :    //δ�ҵ�
		pop ebp
		pop ecx
		pop edx
		xor eax, eax
		ret

	OVER2 :     //�ҵ�
		pop ebp
		pop ecx
		pop edx
		mov eax, esi      //׼������ֵ
		ret

	OVER3:
		pop ebp
		pop ecx
		pop edx
		xor eax, eax             //eax=0,����û�ҵ�
		ret
	}

	_asm
	{    //�Լ�д�����ַ������ȵĿ⺯��
	strlen1 :
		push esi           //����esi
		xor esi, esi
		xor eax, eax
		or esi, ecx       //esi��ֵҲΪ�ַ����׵�ַ
	then :
		mov al, [esi]
		or al, al        //�ж��ַ����Ƿ����
		je len1            //������������ת
		inc esi
		jmp then
	len1 :
		sub esi, ecx
		mov eax, esi      //׼������ֵ
		pop esi
		ret
	}
	_asm
	{
		end1 :
	}
	if (p)
	{
		printf("��ĸ�����״γ��ֵ��ַ���ַƫ��Ϊ��%p", p);
		printf("\n���ַ�Ϊ��%c", *p);
	}
	else
	{
		printf("��1��û���ַ��ڴ�2�г���");
	}
	return 0;
}