#ifndef HD_H
#define HD_H

#include "def.h"

#define NUM_PORT    0x1f2
#define S_PORT      0x1f3
#define C_PORT_LOW  0x1f4
#define C_PORT_HIGH 0x1f5
#define H_PORT      0x1f6
#define CTRL_PORT   0x1f7
#define STAT_PORT   0x1f7
#define DATA_PORT   0x1f0

void read_disk(uint32_t num_sec, uint8_t num,  uint8_t * buf);

#endif