bits 32
org 0x60800
;================= �������� ===================

     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     delay equ 1500				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
     ddelay equ 1000				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�

     ;org 0x600					; ������ص� cs : 8200h
start:

	mov byte[char],'@'

;���������ӳ�
	call bdaryDraw

	mov ecx, 100					;���ó������ʱ��

pro:
	push ecx
loop1:
	dec word[count]				; �ݼ���������
	jnz loop1					; >0����ת;
	mov word[count],delay
	dec word[dcount]				; �ݼ���������
    jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay
	
	;����ۼ�
	mov al, 20h
	mov [gs:bx],ax 

s: 
	mov al,1
    cmp al,byte[rdul]
	jz  DnRt
      mov al,2
      cmp al,byte[rdul]
	jz  UpRt
      mov al,3
      cmp al,byte[rdul]
	jz  UpLt
      mov al,4
      cmp al,byte[rdul]
	jz  DnLt
      jmp $	

DnRt:
	mov byte[rdul],Dn_Rt
	inc word[x]
	inc word[y]
	mov bx,word[x]
	mov ax,12
	sub ax,bx
      jz  dr2ur
	mov bx,word[y]
	mov ax,80
	sub ax,bx
      jz  dr2dl
	jmp show
dr2ur:
	  mov bx, word[y]
	  mov ax, 80
	  sub ax, bx
	  jz dr2ul 
      mov word[x],10
      mov byte[rdul],Up_Rt	
      jmp show
dr2dl:
      mov word[y],78
      mov byte[rdul],Dn_Lt	
      jmp show

dr2ul:
	 dec word[x]
	 dec word[y]
	 mov word[rdul], Up_Lt
	 jmp show

UpRt:
	mov byte[rdul],Up_Rt
	dec word[x]
	inc word[y]
	mov bx,word[y]
	mov ax,80
	sub ax,bx
      jz  ur2ul
	mov bx,word[x]
	mov ax, -1
	sub ax,bx
      jz  ur2dr
	jmp show
ur2ul:
	  mov bx,word[x]
	  mov ax,-1
	  sub ax,bx
      jz  ur2dl
      mov word[y],78
      mov byte[rdul],Up_Lt	
      jmp show
ur2dr:
      mov word[x],1
      mov byte[rdul],Dn_Rt	
      jmp show

ur2dl:
	inc word[x]
	dec word[y]
	mov word[rdul], Dn_Lt
	jmp show
	
UpLt:
	mov byte[rdul],Up_Lt
	dec word[x]
	dec word[y]
	mov bx,word[x]
	mov ax,-1
	sub ax,bx
      jz  ul2dl
	mov bx,word[y]
	mov ax,40
	sub ax,bx
      jz  ul2ur
	jmp show

ul2dl:
	  mov bx,word[y]
	  mov ax,40
	  sub ax,bx
      jz  ul2dr
      mov word[x],1
      mov byte[rdul],Dn_Lt	
      jmp show
ul2ur:
      mov word[y],42
      mov byte[rdul],Up_Rt	
      jmp show

ul2dr:
	inc word[x]
	inc word[y]
	mov word[rdul], Dn_Rt
	jmp show
	
	
DnLt:
	mov byte[rdul],Dn_Lt
	inc word[x]
	dec word[y]
	mov bx,word[y]
	mov ax,40
	sub ax,bx
      jz  dl2dr
	mov bx,word[x]
	mov ax,12
	sub ax,bx
      jz  dl2ul
	jmp show

dl2dr:
	  mov bx,word[x]
 	  mov ax,12
	  sub ax,bx
      jz  dl2ur
      mov word[y],42
      mov byte[rdul],Dn_Rt	
      jmp show
	
dl2ul:
      mov word[x],10
      mov byte[rdul],Up_Lt	
      jmp show

dl2ur:
	dec word[x]
	inc word[y]
	mov word[rdul],Up_Rt
	jmp show
	
show:
	;��ʾ����-msg
	mov ebx, 160*5 + 110 	;��Ļ����
	mov ecx, msglen
	mov esi, 0
	mov edi, 0
showMsg:
	mov al,byte[msg+esi]
	mov ah, 0x0f
	mov [gs:ebx+edi],  ax
	inc esi
	add edi,2
	loop showMsg

    xor eax,eax                 ; �����Դ��ַ
    mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,0Fh				;  0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	mov al,byte[char]		;  AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
	mov [gs:bx],ax  		;  ��ʾ�ַ���ASCII��ֵ

	pop ecx
	dec ecx
	cmp ecx,0
	jnz pro
	
	mov eax, 1
	int 0x80

	ret 
         ; ֹͣ��������ѭ�� 

;================= �߿���� ===============
bdaryDraw:
	mov bx, 160*12+80
	mov ah, 0x0f
	mov al, byte[bdaryrow]
	mov cx, 40
	mov di, 0
row:
	mov [gs:bx+di], ax
	add di, 2
	loop row 

	mov al, byte[bdarycol]
	mov bx, 80
	mov di, 0
	mov cx, 12
col:
	mov [gs:bx+di], ax
	add di, 160
	loop col

	ret

;================= ������ =================
datadef:	
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; �������˶�
    x    dw 7			;�ַ�������
    y    dw 40			;�ַ�������
    char db 'A'
	msg  db 'LuoRenLiang p2'		;����
    msglen equ ($-msg)
	bdaryrow db '-'
	bdarycol db '|'

