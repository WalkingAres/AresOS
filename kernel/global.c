

#include "stdio.h"
#include "string.h"
#include "keyboard.h"
#include "int.h"
#include "kernlib.h"

char get_char(void) {

    int i;
    int j;
    int a= 0;
    enble_irq(KEYBOARD_IRQ);
    while(kb.readcount <= 0) {
        keyboard_read();
        for(i =0; i<0x1000;i++)
            for(j=0;j<0x1000;j++) {
                a++;
            }
     }

    disable_irq(KEYBOARD_IRQ);
    //put_char(kb.readcount+'0');
    //put_char(kb.count+'0');

    char temp = *kb.p_read;
    kb.p_read++;
    if(kb.p_read == kb.input_buf + KB_BUF_SIZE) 
        kb.p_read = kb.input_buf;
    kb.readcount--;

    //printf("#");
    //put_char(kb.readcount+'0');

    return temp;
}