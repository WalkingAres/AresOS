#ifndef KERNLIB_H
#define KERNLIB_H

#include "def.h"


// kernlib.asm
void out_byte(uint16_t port, uint8_t value);    // out dx, al

uint8_t in_byte(uint16_t port);                 // in al, dx

uint16_t in_word(uint16_t port);                // in ax, dx

void show(char ch);
      
#define USER_PRO_POINT 0x60400

void load_program();

//__attribute__((naked))
void pro();

#endif