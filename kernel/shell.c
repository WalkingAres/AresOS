#include "global.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "kernlib.h"

typedef enum shell_cmd {
    HELP,
    A,
    B,
    C,
    D,
    TIME,
    CLEAR
}cmd_key;


cmd_key get_cmd_key(const char * cmd) {
    int len = strlen(cmd);
    int i=0;
    if(!strcmp(cmd,"help")) return HELP;
    if(!strcmp(cmd,"time")) return TIME;
    if(!strcmp(cmd,"a")) return A;
    if(!strcmp(cmd,"b")) return B;
    if(!strcmp(cmd,"c")) return C;
    if(!strcmp(cmd,"d")) return D;
    if(!strcmp(cmd,"clear")) return CLEAR;
}

void clear_screen() {
    int i=0;
    while(i<160*25){
        __asm__("mov $0x0720,%%ax\r\n"
                "mov %%ax, %%gs:(%0)"
                ::"b"(i));
        i += 2;
    }
    out_byte(0x3d4,0xe);
    out_byte(0x3d5,0);
    out_byte(0x3d4,0xf);
    out_byte(0x3d5, 0); 
}

void help() {
    printf("\r\n");
    printf("a b c d:run a user program *\n\r");
    printf("time:show the real time\r\n");
    printf("clear:clear the screen\r\n");
}

void cmd_time(){
    get_time();
    showtime();
    printf("press any key to continue...");
    get_char();
}

void user_pro(cmd_key key) {
    clear_screen();
    enble_irq(KEYBOARD_IRQ);
    load_program(key);
    exec();
    clear_screen();
    disable_irq(KEYBOARD_IRQ);
}


void _shell() {
    char cmd[100];
    cmd_key key;
    clear_screen();
    while(1) {
        printf("@Ares >");
        get_string(cmd);
        key  = get_cmd_key(cmd);
        switch (key)
        {
        case HELP:
            help();
            break;
        case TIME:
            cmd_time();
            break;
        case A:
        case B:
        case C:
        case D:
            user_pro(key);
            break;
        case CLEAR:
            clear_screen();
            break;
        default:
            printf("\r\ncommand not found!\r\n");
            break;
        }
    }
}