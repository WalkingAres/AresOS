

#include "stdio.h"
#include "string.h"
#include "keyboard.h"
#include "int.h"
#include "kernlib.h"

char get_char(void) {

    int i, j;
    enble_irq(KEYBOARD_IRQ);
    while (kb.readcount <= 0)
    {
        keyboard_read();
        //for(i=0;i<30000000;i++) j++;
    }
    
    char temp = kb.input_buf[kb.rpos++];
    if(kb.rpos == KB_BUF_SIZE) kb.rpos = 0;

    kb.readcount--;

    disable_irq(KEYBOARD_IRQ);

    return temp;
}

char * get_string(char * str) {
    int i=0;
    while(1) {
        str[i] = get_char();
        if(str[i] == 0x0d) {
            str[i] = 0;
            break;
        }
        i++;
    }
    return str;
}

char * itoa(int num, char * str) {
    int base = 10;
    int b, r , i=0; // num = b*base + r
    char stack[100];
    int top = -1;
    while (1)
    {
        b = num / 10;
        r = num % 10;
        top = top + 1;
        stack[top] = r +'0';
        num = b;
        if(num == 0) break;
    }
    while (top != -1)
    {
       str[i++] = stack[top--];
    }
    str[i] = 0;
    return str;
}