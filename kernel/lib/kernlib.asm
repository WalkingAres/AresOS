
global out_byte
global in_byte
global LGDT
global LIDT
global CLI
global STI

;========= void out_byte(uint16_t port, uint8_t value)

out_byte:

    push edx
    push eax

	mov	edx, [esp + 12]		; port
	mov	eax, [esp+16]	; value
	out	dx, al
	nop	
	nop

    pop eax
    pop edx

	ret

;========= uint8_t in_byte(uint16_t port)

in_byte:

    push edx

    mov edx, [esp+8]
    xor eax, eax
    in al, dx

    nop
    nop

    pop edx

    ret

LGDT:

    lgdt [eax]

    ret

LIDT:

    lidt [eax]

    ret 

CLI:

    cli

    ret

STI:

    sti

    ret