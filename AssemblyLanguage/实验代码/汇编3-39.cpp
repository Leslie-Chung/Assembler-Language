#include<stdio.h>
int main()
{
	char a[20];
	char Inverse[20];  //����������ַ���
	printf("������һ����Ҫ����������ַ�����");
	scanf_s("%s", a, 20);
	_asm
	{
		xor eax, eax
		xor esi,esi
		xor ecx, ecx          //����
		lea ebx, a          //ȡԭ�ַ����׵�ַ
		lea edx, Inverse      //ȡ���ú��ַ����׵�ַ
			loop1:            //ѹջ����¼
		mov al, BYTE PTR[ebx]
		cmp al, 0             //�ж��ַ����Ƿ����
		je NEXT1
		push ax              //ѹջ
		inc ecx              //�ַ�������+1
		inc ebx              //������һ��Ԫ��
		jmp loop1
			NEXT1:
		pop bx
		mov BYTE PTR[edx+esi], bl
		inc esi
		loop NEXT1                            //��Դ�ַ������ε�ջ��ʵ������

		mov BYTE PTR[edx + esi], 0            //�ַ���β�ӡ�\0��
	}
	printf("�������ַ���Ϊ��%s", Inverse);
	return 0;
}