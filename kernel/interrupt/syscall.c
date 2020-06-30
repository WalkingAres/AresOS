#include "syscall.h"
#include "global.h"


void syscall() {
    save();

    __asm__("sti\r\n");

    uint32_t *arg = malloc(sizeof(uint32_t)*5);
    StackFrame * reg = &(proc_current->regs);
    int sysnum = reg->eax;
    if( sysnum >=0 && sysnum < NUM_SYSCALLS) {
        arg[0]=reg->edx;
        arg[1]=reg->ecx;
        arg[2]=reg->ebx;
        arg[3]=reg->edi;
        arg[4]=reg->esi;

        reg->eax = SysCall_Table[sysnum](arg);
    }

    free(arg);

    __asm__("cli\r\n");

    __asm__("ret\r\n");
}

int sys_fork(uint32_t arg[]) {
    StackFrame * reg = &(proc_current->regs);
    uint32_t stack = reg->esp;
    return do_fork(0, stack, reg);
}

int sys_exit(uint32_t arg[]) {
    return do_exit(arg[0]);
}

int sys_wait(uint32_t arg[]) {
    return do_wait();
}

int sys_execv(uint32_t arg[]) {
    return do_execv(arg[0]);
}
