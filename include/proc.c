#include "proc.h"
#include "global.h"
#include "stdio.h"
#include "string.h"
#include "kernlib.h"

char t[10];

void schedule() {
    Process *p = p_proc_ready;
    p->ticks--;
    if(p->ticks <= 0 || p->state == died) {
        //时间结束
        //put_char('0'+p->ticks);
        if(p->state != died) {
            p->state = suspended;
            p->ticks = p->priorty;
        }
        //寻找就绪的进程
        p++;
        if(p == proc_table + NUM_TASKS) p = proc_table;
        while (p->state != suspended)
        {
            //printf("#");
            p++;
            if(p == proc_table + NUM_TASKS) p = proc_table;
        }
        //printf("@");
        p->state == alive;
        p_proc_ready = p;
    }
    else return;
    //printf("@");
}

void exec() {
    pro();
    //proc_table[1].state = died;
    schedule();
}