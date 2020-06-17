#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KB_BUF_SIZE 256
#define KB_READ_PORT 0x60

typedef struct Keyboard
{
    int head;       //扫描码位置
    int tail;
    int rpos;       //读位置
    int wpos;       //写位置
    int count;      //计数
    int readcount;  //缓冲区的可读数
    char code_buf[KB_BUF_SIZE];//扫描码
    char input_buf[KB_BUF_SIZE];//解析后输入缓冲区
}Keyboard;

Keyboard kb;

#define EOI_KB __asm__("mov $0x20, %al\r\n" \
                       "out %al, $0x20"     \
                      )
                      
__attribute__((naked))
void keyboard_handler();

void init_keyboard();

void keyboard_read();

#endif