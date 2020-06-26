#include "proc.h"
#include "global.h"
#include "stdio.h"
#include "string.h"
#include "kernlib.h"


ProcNode* pre(const ProcNode* cur) {
    return cur->pre;
}

ProcNode* next(const ProcNode* cur) {
    return cur->next;
}




void schedule() {
    Process *p = procCurrent->pproc;
    if(p->state == ALIVE && p->ticks > 0 ) return;
    if(p->state == ALIVE ) {
        p->state = READY;
        p->ticks = p->priorty;
    }

    procCurrent = next(procCurrent);

    // p++;
    // if( p == proc_table + NUM_TASKS) p = proc_table;
    // while( p->state != READY) {
    //     p++;
    //     if( p == proc_table + NUM_TASKS) p = proc_table;
    // }

    p = procCurrent->pproc;
    p->state = ALIVE;
    p->ticks = p->priorty;
    proc_current = p;
    //printf("@");
}

void exec() {
    //pro();
    //proc_table[1].state = died;
    schedule();
}

void init_exec(_funcptr func) {
    proc_table[2].regs.eip = (uint32_t)func;
    proc_table[2].state = READY;
}

void init_mulpro() {
    int i;
    for(int i=0;i<4;i++) {
        proc_table[i+3].regs.eip = 0x60400 + 0x400*i;
        proc_table[i+3].state = READY;
    }
    proc_table[0].state = SLEEP;
    schedule();
}

