#include "int.h"
#include "pm.h"
#include "kernlib.h"


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
