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


void init_gdt() {
    memcpy( gdt,
            ((void *)(*(uint32_t *)(&gdt_ptr[2]))),
            (*(uint16_t *)&gdt_ptr[0]) + 1);

    printf("gdt is loaded!\r\n");
    uint32_t *p = (uint32_t *) &gdt_ptr[2];
    *p = &gdt;
    uint16_t *limit = (uint16_t *) gdt_ptr;
    //LGDT((void *)gdt_ptr);
    
    init_gdt_dspt(&(gdt[SelectorLDT >> 3]), &(proc_table[0].ldts), \
                    LDT_SIZE*sizeof(DESCRIPTOR)-1,SEG_LDT);


    memset(&tss,0,sizeof(tss));
    tss.ss0 = SelectorData;
    init_gdt_dspt(&(gdt[SelectorTSS>>3]), (uint32_t)(&tss), \
                    sizeof(tss)-1,SEG_386TSS);
    tss.iobase = sizeof(tss);

    *limit = 47;
}

void init_8259A() {
    out_byte(M_CTL,0x11);       //主 icw1
    out_byte(S_CTL,0x11);       //从 icw1
    out_byte(M_CTLMASK,0x20);   //主 icw2
    out_byte(S_CTLMASK,0x28);   //从 icw2
    out_byte(M_CTLMASK,0x04);   //主 icw3
    out_byte(S_CTLMASK,0x02);   //从 icw3
    out_byte(M_CTLMASK,0x01);   //主 icw4
    out_byte(S_CTLMASK,0x01);   //从 icw4

    out_byte(M_CTLMASK,0xff);
    out_byte(S_CTLMASK,0xff);
}

void init_idt() {
    uint32_t * p = &idt_ptr[2];
    *p = idt;
    uint16_t * limit = &idt_ptr;
    *limit = 0x800;
    //LIDT(idt_ptr);
    //set_intGate(0x21,clock);
    
    int i;
    for(i=0;i<256;i++) set_intGate(i,0x0);

}

void delay() {
    int i, j;
    for(int i=0;i<100000;i++) j++;
}


void taskA() {
    printf("taskA is running!\r\n");
    while(1) {
        printf("A:");
        //put_char('0'+i);
        // i++;
       delay();
    }
    //printf("taskA!");
}

void taskB() {
    printf("taskB is running!\r\n");
    while(1) {
        printf("B:");
        //put_char('0'+i);
        // i++;
       delay();
    }
    //printf("taskA!");
}



int k_reenter;

void init() {
    init_gdt();
    init_idt();
    init_8259A();

    init_clock();
    //enble_irq(0x0);
    init_keyboard();

    init_time();

    //disable_irq(KEYBOARD_IRQ);
    p_proc = proc_table;
    p_proc->ldt_sel = SelectorLDT;
    memcpy(&(p_proc->ldts[0]),&(gdt[SelectorCode>>3]),sizeof(DESCRIPTOR));
    p_proc->ldts[0].attr1 = SEG_C |  PL_TASK << 5;
    memcpy(&(p_proc->ldts[1]),&(gdt[SelectorData>>3]),sizeof(DESCRIPTOR));
    p_proc->ldts[1].attr1 = SEG_DRW |  PL_TASK << 5;

    p_proc->regs.cs = (0 & 0xfff8) | LDT_TI | PL_TASK;
    p_proc->regs.ds = (8 & 0xfff8) | LDT_TI | PL_TASK;
    p_proc->regs.es = (8 & 0xfff8) | LDT_TI | PL_TASK;
    p_proc->regs.fs = (8 & 0xfff8) | LDT_TI | PL_TASK;
    p_proc->regs.ss = (8 & 0xfff8) | LDT_TI | PL_TASK; 
    p_proc->regs.gs = (SelectorVideo+3 & 0xfffd) | PL_TASK;
    p_proc->regs.eip = (uint32_t) taskA;
    p_proc->regs.esp = (uint32_t) Task_Stack+TASK_STACK_SIZE;
    p_proc->regs.eflags = 0x1202;

    k_reenter = 0;

    return;   
}
