#ifndef TIME_H
#define TIME_H

#include "def.h"

#define TIME_INDEX_PORT 0x70
#define TIME_DATA_PORT  0x71

#define YEAR    0x09
#define MON     0x08
#define DAY     0x07
#define WEEK    0x06
#define HOUR    0x04
#define MIN     0x02
#define SEC     0x00



typedef struct time {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}time;

static time _time;

void init_time();

void time_handler();

void showtime();

void get_time();

#endif