#ifndef KERNLIB_H
#define KERNLIB_H

#include "def.h"

void out_byte(uint16_t port, uint8_t value);
uint8_t in_byte(uint16_t port);
void LGDT(void * gdt_ptr);
void LIDT(void * idt_ptr);
void CLI();
void STI();
void POP_AD();
void PUSH_AD();
void savereg();
void retreg();

void show(char ch);

#endif