#include "malloc.h"
#include "global.h"

void *malloc(size_t size) {

    if(size == 0) return NULL;

    MemBlock * p = MemHead;
    MemBlock * ret = NULL;
    int tolsize = size + HEAD_SIZE;
    while(p != NULL) {
        //Ѱ���㹻��Ŀ��п�
        if(p->state == FREE && p->size >= tolsize) {
            ret = (MemBlock *)p->addr;
            p->state = BUSY;
            uint32_t left = p->size - size;
            //����Ŀ��п���
            if(left > HEAD_SIZE) {
                p->size = size;
                MemBlock * new = (MemBlock *)(p->addr + size);
                new->addr = (uint32_t)new + HEAD_SIZE;
                new->size = left - HEAD_SIZE;
                new->state = FREE;
                MemBlock * temp = p->next;
                p->next = new;
                new->next = temp;
            }

            break;

        }

        else p = p->next;
    }

    return ret;

}

void free(void * ptr) {
    MemBlock * p = ptr - HEAD_SIZE;
    p->state = FREE;
    
    p = MemHead;
    //�ϲ������Ŀտ�
    while(p != NULL) {
        if(p->state == FREE && p->next->state == FREE) {
            p->size += p->next->size + HEAD_SIZE;
            p->next = p->next->next;
        }

        p = p->next;
    }
}