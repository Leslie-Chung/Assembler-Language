    ;��ʾ����ʶ��MARUI�ַ���
	PORT_KEY_DAT   EQU   0x60
    PORT_KEY_STA   EQU   0x64
        section   text
        bits   16
    Signature     db   "MARY"       ;ǩ����Ϣ
    Version       dw   1            ;��ʽ�汾
    Length        dw   end_of_text  ;�������򳤶�
    Start         dw   Begin        ;����������ڵ��ƫ��
    Zoneseg       dw   1500H        ;����������ڵ�Ķ�ֵ��������
    Reserved      dd   0            ;����

	;-----------------------------------
    Begin:
        MOV   AX, 0                     ;׼�������ж�����
        MOV   DS, AX
        CLI
		MOV   WORD [9*4], int09h_handler
        MOV   [9*4+2], CS               ;�����µļ����жϴ������
        STI
        ;
	NEXT:
		MOV   AH, 0                     ;���ü���I/O����
        INT   16H                       ;��ȡ�û�����
        ;
		MOV   AH, 14                    ;��ʾȡ�õ��ַ���������
        INT   10H
        ;
        CMP   AL, 0DH
        JNZ   NEXT;
        ;
        MOV   AH, 14
        MOV   AL, 0DH
        INT   10H                        ;��ʾ����
        MOV   AH, 14
        MOV   AL, 0AH
        INT   10H                        ;��ʾ����
        ;
        RETF                             ;����(���ص�������)
    ;-----------------------------------
    int09h_handler:                     ;�µ�9�ż����жϴ������
        PUSHA                           ;����ͨ�üĴ���
        ;
        MOV   AL, 0ADH
        OUT   PORT_KEY_STA, AL          ;��ֹ���̷������ݵ��ӿ�
        ;
        IN    AL, PORT_KEY_DAT          ;�Ӽ��̽ӿڶ�ȡ����ɨ����
        ;
        STI                             ;���ж�
        CALL  Int09hfun                 ;�����ع���
        ;
        CLI                             ;���ж�
        MOV   AL, 0AEH
        OUT   PORT_KEY_STA, AL          ;������̷������ݵ��ӿ�
        ;
        MOV   AL, 20H                   ;֪ͨ�жϿ�����8259A
        OUT   20H, AL                   ;��ǰ�жϴ����Ѿ�����
        ;
        POPA                            ;�ָ�ͨ�üĴ���
        ;
        IRET                            ;�жϷ���
    ;-----------------------------------
    Int09hfun:                          ;��ʾ9H���жϴ������ľ��幦��
        CMP   AL, 1CH                   ;�жϻس�����ɨ����
        JNZ   .LAB1                     ;�ǻس�����ת
        MOV   AH, AL                    ;�س���������ɨ����
        MOV   AL, 0DH                   ;�س���ASCII��
        JMP   SHORT .LAB2
    .LAB1:
        MOV   AH, AL                    ;����ɨ����
        MOV   AL, 31H                   ;�����MARUI�������1
        CMP   AH, 13H                   ;R
        JZ    .LAB2                     
        CMP   AH, 16H                   ;U
        JZ    .LAB2
        CMP   AH, 1EH                   ;A
        JZ    .LAB2
        CMP   AH, 17H                   ;I
        JZ    .LAB2
        CMP   AH, 32H                   ;M
        JZ    .LAB2
        JMP   .LAB3
    .LAB2:
        CALL  Enqueue                   ;���浽���̻�����
    .LAB3:
        RET                             ;����
    ;-----------------------------------
    Enqueue:                            ;��ɨ�����ASCII�������̻�����
        PUSH  DS                        ;����DS
        MOV   BX, 40H
        MOV   DS, BX                    ;DS=0040H
        MOV   BX, [001CH]               ;ȡ���е�βָ��
        MOV   SI, BX                    ;SI=����βָ��
        ADD   SI, 2                     ;SI=��һ������λ��
        CMP   SI, 003EH                 ;Խ������������
        JB    .LAB1                     ;û�У�ת
        MOV   SI, 001EH                 ;�ǵģ�ѭ����������ͷ��
    .LAB1:
        CMP   SI, [001AH]               ;�����ͷָ��Ƚ�
        JZ    .LAB2                     ;��ȱ�ʾ�������Ѿ���
        MOV   [BX], AX                  ;��ɨ�����ASCII���������
        MOV    [001CH], SI              ;�������βָ��
    .LAB2:
        POP   DS                        ;�ָ�DS
        RET                             ;����
    ;
    end_of_text:                    ;����λ��
