global show

show:
    push ebp
    mov ebp, esp
    push eax

    mov al, [ebp+8]
    mov ah, 0x07
    mov [gs:160*12+80],ax

    pop eax

    pop ebp

    ret
