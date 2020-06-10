#include "kernlib.h"
#include "hd.h"



void load_program() {
    uint8_t *p = USER_PRO_POINT;
    read_disk(0,10,p);
}

void pro() {
a:
    __asm__(
        "movl $0x60400,%eax\r\n"
        "call *%eax\r\n"
        );
    goto a;
}