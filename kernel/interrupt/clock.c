#include "clock.h"
#include "int.h"
#include "kernlib.h"

char msg[] = "-\\|/";
int i = 0;

void clock(){

    show(msg[i]);
    i = (i+1) % 4;

    out_byte(M_CTL,0x20);
    __asm__("leave\r\n");
    __asm__("iretl\r\n");
}

void init_clock() {
    set_intGate(TIME_VECTOR,clock);
    enble_irq(TIME_IRQ);
}