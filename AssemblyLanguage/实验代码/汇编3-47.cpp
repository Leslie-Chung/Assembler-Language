#include<iostream>
using namespace std;
#define max 100
int main()
{
	int num;
	char a[max];
	char b[9];
	printf("������һ��ʮ��������ɵ��ַ��������ܺ��������ַ�����");
	cin >> a;
	_asm
	{
		call LAB1

		lea edx, b;
		xor esi, esi
		mov edi, eax      //Ҫת����ʮ������ֵ
		inc esi           //ѭ��8�Σ�һ��4λ����32λ
		for1:
		mov ecx, 8
		sub ecx, esi       //8-i
		shl ecx, 2         //32 - i*4
		mov eax, edi
		shr eax, cl        // >>(32 - i*4)
		and al, 0fH        // ��ȡ��4λ
		or al, 30H         //�൱�ڼ�30H
		cmp al, 39H
		jle for2
		add al, 7
			for2:
		mov BYTE PTR[edx], al
		inc edx

		inc esi               //��������
		cmp esi, 8             // <=8��ת
		jle for1
		mov BYTE PTR[edx], 0

		jmp LAB2            //����������ӳ��򲿷�
	}
	_asm      //ת����Ӧ��ֵ�ӳ���
	{
	LAB1:
		push ecx
		push edx
		push esi
		lea esi, a
		xor ecx, ecx        //ECX�洢�ַ�������
		
	loop1:
		mov al, BYTE PTR [esi + ecx]
		cmp al,0
		je next1
		inc ecx
		jmp loop1
	next1:
		xor edx, edx         //EDX��Ϊ��ֵY
		xor eax, eax
		jecxz next3
	next2:
		imul edx, 10         //Y*10
		mov al, [esi]        //al��ʱ����Ϊ��Ӧ��ASCII��
		inc esi
		and al, 0fH          //Ч������ -30H
		add edx, eax          //Y = Y*10 + d
		loop next2
	next3:
		mov num, edx
		mov eax, edx         //׼������ֵ
		pop esi
		pop edx
		pop ecx
		ret
	}
	_asm
	{
		LAB2:
	}
	cout <<"ʮ������ֵΪ��" <<num << endl << "ʮ�������ַ�����ʽΪ��" << b;
	return 0;
}