#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int main()
{
	char* dst;
	char a;
	int n,count;
	printf("�������ʼ�ռ��С��");
	scanf_s("%d", &n);
	dst = (char*)malloc(n * sizeof(char));
	printf("��������Ҫ��������Ŀռ��С��");
	scanf_s("%d", &count);
	printf("������Ҫ����ֵ��");
	scanf_s("\n%c", &a, 1);
	_asm
	{
		xor eax, eax
		mov ecx, dst      //ecx��ռ���׵�ַ
		mov edx, count    //edx���Ҫ�޸ĵĿռ��С
		mov al, a         //Ҫ���ǵ�ֵ
		//�������麯���Ļ���������ѹջ���Σ��Ĵ�������
		call memset1
		jmp last
	}
	_asm
	{
	memset1:
		push ecx
		test edx, edx
		jz toend          //Ҫ�޸ĳ���Ϊ0��ֱ�ӽ���
	dword_alain:
		push edi          //����edi
		mov edi, ecx      //edi=Ŀ���׵�ַ
		cmp edx, 4    //����С��4��ֱ�ӽ�����β��ʣ��ռ�һ��һ���ֽڵ����
		jb tail
		neg ecx         //ȡ�����������Ŀ���ַ�ڶ���֮ǰ���ֽ���
		and ecx, 3      //ecxΪ���ֽڶ���֮ǰ���ֽ���
		jz SHORT dwords  //�Ѿ�4�����룬����ת
		sub edx, ecx     //�Ժ���Ҫ��������ĳ���

	adjust_loop:
		mov [edi], al       //��4�ֽڶ���ǰ�Ŀռ������
		inc edi
		dec ecx         //�����õ�add��subָ���Դ����ֽڽϳ�
		jnz adjust_loop
	dwords:        //���ˣ��׵�ַ��4�ֽڶ���
		//�˶ε�Ŀ��Ϊ��eax�к����ֽڵ����ֵ
		//�Ż������ϵĴ���
		mov ecx, eax         //ecx = 0/0/0/value
		shl eax, 8       //eax = 0/0/value/0
		or eax, ecx      //eax = 0/0/value/value
		or ecx, eax      //ecx = 0/0/value/value
		shl eax, 10h     //eax = value/value/0/0
		or eax, ecx      //eax = value/value/value/value
		//�����ϴ��������ٶȿ�
		//ʵ��ÿ��4�ֽڵ����
		mov ecx, edx     //ecx = ����
		and edx, 3       //edx = 4�ֽ������ʣ��
		shr ecx, 2       //���ȳ���4��Ϊ���ֽ����Ĵ���
		jz tail          //��Ϊ0��ֱ����ת����β����
		rep stosd        //�������
	main_loop_tail:
		test edx, edx         //�����Ƿ���ʣ��β��
		jz finish         //û�У�������

	tail://ɨβ����
		mov [edi],al     //ÿ��һ�ֽ�
		inc edi
		dec edx
		jne tail
	finish:
		pop edi
		pop eax       //eax=�ռ��׵�ַ��׼������ֵ
			ret
	toend:
		pop eax
			ret
	}
	_asm
	{
		last:
	}
	if (dst)
	{
		printf("����Ŀռ�ֵΪ��");
		for (int i = 0; i < count; i++)
		{
			printf("%c ", dst[i]);
		}
	}
	return 0;
}