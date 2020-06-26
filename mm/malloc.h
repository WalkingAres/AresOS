#ifndef MALLOC_H
#define MALLOC_H

#include "def.h"

typedef enum MemSate{
    FREE,
    BUSY
}MemState;

typedef struct MemBlock
{
    uint32_t addr;
    uint32_t size;
    MemState state;
    struct MemBlock *next;
}MemBlock;

#define HEAD_SIZE sizeof(MemBlock)

void * malloc(size_t size);

void free(void * ptr);

#endif