#ifndef CLOCK_H
#define CLOCK_H

__attribute__((naked))
void clock();

void init_clock();

#define CLK_EOI()                       \
    __asm__ (                           \
            "movb   $0x20,%al\r\n"      \
            "outb   %al,$0x20"          \
            );


#endif