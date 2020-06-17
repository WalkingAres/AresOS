#include "keyboard.h"
#include "stdio.h"
#include "pm.h"
#include "kernlib.h"
#include "stdio.h"
#include "int.h"
#include "keymap.h"
#include "string.h"



static int col_flag     = 0;
static int shift_l      = 0;
static int shift_r      = 0;
static int caps_lock    = 0;
static int ctrl_flag    = 0;


void keyboard_handler() {

    save();

    EOI_KB;

    uint8_t scan_code = in_byte(KB_READ_PORT);

    if(kb.count < KB_BUF_SIZE) {
        kb.code_buf[kb.head++] = scan_code;

        if(kb.head == KB_BUF_SIZE ) kb.head = 0;

        kb.count++;
    }

    RET;
}

void init_keyboard() {

    kb.head = kb.tail = kb.rpos = kb.wpos = 0;
    kb.count = 0;
    kb.readcount = 0;
    col_flag     = 0;
    shift_l      = 0;
    shift_r      = 0;
    caps_lock    = 0;
    ctrl_flag    = 0;
    set_intGate(KEYBOARD_VECTOR,keyboard_handler);
    //enble_irq(KEYBOARD_IRQ);
}

static int col_flag;

void keyboard_read() {

    uint8_t scan_code;
    int make;
    uint8_t key;
    uint8_t * map_row;

    if(kb.count > 0) {
        //printf("!");
        disable_irq(KEYBOARD_IRQ);
        //put_char(kb.count+'0');
        scan_code = kb.code_buf[kb.tail++];
        if(kb.tail == KB_BUF_SIZE) kb.tail = 0;
        kb.count = kb.count - 1;
        enble_irq(KEYBOARD_IRQ);
        //printf(itoa(scan_code,t));
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
                if(shift_l == 1 || shift_r == 1 || caps_lock == 1) {
                    col_flag = 1;
                }
            
                key = map_row[col_flag];
                //printf(itoa(key,t));
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
                case CAPS_LOCK:
                    caps_lock = make;
                    key = 0;
                    break;
                case ENTER:
                    //put_char('@');
                    ctrl_flag = make;
                    break;
                default:
                    if(!make) key = 0;
                    break;
                }
                break;
            }
        }

        if(key != 0) {
            //printf("#");
            if(!ctrl_flag) put_char(key);
            //put_char(ctrl_flag+'0');
            kb.input_buf[kb.wpos++] = key; 
            if(kb.wpos == KB_BUF_SIZE) kb.wpos = 0;
            kb.readcount++;
        }

    }
}