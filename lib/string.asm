

global memcpy
global printf
global put_char

%include "string.inc"

printf:
    push ebp
    mov ebp, esp
    
    push dword[ebp+8]
    call put_string
    add esp, 4

    pop ebp

    ret

