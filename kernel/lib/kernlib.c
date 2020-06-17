#include "kernlib.h"
#include "hd.h"



void load_program(uint8_t id) {
    uint8_t *p = USER_PRO_POINT;
    read_disk((id-1)*2,2,p);
}

void pro() {
    __asm__(
        "movl $0x60400,%eax\r\n"
        "call *%eax\r\n"
        );
}