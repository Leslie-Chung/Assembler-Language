#include<iostream>
using namespace std;
#define max 100
int main()
{
	char a[max];
	int num1, num2;
	int flag;    //�жϳ���Ϊ�Ƿ�Ϊ0
	char b[11];
	char s[11], ys[11];
	printf("�����뱻����:");
	cin >> a;
	printf("���������:");
	cin >> b;
	
	_asm
	{
		lea esi, a
		call LAB1
		mov edx, eax     //���ر�����
		lea esi, b
		call LAB1       //���س���
		mov ecx,eax     //��������ecx��
		mov eax,edx    //����������eax��
		xor edx, edx
		jecxz end1      //����Ϊ0,��ת����
		div ecx          //����eax,������edx
		mov num1, eax    //num1�̵���ֵ
		mov num2, edx    //num2��������ֵ
		lea ebx, s
		call for1

		mov eax, edx
		lea ebx, ys
		call for1

		jmp end2        //����������ӳ���
	}
	_asm
	{  //���̺�����ת��Ϊ10�����ַ������ӳ���
	for1:
		push edx
		push ecx
		push ebp
		//lea ebx, count
		mov esi, 10    //ʮ���ƻ���
		mov ecx, 10    //ѭ������
	for2 :
		xor edx, edx
		div esi         //eax���̣�edx������
		add dl, '0'
		mov[ebx + ecx - 1], dl
		loop for2

		mov BYTE PTR[ebx + 10], 0       //�ַ���ĩβ�ӡ�\0��
		
		pop ebp
		pop ecx
		pop edx
		ret
	}
	_asm
	{     //���ַ���ת��Ϊ��ֵ���ӳ���
	LAB1:
		push ecx
		push esi
		push edx
		push ebp
		xor ecx, ecx        //ECX�洢�ַ�������

	loop1 :
		mov al, BYTE PTR[esi + ecx]
		cmp al, 0
		je next1
		inc ecx
		jmp loop1
	next1 :
		xor ebx, ebx         //ebx��Ϊ��ֵY
		xor eax, eax
		jecxz next3
	next2 :
		imul ebx, 10         //Y*10
		mov al, [esi]        //al��ʱ����Ϊ��Ӧ��ASCII��
		inc esi
		and al, 0fH          //Ч������ -30H
		add ebx, eax          //Y = Y*10 + d
		loop next2
	next3 :
		mov eax, ebx         //׼������ֵ
		pop ebp
		pop ebx              //�ָ��Ĵ���ֵ
		pop esi
		pop ecx
		ret
	}
	_asm
	{
	end1:
		mov flag,ecx
	end2:
	}
	if (flag == 0)
	{
		cout << "��������Ϊ0������" << endl;
	}
	else
	{
		cout << "ת��Ϊ10������ֵ����Ϊ��"<<num1 << endl << "ת��Ϊ10������ֵ������Ϊ��" << num2 << endl;
		cout << "ʮ�����ַ�����ʽ" << endl << "��Ϊ��";
		for (int i = 0; i < 10; i++)
		{   //���������ʽ��ȥ��ǰ������0
			if (s[i] != '0')
			{
				int j = i;
				while (j < 10)
				{
					cout<<s[j];
					j++;
				}
				break;
			}
		}
		cout << endl << "����Ϊ��";
		for (int i = 0; i < 10; i++)
		{   //���������ʽ��ȥ��ǰ������0
			if (ys[i] != '0')
			{
				int j = i;
				while (j < 10)
				{
					cout << ys[j];
					j++;
				}
				break;
			}
		}
	}
	
	return 0;
}