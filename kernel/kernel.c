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

//**** ����ģʽ
uint32_t    gdt_pos;//ָ��������һ��������

uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
DESCRIPTOR	gdt[GDT_SIZE];
uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
GATE		idt[IDT_SIZE];
TSS			tss;

//**** ������ص�����
#define NUM_TASKS 10     //����߳���
int num_proc_alive;     //��ǰ���߳�

// Process *p_proc_ready;
Process *proc_current;

ProcNode *procCurrent;  //cpu ����ִ�е��߳�
ProcNode *procReady;    //׼���������̶߳���
ProcNode *procDied;     //�����̶߳���
ProcNode *procSleep;    //�����������̶߳���

#define TASK_STACK_SIZE 0x1000
#define USER_STACK_SIZE  0x1000

Process proc_table[NUM_TASKS];          //���̱�

uint8_t Task_Stack[TASK_STACK_SIZE*10];   //����ջ

uint32_t pid_map;

//**** ϵͳ����
#define NUM_SYSCALLS 10
_ptr_syscall SysCall_Table[NUM_SYSCALLS];

//**** 8259�ж�
// #define NUM_INTS 16
// int_handler Int_Table[NUM_INTS];

/**** Memmory Manager
     0x100000��0x1100000 16MB�Ŀɷ�����ڴ�ռ�
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
