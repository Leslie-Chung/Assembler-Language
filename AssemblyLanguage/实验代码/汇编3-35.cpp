#include <stdio.h>
int main()
{
	unsigned a;
	int count;
	printf("������һ��������");
	scanf_s("%u", &a);
	_asm
	{
			xor edx,edx  //��λֵΪ0��λ��
			mov eax,a
			mov ecx,32   //ѭ������
		NEXT:
			shr eax,1    //����һλ�����λ����CF
			cmc          //��CFλȡ����0->1���Ӷ�����adcָ��ͳ��λλ0�ĸ���
			adc dl, 0    //��CFλ,ͳ��Ϊ0λ�ĸ���
			loop NEXT
			mov count,edx
	}
	printf("%d ", count);
	return 0;
}