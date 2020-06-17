#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

typedef void (*_ptr_syscall) (void);

__attribute__((naked))
void syscall();

#endif