[section .text]	; 代码在此

global _start	; 导出 _start
extern kernel
extern gdt_ptr
extern idt_ptr
extern init_gdt



_start:
	mov esp, StackTop
	sgdt [gdt_ptr]
	call init_gdt
	lgdt [gdt_ptr]
	call kernel
	jmp	$

StackSpace		resb	2 * 1024
StackTop:		; 栈顶
