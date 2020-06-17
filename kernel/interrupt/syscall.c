#include "syscall.h"
#include "global.h"

void syscall() {
    save();

    int syscall_num;
    __asm__(
        "movl %%eax, %0\r\n"
        :"=a"(syscall_num));
    SysCall_Table[syscall_num]();

    __asm__("ret\r\n");
}