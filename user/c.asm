bits 32
org 0x60400
;================= 常量定义 ===================
     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     delay equ 1500				; 计时器延迟计数,用于控制画框的速度
     ddelay equ 1000				; 计时器延迟计数,用于控制画框的速度

     ;org 0x600					; 程序加载到 cs : 8200h
start:

	mov byte[char],'@'

;程序启动延迟
	call bdaryDraw

	mov ecx, 100					;设置程序结束时间

pro:
	push ecx
loop1:
	dec word[count]				; 递减计数变量
	jnz loop1					; >0：跳转;
	mov word[count],delay
	dec word[dcount]				; 递减计数变量
    jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay
	
	;清除痕迹
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
	mov ax,25
	sub ax,bx
      jz  dr2ur
	mov bx,word[y]
	mov ax,40
	sub ax,bx
      jz  dr2dl
	jmp show
dr2ur:
	  mov bx, word[y]
	  mov ax, 40
	  sub ax, bx
	  jz dr2ul 
      mov word[x],23
      mov byte[rdul],Up_Rt	
      jmp show
dr2dl:
      mov word[y],38
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
	mov ax,40
	sub ax,bx
      jz  ur2ul
	mov bx,word[x]
	mov ax,12
	sub ax,bx
      jz  ur2dr
	jmp show
ur2ul:
	  mov bx,word[x]
	  mov ax,12
	  sub ax,bx
      jz  ur2dl
      mov word[y],38
      mov byte[rdul],Up_Lt	
      jmp show
ur2dr:
      mov word[x],14
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
	mov ax,12
	sub ax,bx
      jz  ul2dl
	mov bx,word[y]
	mov ax,-1
	sub ax,bx
      jz  ul2ur
	jmp show

ul2dl:
	  mov bx,word[y]
	  mov ax,-1
	  sub ax,bx
      jz  ul2dr
      mov word[x],14
      mov byte[rdul],Dn_Lt	
      jmp show
ul2ur:
      mov word[y],1
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
	mov ax,-1
	sub ax,bx
      jz  dl2dr
	mov bx,word[x]
	mov ax,25
	sub ax,bx
      jz  dl2ul
	jmp show

dl2dr:
	  mov bx,word[x]
 	  mov ax,25
	  sub ax,bx
      jz  dl2ur
      mov word[y],1
      mov byte[rdul],Dn_Rt	
      jmp show
	
dl2ul:
      mov word[x],23
      mov byte[rdul],Up_Lt	
      jmp show

dl2ur:
	dec word[x]
	inc word[y]
	mov word[rdul],Up_Rt
	jmp show
	
show:
	;显示姓名-msg
	mov ebx, 160*19 + 30 	;屏幕中央
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

    xor eax,eax                 ; 计算显存地址
    mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,0Fh				;  0000：黑底、1111：亮白字（默认值为07h）
	mov al,byte[char]		;  AL = 显示字符值（默认值为20h=空格符）
	mov [gs:bx],ax  		;  显示字符的ASCII码值

	pop ecx
	dec ecx
	cmp ecx,0
	jnz pro
	

	ret 
         ; 停止画框，无限循环 



;================= 边框绘制 ===============
bdaryDraw:
	mov bx, 160*12
	mov ah, 0x0f
	mov al, byte[bdaryrow]
	mov cx, 40
	mov di, 0
row:
	mov [gs:bx+di], ax
	add di, 2
	loop row 

	mov al, byte[bdarycol]
	mov bx, 160*12+80
	mov di, 0
	mov cx, 13
col:
	mov [gs:bx+di], ax
	add di, 160
	loop col

	ret

;================= 数据区 =================
datadef:	
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; 向右下运动
    x    dw 19			;字符所在行
    y    dw 0			;字符所在列
    char db 'A'
	msg  db 'LuoRenLiang p3'		;姓名
    msglen equ ($-msg)
	bdaryrow db '-'
	bdarycol db '|'


