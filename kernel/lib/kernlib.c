#include "kernlib.h"
#include "hd.h"
#include "unistd.h"
#include "global.h"

int fork(void) {
    __asm__(
        "movl $1,%eax\r\n"
        "int $0x80\r\n"
    );
    return;
}

int exit(int state) {
    __asm__(
        "movl $2, %%eax\r\n"
        "movl %0, %%edx\r\n"
        "int $0x80\r\n"
        :
        :"b"(state)
    );
    return;
}

int wait() {
    // __asm__(
    //     "movl $3,%eax\r\n"
    //     "int $0x80\r\n"
    // );
    // return;
    Process *parent = proc_current;
    Process *head = proc_current->head_child;
    if(head == NULL ) return 0;
    while(1) {
        if(head->state == DIED ) {
            free((uint32_t*)(head->stack));
            free(head);
            return head->pid;
        }
        head = head->next;
        if(head == NULL ) {
            head = proc_current->head_child;
        }
    }
    return 0;
}

int execv(uint32_t ptr_func) {
    __asm__(
        "movl $4, %%eax\r\n"
        "movl %0, %%edx\r\n"
        "int $0x80\r\n"
        :
        :"b"(ptr_func)
    );
    return;
}

void load_program(uint8_t id) {
    uint8_t *p = (uint8_t *) USER_PRO_POINT + 0x400*(id-1);
    read_disk((id-1)*2,2,p);
}

void pro() {
    __asm__(
        "movl $0x60400,%eax\r\n"
        "call *%eax\r\n"
        );
}