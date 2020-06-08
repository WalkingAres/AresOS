#include "stdio.h"
#include "keyboard.h"
#include "kernlib.h"
#include "string.h"
#include "time.h"
#include "hd.h"
#include "proc.h"

void kernel(){

    printf("hello world!\r\n");
    p_proc_ready = proc_table;
    //get_char();

    restart();
}
