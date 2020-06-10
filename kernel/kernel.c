#include "stdio.h"
#include "keyboard.h"
#include "kernlib.h"
#include "string.h"
#include "time.h"
#include "hd.h"
#include "clock.h"
#include "proc.h"

void kernel(){

    printf("hello world!\r\n");
    p_proc_ready = proc_table;
    load_program();
    pro();
    //get_char();
    //__asm__("int $0x20");
    //clock();
    //load_program();
    restart();
}
