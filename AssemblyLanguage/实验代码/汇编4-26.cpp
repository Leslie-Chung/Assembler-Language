#include<stdio.h>

int main() {
	char a[100];
	printf("������Ҫͳ�Ƶ��ַ�����");
	scanf_s("%s", a, 100);
	int n;

	_asm {
		lea edx, a      //ȡ�ַ������׵�ַ
		xor eax, eax    //����
		xor ebx, ebx     //BL��Ŀǰ�����0����,BH��Ŀǰ����0��Ŀ
	    mov ecx, 8      //ÿ�β���һ���ַ�����8λ

	then:
		mov al, BYTE PTR[edx]
		mov ecx, 8
		cmp al, 0
		je OVER       //����

	for1 :
		shr eax, 1      //�����λ�Ƶ�CFλ�����������ֵΪ0����1
		jnb zero_count      //CFΪ0����ת��ͳ�Ƽ���
		xor bh, bh        //����1�򽫵�ǰ����

	for2 :
		dec ecx
		cmp ecx, 0
		je NEXT    //ѭ��8�������ϼ�ѭ��
		jmp for1

	zero_count :
		inc bh
		cmp bl, bh
		jge for2
		mov bl, bh
		jmp for2
		
	NEXT:
		inc edx
		jmp then

	OVER :
		xor eax,eax
		mov al, bl
		mov n, eax

	}

	printf("����0����󳤶�Ϊ��%d", n);

	return 0;
}