#include <stdio.h>
int main()
{
	char a[100];
	printf("������һ���ַ�����");
	scanf_s("%s", a,100);
	char count[11];
	_asm
	{
		xor eax, eax
		lea ebx, a
	loop1:
		mov cl,BYTE PTR[ebx]
		cmp cl,0    //�ж��ַ����Ƿ����
		je NEXT
		inc eax
		inc ebx
		jmp loop1
	NEXT:
		lea ebx, count
		mov esi, 10    //ʮ���ƻ���
		mov ecx, 10    //ѭ������
	NEXT1:
		xor edx,edx
		div esi         //eax���̣�edx������
		add dl, '0'
		mov [ebx + ecx - 1], dl
		loop NEXT1
		
		mov BYTE PTR[ebx + 10],0
	}
	printf("���ַ����ĳ���Ϊ��");
	for (int i = 0; i < 10; i++)
	{   //����Ϊ10���ַ������ȵõ���λ�����һλ��ǰ���λ����Ϊ0�����ʱ�����ǰ��λ����Ϊ0��λ
		if (count[i] != '0')
		{
			int j = i;
			while (j < 10)
			{
				printf("%c", count[j]);
				j++;
			}
			break;
		}
	}
	return 0;
}