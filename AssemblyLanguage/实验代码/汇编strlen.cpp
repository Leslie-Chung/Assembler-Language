#include <stdio.h>
#define MAX 100
int main()
{
	char a[MAX];
	int len;
	printf("������һ���ַ�����");
	scanf_s("%s", a, MAX);
	_asm
	{
		lea ecx, a    //ECX �д���ַ����׵�ַ
		call strlen1
		mov len, eax
		jmp end1
	}
	_asm
	{
	strlen1:
		push esi          //����esi
		xor esi, esi
		or esi, ecx       //esi��ֵҲΪ�ַ����׵�ַ
	for1:
		mov al, [esi]
		or al, al        //�ж��ַ����Ƿ����
		je len1            //������������ת
		inc esi
		jmp for1
	len1:
		sub esi,ecx
		mov eax, esi       //׼������ֵ
		pop esi
		ret
	
	}
	_asm
	{
		end1:
	}
	printf("�ַ�������Ϊ��%d", len);
	return 0;
}