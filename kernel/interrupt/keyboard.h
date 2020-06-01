#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KB_BUF_SIZE 256
#define KB_READ_PORT 0x60

typedef struct Keyboard
{
    int head;
    int tail;
    int rpos;
    int wpos;
    int count;
    int readcount;
    char code_buf[KB_BUF_SIZE];
    char input_buf[KB_BUF_SIZE];
}Keyboard;

Keyboard kb;



void keyboard_handler();

void init_keyboard();

void keyboard_read();

#endif