#include "stdio.h"
#include "keyboard.h"
#include "kernlib.h"
#include "string.h"
#include "time.h"
#include "hd.h"
#include "clock.h"
#include "proc.h"
#include "syscall.h"
#include "malloc.h"

//**** 保护模式
uint32_t    gdt_pos;//指向表中最后一个描述符

uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
DESCRIPTOR	gdt[GDT_SIZE];
uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
GATE		idt[IDT_SIZE];
TSS			tss;

//**** 进程相关的数据
#define NUM_TASKS 10     //最大线程数
int num_proc_alive;     //当前的线程

// Process *p_proc_ready;
Process *proc_current;

ProcNode *procCurrent;  //cpu 正在执行的线程
ProcNode *procReady;    //准备就绪的线程队列
ProcNode *procDied;     //结束线程队列
ProcNode *procSleep;    //阻塞或挂起的线程队列

#define TASK_STACK_SIZE 0x1000
#define USER_STACK_SIZE  0x1000

Process proc_table[NUM_TASKS];          //进程表

uint8_t Task_Stack[TASK_STACK_SIZE*10];   //进程栈

uint32_t pid_map;

//**** 系统调用
#define NUM_SYSCALLS 10
_ptr_syscall SysCall_Table[NUM_SYSCALLS];

//**** 8259中断
// #define NUM_INTS 16
// int_handler Int_Table[NUM_INTS];

/**** Memmory Manager
     0x100000～0x1100000 16MB的可分配的内存空间
****/

MemBlock * MemHead;

#define MEM_ADDR 0x100000

extern void mulpro();
extern int k_reenter;
extern void _shell();

void kernel(){

    proc_current = proc_table;

    restart();
    while(1) ;
}
