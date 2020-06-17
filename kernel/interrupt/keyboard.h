#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KB_BUF_SIZE 256
#define KB_READ_PORT 0x60

typedef struct Keyboard
{
    int head;       //ɨ����λ��
    int tail;
    int rpos;       //��λ��
    int wpos;       //дλ��
    int count;      //����
    int readcount;  //�������Ŀɶ���
    char code_buf[KB_BUF_SIZE];//ɨ����
    char input_buf[KB_BUF_SIZE];//���������뻺����
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