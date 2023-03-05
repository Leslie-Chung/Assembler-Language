; multi-segment executable file template.
macro printn  
    mov DL,0DH
    mov AH, 2
    int 21H
    mov DL,0AH
    mov AH, 2
    int 21H 
endm       ;��ӡ�س�����

data segment
    result db "00000$"; 
    pout db "the sum is :$"
    pkey db "press any key...$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, 0F000H     ;�����ݸĵ�Ҫ�������
    mov ds, ax
    mov es, ax
     
    xor ax, ax
    xor bx, bx 
    xor si, si
    mov cx, 100 
    
lop1:           ;��Ҫ�����������100������
    mov [si], 2  ;��ʵ��ʱ���100��2
    inc si
    loop lop1
     
    mov cx, 100
    dec si 
    
again:
    mov al, [si]
    dec si
    add bx, ax
    loop again
      ;��ʱbx�д�ź�
    mov ax, data
    mov ds, ax
    mov es, ax
    
    mov cx, 5
    lea di, result
    add di, 4  
    mov ax, bx

lop2:
    mov bl, 10   ;10���ƻ���
    div bl    ;������ah��
    or  ah, 30h
    mov [di], ah 
    dec di
    xor ah, ah
    loop lop2
    
    mov cx, 4
    lea si, result
notzero: ;����ǰ���0
    
    mov ah, [si]
    cmp ah,'0'
    jne printstr 
    inc si
    loop notzero
     
printstr:    
    lea dx, pout
    mov ah, 9
    int 21h      ;��ӡ��ʾ��Ϣ
    mov dx, si
    mov ah, 9
    int 21h
    
    printn    ;��ӡ�س�����       
   lea dx, pkey
   mov ah, 9
   int 21h        ; output string at ds:dx
    
    ; wait for any key....    
   ; mov ah, 1
   ; int 21h
over:  
   mov ax, 4C00h ; exit to operating system.
   int 21h    
ends

end start ; set entry point and stop the assembler.
