#ifndef PROC_H
#define PROC_H

#include "def.h"
#include "pm.h"


typedef struct proc_stackframe {

    //保存现场 save()
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t kernel_esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t ret_addr;  //save()的返回地址

    //中断处理保存的寄存器
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
}StackFrame;

typedef struct process
{
    StackFrame regs;

    uint16_t ldt_sel;
    DESCRIPTOR ldts[LDT_SIZE];
    uint32_t pid;
    char p_name[16];
}Process;

#define NUM_TASKS 1

Process proc_table[NUM_TASKS];

Process *p_proc;
Process *p_proc_ready;

#define TASK_STACK_SIZE 0x8000

uint8_t Task_Stack[TASK_STACK_SIZE];

#endif