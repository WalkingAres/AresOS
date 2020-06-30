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

int c=0;


void schedule() {
    //printf("curpid:+++%d",proc_current->pid);
    Process *p = proc_current;
    if(p->state == ALIVE && p->ticks > 0 ) return;
    if(p->state == ALIVE ) {
        p->state = READY;
        p->ticks = p->priorty;
    }

    procCurrent = procReady;

    proc_current = procReady->pproc;
    procReady = procReady->next;

    // p++;
    // if( p == proc_table + NUM_TASKS) p = proc_table;
    // while( p->state != READY) {
    //     p++;
    //     if( p == proc_table + NUM_TASKS) p = proc_table;
    // }

    p=proc_current;
    p->state = ALIVE;
    p->ticks = p->priorty;
    //printf("@");
}

void ProcCpy(Process * child, Process *parent){
    memcpy(child,parent,sizeof(Process));
}

uint32_t set_pid() {
    return 3;
}


int do_fork(uint32_t flag, uint32_t stack, StackFrame * regs){
    if(flag == 0) {
        Process * new = malloc(sizeof(Process));
        // pcb 复制
        ProcCpy(new,proc_current);

        // 子进程的堆栈
        uint32_t * childstack = malloc(sizeof(uint32_t)*0x1000);
        new->stack = (uint32_t) childstack;

        memcpy(childstack+0x800,(uint32_t*)new->regs.esp,0x800);

        new->regs.esp = (uint32_t)(childstack+0x800);

        uint32_t * ebp = (uint32_t *)new->regs.esp;
        *ebp = *ebp - regs->esp + new->regs.esp;

        new->regs.eax = 0;
        new->state = READY;

        new->parent = proc_current;
        Process * temp = proc_current->head_child->next;
        proc_current->head_child = new;
        new->next = temp;

        new->pid = set_pid();

        ProcNode * newnode = malloc(sizeof(ProcNode));
        newnode->pproc = new;
        ProcNode * next = procReady->next;
        ProcNode * pre = procReady->pre;

        procReady->next = newnode;
        newnode->next = next;
        newnode->pre = procReady;
        next->pre = newnode;

        procReady = newnode;

    }

    return 1;
}

int do_exit(uint32_t state) {
    Process * current = proc_current;
    ProcNode * temp;
    if(current->parent != NULL ) {
        // remove from reat quque
        temp = procCurrent->pre;
        temp->next = procCurrent->next;
        procCurrent->next->pre= temp;
        // go to died quque 
        //printf("do_exit");
        current->state = DIED;
        temp = procDied->next;
        procDied = procCurrent;
        procDied->next = temp;
    }

    temp = procDied;
    while ( temp != NULL )
    {
        procDied=procDied->next;
        free(temp);
        temp=procDied;
    }

    schedule();

    return state;
}

int do_wait() {
    printf("wait");
    while (1)
    {
        /* code */
    }
    
    Process *parent = proc_current;
    Process *head = proc_current->head_child;
    if(head == NULL ) return 0;
    while(1) {
        if(head->state == DIED ) {
            free((uint32_t*)(head->stack));
            free(head);
            return head->pid;
        }
        head = head->next;
        if(head == NULL ) {
            head = proc_current->head_child;
        }
    }
    return 0;
}

int do_execv(uint32_t ptr_func) {
    if(ptr_func != 0) proc_current->regs.eip = ptr_func;
    return 0;
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

