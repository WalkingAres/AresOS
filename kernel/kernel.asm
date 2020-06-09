[section .text]	; 代码在此

global _start	; 导出 _start
global restart
global KernelStackTop
global StackTop
global pcb_ldt_sel

extern kernel
extern gdt_ptr
extern idt_ptr
extern init_gdt
extern init_idt
extern init
extern clock
extern p_proc_ready
extern tss

Sel_Tss equ 0x20

;=== pcb 寄存器偏移量
pcb_stackbase 	equ 0
pcb_gs			equ pcb_stackbase			;0
pcb_fs			equ pcb_gs			+	4	;4
pcb_es			equ pcb_fs			+	4	;8
pcb_ds			equ pcb_es			+	4	;12
pcb_edi			equ pcb_ds			+	4	;16
pcb_esi			equ pcb_edi			+	4	;20
pcb_ebp			equ pcb_esi			+	4	;24
pcb_kernel_esp	equ pcb_ebp			+	4	;28
pcb_ebx			equ pcb_kernel_esp	+	4	;32
pcb_edx			equ pcb_ebx			+	4	;36
pcb_ecx			equ pcb_edx			+	4	;40
pcb_eax			equ pcb_ecx			+	4	;44
pcb_retaddr		equ pcb_eax			+	4	;48
pcb_eip			equ pcb_retaddr		+	4	;52
pcb_cs 			equ pcb_eip			+	4	;56
pcb_eflags		equ pcb_cs			+	4	;60
pcb_esp 		equ pcb_eflags		+	4	;64
pcb_ss			equ pcb_esp			+	4	;68
pcb_stacktop	equ	pcb_ss			+	4	;72
pcb_ldt_sel		equ pcb_stacktop			;72
pcb_ldt			equ	pcb_ldt_sel		+	4	;76

tss_sp0			equ 4



_start:
	;cli
	mov esp, StackTop
	;call clock
	sgdt [gdt_ptr]
	call init
	lgdt [gdt_ptr]
	lidt [idt_ptr]
	;sti

	xor eax, eax
	mov	ax, Sel_Tss
	ltr	ax

	jmp 0x08:start

start:
	;int 0x20
	call kernel
	;sti
	;int 0x28
	jmp	$

StackSpace		resb	2 * 1024
StackTop:		; 栈顶

KernelStackSpace		resb	2 * 1024
KernelStackTop:		; 栈顶

;restart:
;	mov esp, [p_proc_ready]
;	lldt	[esp+pcb_ldt_sel]
;	lea		eax, [esp + pcb_stacktop]
;	mov dword [tss+tss_sp0], eax

;	pop gs
;	pop fs
;	pop es
;	pop ds
;	popad
;
;	add esp,4
;
;	iretd