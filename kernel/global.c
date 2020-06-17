#include "stdio.h"
#include "string.h"
#include "keyboard.h"
#include "int.h"
#include "kernlib.h"
#include "def.h"

char get_char(void) {

    __asm__("sti\r\n");
    enble_irq(KEYBOARD_IRQ);
    while (kb.readcount <= 0)
    {
        keyboard_read();
        //for(i=0;i<30000000;i++) j++;
    }
    
    //printf("?");

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
        if(str[i] == 0x0d || str[i] == ' ') {
            str[i] = 0;
            break;
        }
        i++;
    }
    return str;
}

char * itoa(unsigned int num, char * str) {
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

int strcmp(const char * str1, const char * str2) {
    int i=0;
    while (str1[i] != 0 && str2[i] != 0)
    {
        if(str1[i] == str2[i] ) {
            i++;
            continue;
        }
        else return str1[i]-str2[i];
    }
    if(str1[i] == 0 && str2[i] != 0) return -1;
    if(str1[i] != 0 && str2[i] == 0) return 1;
    return 0;
}

uint32_t strlen(const char *str) {
    int count = 0;
    while (str[count] != 0)
    {
        count++;
    }
    
    return count;
}