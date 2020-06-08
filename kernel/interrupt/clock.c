#include "clock.h"
#include "int.h"
#include "kernlib.h"
#include "time.h"
#include "pm.h"

extern int KernelStackTop;
extern int StackTop;

char msg[] = "-\\|/";
int i = 0;

void clock(){
    __asm__("pop %ebp\r\n");
    __asm__("sub $4,%esp\r\n");
    SAVE_REG();
    __asm__ (
            "mov   %ss,%dx\r\n"         //½øÈëÄÚºËÕ»
            "mov   %dx,%ds\r\n"
            "mov   %dx,%es\r\n"
            "movl   $StackTop,%esp"    //check!
            );

    show(msg[i]);
    i = (i+1) % 4;

    get_time();
    showtime();
    out_byte(M_CTL,0x20);

    __asm__(
        "movl (p_proc_ready),%esp\r\n"           //check!
        "lea 72(%esp),%eax\r\n"
        "mov  $tss,%edx\r\n"
        "movl %eax,4(%edx)"
    );

    RET_REG();
    __asm__("add $4,%esp\r\n");
    __asm__("sti\r\n");
    __asm__("iret\r\n");
}

void init_clock() {

    out_byte(0x43,0x34);
    out_byte(0x40,(uint8_t)119182/100);
    out_byte(0x40,(uint8_t)(119182/100 >> 8));
    
    set_intGate(CLOCK_VECTOR,clock);
    enble_irq(CLOCK_IRQ);
}