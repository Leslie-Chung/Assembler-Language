#include<iostream>
using namespace std;
#define max 100
int main()
{
	char cha;
	char str1[max];
	int n;
	cout << "������һ���ַ���";
	cin >> cha;
	cout << "�����볤�ȣ�";
	cin >> n;
	_asm
	{
		xor eax, eax
		mov ecx, n   //����n��
		mov al, cha   //ȡ�ַ�
		lea esi, str1
		call cat
		jmp end1
	}
	_asm
	{
		cat :
		for1:
		mov BYTE PTR[esi], al
		inc esi
		loop for1
		mov BYTE PTR[esi],0
		ret
	}
	_asm
	{
		end1 :
	}
	
	cout <<"���ɵ��ַ���Ϊ��"<< str1 << endl;
	return 0;
}