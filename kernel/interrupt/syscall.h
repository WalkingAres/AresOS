#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

typedef void *_ptr_syscall;

typedef void (*_ptr_syscall0)(void);

typedef void (*_ptr_syscall1)(void *);


__attribute__((naked))
void syscall();

#endif