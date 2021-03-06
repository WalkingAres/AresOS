#ifndef INT_H
#define INT_H

#include "stdio.h"
#include "def.h"
// 8259

#define M_CTL 0x20
#define M_CTLMASK 0x21
#define S_CTL 0xa0
#define S_CTLMASK 0xa1

#define CLOCK_IRQ 0
#define KEYBOARD_IRQ 1
#define TIME_IRQ 8

#define CLOCK_VECTOR 0x20
#define KEYBOARD_VECTOR 0x21
#define TIME_VECTOR 0x28


#define RET __asm__("ret\r\n");

__attribute__((naked))  
void save();

__attribute__((naked))
void restart();

void enble_irq(uint8_t irq);

void disable_irq(uint8_t irq);

typedef void (*int_handler)();

void set_intGate(uint8_t vector, int_handler handle);


#endif