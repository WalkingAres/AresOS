#include "clock.h"
#include "int.h"
#include "kernlib.h"
#include "time.h"
#include "pm.h"
#include "proc.h"
#include "global.h"

extern int KernelStackTop;
extern int StackTop;
extern int k_reenter;

char msg[] = "-\\|/";
int wheel;

// void clock(){
//     //__asm__("pop %ebp\r\n");
//     __asm__("sub $4,%esp\r\n");
//     SAVE_REG();
//     __asm__ (
//             "mov   %ss,%dx\r\n"         //进入内核栈
//             "mov   %dx,%ds\r\n"
//             "mov   %dx,%es\r\n"
//             );

//     CLK_EOI();

//     k_reenter++;
//     if(k_reenter != 1) goto reenter;

//     __asm__("movl  $StackTop,%esp\r\n");

//     __asm__("sti\r\n");             //中断重入（嵌套）

//     show(msg[i]);
//     i = (i+1) % 4;

//     get_time();
//     showtime();
//     //printf("clock!");
//     //for(j=0;j<1000000;j++);
//     // out_byte(M_CTL,0x20);
//     // __asm__("sti\r\n");
//     //for(j=0;j<100000;j++);

//     //put_char(clk_reenter+'0');

//     __asm__("cli\r\n");

//     __asm__(
//         "movl (p_proc_ready),%esp\r\n"           //check!
//         "lea 72(%esp),%eax\r\n"
//         "mov  $tss,%edx\r\n"
//         "movl %eax,4(%edx)"
//     );
// reenter:
//     k_reenter--;
//     RET_REG();
//     __asm__("add $4,%esp\r\n");
//    // __asm__("sti\r\n");
//     __asm__("iret\r\n");
// }

void clock() {
    save();
    CLK_EOI();
    __asm__("sti\r\n");
    clock_handler(0);
    __asm__("ret");     // restart()
}

void clock_handler(int irq) {
    FireWheel();
    proc_current->ticks--;
    schedule();
}

void FireWheel() {
    wheel = (wheel + 1)%4;
    show(msg[wheel]);
}


void init_clock() {

    //时钟频率 100hz
    out_byte(0x43,0x34);
    out_byte(0x40,(uint8_t)1193182/100);
    out_byte(0x40,(uint8_t)(1193182/100>> 8));
    
    set_intGate(CLOCK_VECTOR,clock);
    enble_irq(CLOCK_IRQ);
}