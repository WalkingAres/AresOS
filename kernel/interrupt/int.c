#include "int.h"
#include "pm.h"
#include "kernlib.h"
#include "proc.h"
#include "global.h"

extern int k_reenter;
extern int StackTop;


void save(){
    //�����ֳ�
    __asm__(
        "pusha\r\n"         
        "push %ds\r\n"      
        "push %es\r\n"      
        "push %fs\r\n"      
        "push %gs\r\n"      
        "mov  %ss,%dx\r\n"  
        "mov  %dx,%ds\r\n"  
        "mov  %dx,%es\r\n"  
    );

    k_reenter++;
    if(k_reenter != 0) goto reenter;

    __asm__(
        "mov %esp,%edx\r\n"     //edx = pcb ��ʼ��ַ
        "movl  $StackTop,%esp\r\n"  //�����ں�ջ
        "push $restart\r\n"
        "jmp *48(%edx)"        //�ص�clock()
        );

reenter:
    __asm__(
        "mov %esp,%edx\r\n"     //edx = pcb ��ʼ��ַ
        "push $restart_reenter\r\n"
        "jmp *48(%edx)"        
    ); 
}

void restart() {
    __asm__(
        "movl (p_proc_ready),%esp\r\n"           //check!
        "lldt pcb_ldt_sel(%esp)\r\n"             //pcb_ldt_sel = 72
        "lea 72(%esp),%eax\r\n"                  //
        "mov  $tss,%edx\r\n"
        "movl %eax,4(%edx)\r\n"                 //tss�л�  �л����ں�ջ sp0 = pcb��stack_frame�Ķ���
        "restart_reenter:\r\n"
    );
    k_reenter--;
    __asm__(
        "pop %gs\r\n"
        "pop %fs\r\n"
        "pop %es\r\n"
        "pop %ds\r\n"
        "popa\r\n"
        "add $4,%esp\r\n"
        "iret\r\n"
    );
}

void enble_irq(uint8_t irq) {
    if(irq < 8) {
        out_byte(M_CTLMASK, (in_byte(M_CTLMASK) & ~(1 << irq)) );
    }
    else
    {
        out_byte(S_CTLMASK, (in_byte(S_CTLMASK) & ~(1<<(irq-8))) );
    }
}

void disable_irq(uint8_t irq) {
    if(irq < 8) {
        out_byte(M_CTLMASK, (in_byte(M_CTLMASK) | (1 << irq)) );
    }
    else
    {
        out_byte(S_CTLMASK, (in_byte(S_CTLMASK) | (1<<(irq-8))) );
    }
}



void set_intGate(uint8_t vector, int_handler proc){
    init_idt_dspt(&idt[vector],proc,SelectorCode,SEG_IGate,0);
}
