#ifndef GLOBAL_H
#define GLOBAL_H

#include "proc.h"
#include "pm.h"
#include "syscall.h"
#include "malloc.h"
//内核使用的全局数据

extern uint32_t    gdt_pos;//指向表中最后一个描述符

extern uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
extern DESCRIPTOR	gdt[GDT_SIZE];
extern uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
extern GATE		idt[IDT_SIZE];
extern TSS			tss;

#define NUM_TASKS 10
extern int num_proc_alive;
extern int k_reenter;

extern Process *proc_current;  
extern ProcNode *procCurrent;
extern ProcNode *procReady;
extern ProcNode *procDied;
extern ProcNode *procSleep;

#define TASK_STACK_SIZE 0x1000
#define USER_STACK_SIZE  0x1000

extern Process proc_table[NUM_TASKS];

extern uint8_t Task_Stack[TASK_STACK_SIZE*10];


extern const uint8_t *phyMem;

#define NUM_SYSCALLS 10

extern _ptr_syscall SysCall_Table[NUM_SYSCALLS];

extern MemBlock * MemHead;
#define MEM_ADDR 0x100000

#endif