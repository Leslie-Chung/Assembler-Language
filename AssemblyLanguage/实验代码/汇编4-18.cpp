#include <iostream>
using namespace std;
#define max 20
#define MAX 2*max
int main()
{
	char a[max];
	char b[max];
	char buffer[MAX];
	cout<<"�������ַ���1��";
	cin >> a;
	cout<<"�������ַ���2��";
	cin >> b;
	_asm
	{
		xor eax,eax
		lea esi, a
		lea edi, buffer
	for1:
		mov al, BYTE PTR[esi]
		cmp al, 0
		je for2                 //a��Ԫ����ȫ��ת��
		mov BYTE PTR[edi], al         //�Ƚ�a��Ԫ���Ƶ�buffer��
		inc edi                //��һ��д���ַ
		inc esi                //��һ��ת��Ԫ�صĵ�ַ
		jmp for1

	for2:
		lea esi, b
	for3:
		mov al, BYTE PTR[esi]
		mov BYTE PTR[edi], al        //ת��b���е�Ԫ�أ����һ��'0'Ҳת��
		cmp al,0
		je for4
		inc esi
		inc edi
		jmp for3

	for4:

	}
	cout <<"�����Ӻ���ַ���Ϊ��"<< buffer << endl;
	return 0;
}