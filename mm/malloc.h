#ifndef MALLOC_H
#define MALLOC_H

#include "def.h"

// �ڴ��״̬
typedef enum MemSate{
    FREE,
    BUSY
}MemState;

typedef struct MemBlock
{
    uint32_t addr;//�ڴ���������ʼ��ַ
    uint32_t size;//��С
    MemState state;//״̬
    struct MemBlock *next;//��һ���ڴ��
}MemBlock;

#define HEAD_SIZE sizeof(MemBlock)

void * malloc(size_t size);

void free(void * ptr);

#endif