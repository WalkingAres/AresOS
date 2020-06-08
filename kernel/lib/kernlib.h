#ifndef KERNLIB_H
#define KERNLIB_H

#include "def.h"


// kernlib.asm
void out_byte(uint16_t port, uint8_t value);    // out dx, al

uint8_t in_byte(uint16_t port);                 // in al, dx

uint16_t in_word(uint16_t port);                // in ax, dx

void show(char ch);

//kernel.asm
void restart();


#define SAVE_REG()              \
    __asm__("pusha\r\n");       \
    __asm__("push %ds\r\n");    \
    __asm__("push %es\r\n");    \
    __asm__("push %fs\r\n");    \
    __asm__("push %gs\r\n");  

#define RET_REG() \
    __asm__("pop %gs\r\n");     \
    __asm__("pop %fs\r\n");     \
    __asm__("pop %es\r\n");     \
    __asm__("pop %ds\r\n");     \
    __asm__("popa\r\n");        


#define P_POINT 0x40400

void load_program();


#endif