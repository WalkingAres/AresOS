#ifndef SYSCALL_H
#define SYSCALL_H

#include "int.h"

#define EXIT 1
#define FORK 2
#define WAIT 3
#define EXEC 4

typedef int (*_ptr_syscall)(uint32_t arg[]);

__attribute__((naked))
void syscall(void);

int sys_fork(uint32_t arg[]);

int sys_exit(uint32_t arg[]);

int sys_wait(uint32_t arg[]);

int sys_execv(uint32_t arg[]);

#endif