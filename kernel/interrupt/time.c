#include "time.h"
#include "int.h"
#include "kernlib.h"
#include "string.h"
#include "stdio.h"

int bcd_to_int(uint8_t code) {
    int a = 0;
    int base = 1;
    while(code !=0 ) {
        a = a +(code & 0x0f) * base;
        code = code >> 4;
        base = 10 *base;
    }
    return a;
}

void showtime() {
    int s_high, s_low;
    int wport = 0x3d4;
    int rport = 0x3d5;
    out_byte(wport,0xe);
    s_high = in_byte(rport);
    out_byte(wport,0xf);
    s_low = in_byte(rport);

    int pos = 80*24;
    //设置光标到最后一行首
    out_byte(wport,0xe);
    out_byte(rport,(pos >> 8) & 0x0ff);
    out_byte(wport,0xf);
    out_byte(rport, pos & 0x0ff); 


    char temp[20];
    printf( itoa(_time.year,temp) );
    printf("-");
    if(_time.month < 10) printf("0");
    printf( itoa(_time.month,temp));
    printf("-");
    if(_time.day < 10) printf("0");
    printf( itoa( _time.day, temp));
    printf(" ");
    if(_time.hour < 10) printf("0");
    printf(itoa( _time.hour, temp));
    printf(":");
    if(_time.min < 10) printf("0");
    printf(itoa( _time.min, temp));
    printf(":");
    if(_time.sec < 10) printf("0");
    printf(itoa( _time.sec, temp));

    out_byte(wport,0xe);
    out_byte(rport,s_high);
    out_byte(wport,0xf);
    out_byte(rport, s_low ); 

}


void get_time() {

    out_byte(TIME_INDEX_PORT,YEAR);
    _time.year = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,MON);
    _time.month = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,DAY);
    _time.day = bcd_to_int( in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,WEEK);
    _time.week = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,HOUR);
    _time.hour = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,MIN);
    _time.min = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,SEC);
    _time.sec = bcd_to_int(in_byte(TIME_DATA_PORT));

}




void time_handler(){

    __asm__("pusha\r\n");
    __asm__("pushf\r\n");



    out_byte(TIME_INDEX_PORT,YEAR);
    _time.year = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,MON);
    _time.month = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,DAY);
    _time.day = bcd_to_int( in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,WEEK);
    _time.week = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,HOUR);
    _time.hour = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,MIN);
    _time.min = bcd_to_int(in_byte(TIME_DATA_PORT));

    out_byte(TIME_INDEX_PORT,SEC);
    _time.sec = bcd_to_int(in_byte(TIME_DATA_PORT));


    // char temp[20];
    // printf( itoa(_time.week,temp) );
    printf("!");

    //showtime();

    __asm__("popf\r\n");
    __asm__("popa\r\n");

    out_byte(S_CTL,0x20);
    out_byte(M_CTL,0x20);

    __asm__("leave\r\n");
    __asm__("iretl\r\n");
}






void init_time(){
    char t[20];
    int al = 0x0a;
    // out_byte(TIME_INDEX_PORT,al);
    // al = in_byte(TIME_DATA_PORT);
    // al = al & 0xf0;
    // out_byte(TIME_DATA_PORT, al);
    // al = in_byte(TIME_DATA_PORT);
    // printf(itoa(al,t));

    out_byte(TIME_INDEX_PORT,0x0b);
    al = in_byte(TIME_DATA_PORT);
    al = 0x12;
    out_byte(TIME_DATA_PORT,al);

    out_byte(TIME_INDEX_PORT,0x0c);
    in_byte(TIME_DATA_PORT);



    set_intGate(TIME_VECTOR,time_handler);
    enble_irq(TIME_IRQ);

}
