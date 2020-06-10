#include "hd.h"
#include "kernlib.h"
#include "stdio.h"
#include "string.h"

char t[10];

void read_disk(uint32_t sec_num, uint8_t num, uint8_t * buf) {

    __asm__("cli\r\n");


    while( (in_byte(CTRL_PORT) & 0x80) != 0) ;


    //printf("not busy!");


    out_byte(NUM_PORT,num);
    out_byte(S_PORT,sec_num & 0x0ff);
    out_byte(C_PORT_LOW,(sec_num >> 8) & 0x0ff);
    out_byte(C_PORT_HIGH, (sec_num >> 16) & 0x0ff);


    out_byte(H_PORT,((sec_num >> 24) & 0x0ff) | 0xe0);


    out_byte(CTRL_PORT,0x20);

    int err = in_byte(STAT_PORT);
    //printf(itoa(err,t));

    while( (in_byte(CTRL_PORT) & 0x08) != 0x08) ;


    //printf("data ready!");

    //err = in_byte(0x1f1);
    //printf(itoa(err,t));

    int num_bytes = num*256;
    int i=0;
    uint16_t *p = (uint16_t *)buf;

    for(i=0;i<num_bytes;i++) p[i] = in_word(DATA_PORT);

    //printf(itoa(p[0],t));

    //printf("@");

    __asm__("sti\r\n");

}