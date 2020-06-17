#ifndef GLOBAL_H
#define GLOBAL_H

#include "proc.h"
#include "pm.h"
#include "syscall.h"
//内核使用的全局数据

extern uint32_t    gdt_pos;//指向表中最后一个描述符

extern uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
extern DESCRIPTOR	gdt[GDT_SIZE];
extern uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
extern GATE		idt[IDT_SIZE];
extern TSS			tss;

#define NUM_TASKS 3
extern int num_proc_alive;

extern Process *p_proc_ready;  

#define TASKA_STACK_SIZE 0x8000
#define TASKB_STACK_SIZE 0x8000
#define USER_STACK_SIZE  0x8000
#define STACK_SIZE_TATAL  (TASKA_STACK_SIZE + TASKB_STACK_SIZE + USER_STACK_SIZE)

extern Process proc_table[NUM_TASKS];

extern uint8_t Task_Stack[STACK_SIZE_TATAL];

#define NUM_SYSCALLS 10
extern _ptr_syscall SysCall_Table[NUM_SYSCALLS];
#endif