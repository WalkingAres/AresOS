#include "stdio.h"
#include "keyboard.h"
#include "kernlib.h"
#include "string.h"
#include "time.h"
#include "hd.h"
#include "clock.h"
#include "proc.h"
#include "syscall.h"

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

#define TASKA_STACK_SIZE 0x1000
#define TASKB_STACK_SIZE 0x1000
#define USER_STACK_SIZE  0x1000
#define STACK_SIZE_TATAL  (TASKA_STACK_SIZE + TASKB_STACK_SIZE + USER_STACK_SIZE)

Process proc_table[NUM_TASKS];          //进程表

uint8_t Task_Stack[TASKA_STACK_SIZE*10];   //进程栈

//**** 系统调用
#define NUM_SYSCALLS 10
_ptr_syscall SysCall_Table[NUM_SYSCALLS];

//**** 8259中断
// #define NUM_INTS 16
// int_handler Int_Table[NUM_INTS];

extern void mulpro();
extern int k_reenter;

void kernel(){

    //__asm__("int $0x21\r\n");

    //printf("hello world!\r\n");
    //char s[] = "hello";
    // printf("@Ares >%d%d",123,321);
    // //printf("%s",s);
    // get_char();
    //__asm__("int $0x21\r\n");

    //enble_irq(KEYBOARD_IRQ);

    //get_char();
    proc_current = proc_table+1;
    // __asm__(
    //     "movl $1, %eax\r\n"
    //     "int $0x80");
    num_proc_alive = 2;
    //mulpro();
    //printf("%d",proc_current->pid);
    //schedule();
    //get_char();
    //load_program(4);
    restart();
    while(1) ;
}
