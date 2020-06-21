#include "syscall.h"
#include "global.h"

void syscall() {
    Process *p = proc_current;
    save();

    int syscall_num = p->regs.eax;



    if(syscall_num != 2){
        _ptr_syscall0 f = SysCall_Table[syscall_num];
        f();
    }
    else {
        _ptr_syscall1 f = SysCall_Table[syscall_num];
        f((char *)p->regs.ebx);
    }
    __asm__("ret\r\n");
}