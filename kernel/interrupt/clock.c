#include "clock.h"
#include "int.h"
#include "kernlib.h"
#include "time.h"

char msg[] = "-\\|/";
int i = 0;

void clock(){

    __asm__("pusha\r\n");
    __asm__("pushf\r\n");


    show(msg[i]);
    i = (i+1) % 4;

    get_time();
    showtime();
    

    __asm__("popf\r\n");
    __asm__("popa\r\n");


    out_byte(M_CTL,0x20);
    __asm__("leave\r\n");
    __asm__("iretl\r\n");
}

void init_clock() {
    set_intGate(CLOCK_VECTOR,clock);
    enble_irq(CLOCK_IRQ);
}