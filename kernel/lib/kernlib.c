#include "kernlib.h"
#include "hd.h"



void load_program() {
    uint8_t *p = P_POINT;
    read_disk(0,10,p);
    pro();
}