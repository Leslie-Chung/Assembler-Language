    ;��ʾ���򣨼����жϸ���ɫ����
	PORT_KEY_DAT   EQU   0x60
    PORT_KEY_STA   EQU   0x64
        section   text
        bits   16
    Signature     db   "MARY"       ;ǩ����Ϣ
    Version       dw   1            ;��ʽ�汾
    Length        dw   end_of_text  ;�������򳤶�
    Start         dw   Begin        ;����������ڵ��ƫ��
    Zoneseg       dw   1A00H        ;����������ڵ�Ķ�ֵ��������
    Reserved      dd   0            ;����

;==============================================================
    newhandler:                     ;��չ��ʾI/O�������
        STI                         ;���ж�//@2
        PUSHA                       ;����ͨ�üĴ���//@3
        PUSH  DS                    ;�����漰�ĶμĴ���//@4
        PUSH  ES
        ;
        CALL  putchar               ;ʵ�ֹ���
        ;
        POP   ES                    ;�ָ��μĴ���
        POP   DS
        POPA                        ;�ָ�ͨ�üĴ���
        IRET                        ;�жϷ���
    ;-----------------------------------------
    putchar:
    ;���ܣ���ǰ���λ�ô���ʾ�����Ե��ַ�����������һ��λ��
    ;��ڣ�AL=�ַ�ASCII�룻BL=����
    ;˵������֧���˸����������ȿ��Ʒ�
        PUSH  AX
        MOV   AX, 0B800H            ;������ʾ�洢����ֵ
        MOV   DS, AX
        MOV   ES, AX
        POP   AX
        ;        
        CALL  get_lcursor           ;ȡ�ù���߼�λ��
        ;
        CMP   AL, 0DH               ;�س�����
        JNZ   .LAB1
        MOV   DL, 0                 ;�ǣ��к�DL=0
        JMP   .LAB3
    .LAB1:
        CMP   AL, 0AH               ;���з���
        JZ    .LAB2
        ;                           ;���ˣ���ͨ�ַ�
        MOV   AH, BL                ;AH=����
        MOV   BX, 0                 ;������λ�ö�Ӧ�洢��Ԫƫ��
        MOV   BL, DH
        IMUL  BX, 80
        ADD   BL, DL
        ADC   BH, 0
        SHL   BX, 1                 ;BX=(�к�*80+�к�)*2
        ;
        MOV   [BX], AX              ;д����ʾ�洢����Ӧ��Ԫ
        ;
        INC   DL                    ;�����к�
        CMP   DL, 80                ;�������һ�У�
        JB    .LAB3                 ;��
        MOV   DL, 0                 ;�ǣ��к�=0
    .LAB2:
        INC   DH                    ;�����к�
        CMP   DH, 25                ;�������һ�У�
        JB    .LAB3                 ;��
        DEC   DH                    ;�ǣ��кż�1�����������һ�У�
        ;
        CLD                         ;ʵ����Ļ���Ϲ�һ��
        MOV   SI, 80*2              ;��1����ʼƫ��
        MOV   ES, AX
        MOV   DI, 0                 ;��0����ʼƫ��
        MOV   CX, 80*24             ;����24������
        REP   MOVSW                 ;ʵ����Ļ���Ϲ�һ��
        ;
        MOV   CX, 80                ;�����Ļ���һ��
        MOV   DI, 80*24*2           ;���һ����ʼƫ��
        MOV   AX, 0x0720            ;�ڵװ���
        REP   STOSW                 ;�γɿհ���
    .LAB3:
        CALL  set_lcursor           ;�����߼����
        CALL  set_pcursor           ;����������
        RET
    ;---------------------------------------------
    get_lcursor:                    ;ȡ���߼����λ�ã�DH=�кţ�DL=�кţ�
        PUSH  DS
        PUSH  0040H                 ;BIOS�������Ķ�ֵ��0040H
        POP   DS                    ;DS=0040H
        MOV   DL, [0050H]           ;ȡ���к�
        MOV   DH, [0051H]           ;ȡ���к�
        POP   DS
        RET
    ;---------------------------------------------
    set_lcursor:                    ;�����߼���꣨DH=�кţ�DL=�кţ�
        PUSH  DS
        PUSH  0040H                 ;BIOS�������Ķ�ֵ��0040H
        POP   DS                    ;DS=0040H
        MOV   [0050H], DL           ;�����к�
        MOV   [0051H], DH           ;�����к�
        POP   DS
        RET
    ;---------------------------------------------
    set_pcursor:                    ;���������꣨DH=�кţ�DL=�кţ�
        MOV   AL, 80                ;������Ĵ���ֵ
        MUL   DH                    ;AX=(�к�*80+�к�)
        ADD   AL, DL
        ADC   AH, 0
        MOV   CX, AX                ;���浽CX
        ;
        MOV   DX, 3D4H              ;�����˿ڵ�ַ
        MOV   AL, 14                ;14���ǹ��Ĵ�����λ
        OUT   DX, AL
        MOV   DX, 3D5H              ;���ݶ˿ڵ�ַ
        MOV   AL, CH
        OUT   DX, AL                ;���ù��Ĵ�����8λ
        ;
        MOV   DX, 3D4H              ;�����˿ڵ�ַ
        MOV   AL, 15
        OUT   DX, AL
        MOV   DX, 3D5H              ;���ݶ˿ڵ�ַ
        MOV   AL, CL
        OUT   DX, AL                ;���ù��Ĵ�����8λ
        RET
    ;========================================================

    Begin:
        MOV   AL, 0
        MOV   AH, 5
        INT   10H                       ;ָ����0��ʾҳ
        ;
        XOR   AX, AX                    ;׼�������ж�����
        MOV   DS, AX
        CLI
        MOV   WORD [90H*4], newhandler  ;����90H�ж�����֮ƫ��
        MOV   [90H*4+2], CS             ;����90H�ж�����֮��ֵ
        STI
        ;
        PUSH  CS
        POP   DS
        MOV   BL, 01H                   ;Ĭ������ɫ
        ROR   ECX, 3                    ;����ɫ�洢��ECX����λ
	NEXT:
		MOV   AH, 0                     ;���ü���I/O����
        INT   16H                       ;��ȡ�û�����
        MOV   CL, AH                    ;����ɨ����
        ;
        CMP   CL, 1CH                    ;�س�����
        JZ    .LAB2                      ;�������
		CMP   CL, 13H                     ;r
		JZ    .COLOR_RED
		CMP   CL, 22H                     ;g
		JZ    .COLOR_GREEN
		CMP   CL, 30H                     ;b
		JZ    .COLOR_BLUE
		MOV   AH, 14                    ;��ʾȡ�õ��ַ���������
        JMP   .LAB1
        ;
	.COLOR_RED:
		MOV   BL, 04H
        ROR   ECX, 3
		JMP   .LAB1
	.COLOR_GREEN:
		MOV   BL, 02H
        ROR   ECX, 3
		JMP   .LAB1
	
	.COLOR_BLUE:
		MOV   BL, 01H
        ROR   ECX, 3
		JMP   .LAB1

    .LAB1:
        ROL   ECX, 3                    ;ȡ����ɫ
        INT   90H                       ;������չ����ʾI/O����
        ;                                ��ʾ�����Ե��ַ�
        JMP   NEXT
    .LAB2:
        MOV   AH, 14
        MOV   AL, 0DH
        INT   10H                        ;��ʾ����
        MOV   AH, 14
        MOV   AL, 0AH
        INT   10H                        ;��ʾ����
        RETF
    ;
    end_of_text:                    ;����λ��
