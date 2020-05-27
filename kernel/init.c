#include "def.h"
#include "stdio.h"
#include "string.h"
#include "pm.h"
#include "proto.h"
#include "kernlib.h"
#include "int.h"
#include "clock.h"
#include "keyboard.h"

void init_gdt() {
    memcpy( gdt,
            ((void *)(*(uint32_t *)(&gdt_ptr[2]))),
            (*(uint16_t *)&gdt_ptr[0]) + 1);

    printf("gdt is loaded!\r\n");
    uint32_t *p = &gdt_ptr[2];
    *p = &gdt;
    //LGDT((void *)gdt_ptr);
    return;
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

    // 8253
    out_byte(0x43,0x34);
    out_byte(0x40,(uint8_t)119182/100);
    out_byte(0x40,(uint8_t)(119182/100 >> 8));
}

void init() {
    init_gdt();
    init_idt();
    init_8259A();

    init_clock();
    //enble_irq(0x0);
    init_keyboard();

    //disable_irq(KEYBOARD_IRQ);

    return;   
}
