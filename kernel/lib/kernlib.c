#include "kernlib.h"
#include "hd.h"


void load_program(uint8_t id) {
    uint8_t *p = (uint8_t *) USER_PRO_POINT + 0x400*(id-1);
    read_disk((id-1)*2,2,p);
}

void pro() {
    __asm__(
        "movl $0x60800,%eax\r\n"
        "call *%eax\r\n"
        );
}