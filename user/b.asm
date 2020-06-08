bits 16
;================= 常量定义 ===================

     Dn_Rt equ 1                  ;D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2                  ;
     Up_Lt equ 3                  ;
     Dn_Lt equ 4                  ;
     delay equ 50000					; 计时器延迟计数,用于控制画框的速度
     ddelay equ 580					; 计时器延迟计数,用于控制画框的速度

     ;org 0x600					; 程序加载到 cs : 8200h
start:
	;xor ax,ax					; AX = 0   程序加载到0000：100h才能正确执行
    mov ax,cs
	mov es,ax					; ES = 0
	mov ds,ax					; DS = CS
	mov es,ax					; ES = CS
	mov ax,0B800h				; 文本窗口显存起始地址
	mov gs,ax					; GS = B800h
	mov byte[char],'@'

;程序启动延迟

sdelay:
	dec word[count]				; 递减计数变量
	jnz sdelay					; >0：跳转;
	mov word[count],delay
	dec word[dcount]				; 递减计数变量
    jnz sdelay
	mov word[count],delay
	mov word[dcount],ddelay

	call refreshscr
	call bdaryDraw

	mov cx, 100					;设置程序结束时间
pro:
	push cx
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

	;键盘控制移动，w-右上，d-右下，s-左下，a-左上
	mov ah, 0x01
	int 16h
	jz s
	mov ah, 0x00
	int 16h
	cmp al, 'd'
	jz  DnRt
	cmp al, 'w'
	jz UpRt
	cmp al, 'a'
	jz UpLt
	cmp al,'s'
	jz DnLt

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
	;显示姓名-msg
	mov bx, 160*5 + 110 	;屏幕中央
	mov cx, msglen
	mov si, 0
	mov di, 0
showMsg:
	mov al,byte[msg+si]
	mov ah, 0x0f
	mov [gs:bx+di],  ax
	inc si
	add di,2
	loop showMsg

    xor ax,ax                 ; 计算显存地址
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

	pop cx
	dec cx
	cmp cx,0
	jnz pro
	
	call refreshscr

	ret 
         ; 停止画框，无限循环 

;================= 清空屏幕 ===============
refreshscr:
	mov ax, 0x0600
	mov bh, 0x07
	mov cx, 0x0
	mov dx, 0x184f
	INT 0x10
	ret

;================= 边框绘制 ===============
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

;================= 数据区 =================
datadef:	
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt         ; 向右下运动
    x    dw 7			;字符所在行
    y    dw 40			;字符所在列
    char db 'A'
	msg  db 'LuoRenLiang p2'		;姓名
    msglen equ ($-msg)
	bdaryrow db '-'
	bdarycol db '|'


