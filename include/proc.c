#include "proc.h"
#include "global.h"
#include "stdio.h"
#include "string.h"
#include "kernlib.h"

char t[10];

void schedule() {
    Process *p = proc_current;
    //p->ticks--;
    // if(p->ticks <= 0 || p->state == died) {
    //     //时间结束
    //     //put_char('0'+p->ticks);
    //     if(p->state != died) {
    //         p->state = suspended;
    //         p->ticks = p->priorty;
    //     }
    //     //寻找就绪的进程
    //     p++;
    //     if(p == proc_table + NUM_TASKS) p = proc_table;
    //     while (p->state != suspended)
    //     {
    //         //printf("#");
    //         p++;
    //         if(p == proc_table + NUM_TASKS) p = proc_table;
    //     }
    //     //printf("@");
    //     p->state == alive;
    //     proc_current = p;
    // }
    // else return;
    if(p->state == alive && p->ticks > 0 ) return;
    if(p->state == alive ) {
        p->state = suspended;
        p->ticks = p->priorty;
    }
    p++;
    if( p == proc_table + NUM_TASKS) p = proc_table;
    while( p->state != suspended) {
        p++;
        if( p == proc_table + NUM_TASKS) p = proc_table;
    }
    p->state = alive;
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
    proc_table[2].state = suspended;
}

void init_mulpro() {
    int i;
    for(int i=0;i<4;i++) {
        proc_table[i+3].regs.eip = 0x60400 + 0x400*i;
        proc_table[i+3].state = suspended;
    }
    proc_table[0].state = sleep;
    schedule();
}