; multi-segment executable file template.

macro printn      ;��ӡ�س�����
    mov DL, 0DH 
    mov ah, 2
    int 21H
    mov DL, 0AH
    mov ah, 2
    int 21H
endm

macro printstr 1 ;��ӡ�ַ���
    mov DX, 1
    mov ah, 9
    int 21H
endm

macro inputstr 1 ;�����ַ���
    mov DX, 1
    mov AH, 0AH
    int 21H
endm
data segment
    a db 6,0,6 DUP(0)
    num1 dw 0
    b db 6,0,6 DUP(0)
    num2 dw 0
    gy dw 0
    gb dw 0,0 
    result db 6 DUP()
    pin db "please input a number bellow 65535:$" 
    pout db "the least common multiple is :$"
    ; add your data here!
    pkey db "press any key...$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    
    lea ax, pin
    printstr ax  ;��ӡ��ʾ��Ϣ
    lea ax, a
    inputstr ax   ;����
    ;lea dx, a
    ;mov ah, 0AH
    ;int 21h 
    printn       ;��ӡ�س�����
    
    lea ax, pin   
    printstr ax  ;��ӡ��ʾ��Ϣ
    lea ax, b
    inputstr ax  ;����
    xor cx, cx
    
    lea si, a 
    inc si
    mov cl, [si]   ;��1���� 
    inc si         ;siָ�����λ��
    
    xor dx, dx
    mov bx, 10
    xor ax, ax
lop1:
    mul bx
    mov dl, [si] 
    inc si
    sub dl, 30H
    add ax,dx
    loop lop1
    mov num1, ax
    ;��ʱnum1Ϊ��һ������ֵ
    
    lea si, b 
    inc si
    mov cl, [si]   ;��2���� 
    inc si         ;siָ�����λ��
    mov bx, 10
    xor ax, ax
lop2:
    mul bx
    mov dl, [si] 
    inc si
    sub dl, 30H
    add ax,dx
    loop lop2
    mov num2, ax 
    ;��ʱax��Ϊ�ڶ�������ֵ
    xor dx, dx
    mov ax, num1  ;axΪ��һ����
    mov bx, num2
    ;�������Լ��
    cmp ax, bx
    jae max
    mov cx, ax
    mov ax, bx
    mov bx, cx
    
max:           ;��ʱax��Ϊ�ϴ�ֵ
    div bx      ;a/b,������dx����ax
    cmp dx, 0
    je over      ;˵��bxֵΪ���Լ��
    mov ax, bx    ;a = b
    mov bx, dx    ;b = ����
    xor dx, dx    ;��ֹ32λ����������λdxӰ��
    jmp max
    
over:
    mov gy, bx
    mov ax, num1  
    mov cx, num2 
    mul cx        ;�˻�ΪDS:AX,����Ϊ32λ
    div bx        ;�˻��������Լ�� = ��С����������AX��,
                  ;����С���������󣨳���16λ���ᱨ��
    mov gb, ax
    mov bx, 10    ;10���ƻ���
    lea si, result
    add si, 5 
    mov [si],'$'   ;�Ž�����־
    
    mov cx, 5     ;���Ϊ5λ��������10��μ���

over1:
    div bx         ;�����AX������DX
    or dl, 30H     ;�õ���ӦASCII��
    dec si
    mov [si], dl 
    xor dx, dx     ;��ֹ32λ����������λdxӰ��
    loop over1
   
   
over2:
    mov al, [si]
    cmp al, 30H
    jne toprint
    inc si
    jmp over2
     
toprint: 
     printn        ;��ӡ�س�����
     lea ax, pout
     printstr ax   ;��ӡ��ʾ��Ϣ
     printstr si   ;��ӡ���
     printn        ;��ӡ�س�����
     
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
