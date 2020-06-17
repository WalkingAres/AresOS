#include "stdio.h"
#include "keyboard.h"
#include "kernlib.h"
#include "string.h"
#include "time.h"
#include "hd.h"
#include "clock.h"
#include "proc.h"
#include "syscall.h"

//**** ����ģʽ
uint32_t    gdt_pos;//ָ��������һ��������

uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
DESCRIPTOR	gdt[GDT_SIZE];
uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
GATE		idt[IDT_SIZE];
TSS			tss;

//**** ������ص�����
#define NUM_TASKS 3     //����߳���
int num_proc_alive;     //��ǰ���߳�

Process *p_proc_ready;  

#define TASKA_STACK_SIZE 0x8000
#define TASKB_STACK_SIZE 0x8000
#define USER_STACK_SIZE  0x8000
#define STACK_SIZE_TATAL  (TASKA_STACK_SIZE + TASKB_STACK_SIZE + USER_STACK_SIZE)

Process proc_table[NUM_TASKS];          //���̱�

uint8_t Task_Stack[STACK_SIZE_TATAL];   //����ջ

//**** ϵͳ����
#define NUM_SYSCALLS 10
_ptr_syscall SysCall_Table[NUM_SYSCALLS];

//**** 8259�ж�
// #define NUM_INTS 16
// int_handler Int_Table[NUM_INTS];


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
    

    p_proc_ready = proc_table;
    __asm__(
        "movl $1, %eax\r\n"
        "int $0x80");
    num_proc_alive = 2;
    //schedule();
    //get_char();
    //load_program(4);
    restart();
    while(1) ;
}
