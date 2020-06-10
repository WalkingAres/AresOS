#include "def.h"
#include "stdio.h"
#include "string.h"
#include "pm.h"
#include "proto.h"
#include "kernlib.h"
#include "int.h"
#include "clock.h"
#include "keyboard.h"
#include "time.h"
#include "proc.h"

void init_gdt()
{
    memcpy(gdt,
           ((void *)(*(uint32_t *)(&gdt_ptr[2]))),
           (*(uint16_t *)&gdt_ptr[0]) + 1);

    printf("gdt is loaded!\r\n");
    uint32_t *p = (uint32_t *)&gdt_ptr[2];
    *p = &gdt;
    uint16_t *limit = (uint16_t *)gdt_ptr;
    //LGDT((void *)gdt_ptr);

    int i;
    Process *proc = proc_table;
    uint16_t ldt_sel = SelectorLDT;
    for(i=0;i<NUM_TASKS;i++){
        init_gdt_dspt(&(gdt[ldt_sel >> 3]),proc->ldts,\
                  LDT_SIZE * sizeof(DESCRIPTOR) - 1, SEG_LDT);  
        proc++;
        ldt_sel += 8;
    }

    // init_gdt_dspt(&(gdt[SelectorLDT >> 3]), &(proc_table[0].ldts),
    //               LDT_SIZE * sizeof(DESCRIPTOR) - 1, SEG_LDT);

    memset(&tss, 0, sizeof(tss));
    tss.ss0 = SelectorData; //内核栈
    init_gdt_dspt(&(gdt[SelectorTSS >> 3]), (uint32_t)(&tss),
                  sizeof(tss) - 1, SEG_386TSS);
    tss.iobase = sizeof(tss);

    *limit = 63;
}

void init_8259A()
{
    out_byte(M_CTL, 0x11);     //主 icw1
    out_byte(S_CTL, 0x11);     //从 icw1
    out_byte(M_CTLMASK, 0x20); //主 icw2
    out_byte(S_CTLMASK, 0x28); //从 icw2
    out_byte(M_CTLMASK, 0x04); //主 icw3
    out_byte(S_CTLMASK, 0x02); //从 icw3
    out_byte(M_CTLMASK, 0x01); //主 icw4
    out_byte(S_CTLMASK, 0x01); //从 icw4

    out_byte(M_CTLMASK, 0xff);
    out_byte(S_CTLMASK, 0xff);
}

void init_idt()
{
    uint32_t *p = &idt_ptr[2];
    *p = idt;
    uint16_t *limit = &idt_ptr;
    *limit = 0x800;
    //LIDT(idt_ptr);
    //set_intGate(0x21,clock);

    int i;
    for (i = 0; i < 256; i++)
        set_intGate(i, 0x0);
}

void delay()
{
    int i, j;
    for (int i = 0; i < 1000000; i++)
        j++;
}

void taskA()
{
    printf("taskA is running!\r\n");
    while (1)
    {
        printf("A:");
        //put_char('0'+i);
        // i++;
        delay();
        delay();
    }
    //printf("taskA!");
}

void taskB()
{
    printf("taskB is running!\r\n");
    while (1)
    {
        printf("B:");
        //put_char('0'+i);
        // i++;
        delay();
    }
    //printf("taskA!");
}


int k_reenter;
Task    task_table[NUM_TASKS]={
    {taskA,TASKA_STACK_SIZE,"A"},
    {taskB,TASKB_STACK_SIZE,"B"},
    {pro,USER_STACK_SIZE,"User pro"}
};

void init()
{
    init_gdt();
    init_idt();
    init_8259A();

    init_clock();
    //enble_irq(0x0);
    init_keyboard();

    init_time();

    Task *task = task_table;
    Process *proc = proc_table;
    char *task_stack = Task_Stack + STACK_SIZE_TATAL;
    uint32_t ldt_sel = SelectorLDT;
    int i;
    for (i = 0; i < NUM_TASKS; i++)
    {
        proc->pid = i;
        proc->ldt_sel = ldt_sel;
        memcpy(&(proc->ldts[0]), &(gdt[SelectorCode >> 3]), sizeof(DESCRIPTOR));
        proc->ldts[0].attr1 = SEG_C | PL_TASK << 5;
        memcpy(&(proc->ldts[1]), &(gdt[SelectorData >> 3]), sizeof(DESCRIPTOR));
        proc->ldts[1].attr1 = SEG_DRW | PL_TASK << 5;

        proc->regs.cs = (0 & 0xfff8) | LDT_TI | PL_TASK;
        proc->regs.ds = (8 & 0xfff8) | LDT_TI | PL_TASK;
        proc->regs.es = (8 & 0xfff8) | LDT_TI | PL_TASK;
        proc->regs.fs = (8 & 0xfff8) | LDT_TI | PL_TASK;
        proc->regs.ss = (8 & 0xfff8) | LDT_TI | PL_TASK;
        proc->regs.gs = (SelectorVideo + 3 & 0xfffd) | PL_TASK;
        proc->regs.eip = (uint32_t)task->eip;
        proc->regs.esp = (uint32_t)task_stack;
        proc->regs.eflags = 0x1202;

        task_stack = task_stack - task->stacksize;
        proc++;
        task++;
        ldt_sel = ldt_sel + 8;
    }

    k_reenter = 0;

    //disable_irq(CLOCK_IRQ);

    return;
}
