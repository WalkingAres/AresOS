[section .text]	; 代码在此

global _start	; 导出 _start
extern kernel
extern gdt_ptr
extern idt_ptr
extern init_gdt
extern init_idt
extern init
extern clock



_start:
	;cli
	mov esp, StackTop
	;call clock
	sgdt [gdt_ptr]
	call init
	lgdt [gdt_ptr]
	lidt [idt_ptr]
	sti
	call kernel
	;sti
	;int 0x28
	jmp	$

StackSpace		resb	2 * 1024
StackTop:		; 栈顶

