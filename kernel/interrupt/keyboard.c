#include "keyboard.h"
#include "stdio.h"
#include "pm.h"
#include "kernlib.h"
#include "stdio.h"
#include "int.h"
#include "keymap.h"




static int col_flag = 0;
static int shift_l = 0;
static int shift_r = 0;

void keyboard_handler() {

    uint8_t scan_code = in_byte(KB_READ_PORT);
    
    //printf("!");

    if(kb.count < KB_BUF_SIZE) {
        *(kb.p_head) = scan_code;
        kb.p_head++;
        if(kb.p_head == kb.code_buf + KB_BUF_SIZE) kb.p_head = kb.code_buf;
        kb.count++;

    }



    out_byte(M_CTL,0x20);
    __asm__("leave\r\n");
    __asm__("iretl\r\n");
}

void init_keyboard() {

    kb.count = 0;
    kb.readcount = 0;
    kb.p_head = kb.p_tail = kb.code_buf;
    kb.p_read = kb.p_input = kb.input_buf;

    set_intGate(KEYBOARD_VECTOR,keyboard_handler);
    //enble_irq(KEYBOARD_IRQ);
}

static int col_flag;

void keyboard_read() {

    __asm__("cli\r\n");

    uint8_t scan_code;
    int make;
    uint8_t key;
    uint8_t * map_row;

    if(kb.count > 0) {
        //printf("@");
                //put_char(kb.count+'0');
        scan_code = *(kb.p_tail);
        kb.p_tail++;
        if(kb.p_tail == kb.code_buf + KB_BUF_SIZE) kb.p_tail = kb.code_buf;
        kb.count = kb.count - 1;

        switch (scan_code)
        {
        case 0xe1:
            /* code */
            break;
        case 0xe0:
            break;
        default:
            {
                make = (scan_code&0x80)? 0:1;
                map_row = &keymap[(scan_code&0x7f)*MAP_COL];
                col_flag = 0;
                if(shift_l == 1 || shift_r == 1) {
                    col_flag = 1;
                }

                key = map_row[col_flag];
                switch (key)
                {
                case SHIFT_L:
                    shift_l = make;
                    key = 0;
                    break;
                case SHIFT_R:
                    shift_r = make;
                    key = 0;
                    break;
                default:
                    if(!make) key = 0;
                    break;
                }
                break;
            }
        }

        if(key != 0) {
            *(kb.p_input) = key;
            kb.p_input++;
            kb.readcount++;
            if(kb.p_input == kb.input_buf + KB_BUF_SIZE) 
                kb.p_input = kb.input_buf;
            //put_char(key);
        }
        
        //put_char(kb.readcount+'0');

    }

    __asm__("sti\r\n");

}