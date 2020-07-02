#ifndef MALLOC_H
#define MALLOC_H

#include "def.h"

// 内存块状态
typedef enum MemSate{
    FREE,
    BUSY
}MemState;

typedef struct MemBlock
{
    uint32_t addr;//内存块空闲区起始地址
    uint32_t size;//大小
    MemState state;//状态
    struct MemBlock *next;//下一个内存块
}MemBlock;

#define HEAD_SIZE sizeof(MemBlock)

void * malloc(size_t size);

void free(void * ptr);

#endif