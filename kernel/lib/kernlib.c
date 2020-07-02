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
    Process *pre = NULL;
    if(head == NULL ) return 0;

    // while(head!=NULL) {
    //     printf("pid:%d-->\r\n",head->pid);
    //     head = head->next;
    // }
    // head = proc_current->head_child;
    while(1) {
        if(head->state == DIED ) {
            // 从子进程列表中删除
            if(head == proc_current->head_child ) {
                proc_current->head_child = head->next;
            }
            else{
                pre->next = head->next;
            }
            
            free((uint32_t*)(head->stack));
            free(head);
            return head->pid;
        }
        pre = head;
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
    uint8_t *p = (uint8_t *) (USER_PRO_POINT + 0x400*(id-1));
    read_disk((id-1)*2,2,p);
}

void pro() {
    __asm__(
        "movl $0x60400,%eax\r\n"
        "call *%eax\r\n"
        );
}