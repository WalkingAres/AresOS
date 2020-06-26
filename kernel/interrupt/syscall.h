#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

#define EXIT 1
#define FORK 2
#define WAIT 3

typedef void *_ptr_syscall;

typedef void (*_ptr_syscall0)(void);

typedef void (*_ptr_syscall1)(void *);


__attribute__((naked))
void syscall();


void sys_1(){
        printf("syscall_1");
        proc_current->state = DIED;
        schedule();
}

void sys_0(){
        printf("syscall_0");
        //put_char('0'+i);
        // i++;
        delay();
}

void sys_2(char *s) {
    printf("%s!\r\n",s);
}

#endif