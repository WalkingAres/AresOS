#include "global.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "kernlib.h"
#include "unistd.h"

typedef enum shell_cmd {
    HELP,
    A,
    B,
    C,
    D,
    TIME,
    CLEAR,
    MULPRO,
    PS
}cmd_key;


cmd_key get_cmd_key(const char * cmd) {
    int len = strlen(cmd);
    int i=0;
    if(!strcmp(cmd,"help")) return HELP;
    if(!strcmp(cmd,"time")) return TIME;
    if(!strcmp(cmd,"a")) return A;
    if(!strcmp(cmd,"b")) return B;
    if(!strcmp(cmd,"c")) return C;
    if(!strcmp(cmd,"d")) return D;
    if(!strcmp(cmd,"clear")) return CLEAR;
    if(!strcmp(cmd,"mulpro")) return MULPRO;
    if(!strcmp(cmd,"ps")) return PS;
}

void clear_screen() {
    int i=0;
    while(i<160*25){
        __asm__("mov $0x0720,%%ax\r\n"
                "mov %%ax, %%gs:(%0)"
                ::"b"(i));
        i += 2;
    }
    out_byte(0x3d4,0xe);
    out_byte(0x3d5,0);
    out_byte(0x3d4,0xf);
    out_byte(0x3d5, 0); 
}

void help() {
    printf("\r\n");
    printf("a b c d:run a user program *\n\r");
    printf("time:show the real time\r\n");
    printf("clear:clear the screen\r\n");
    printf("ps:check the running thread\r\n");
}

void cmd_time(){
    get_time();
    showtime();
    printf("press any key to continue...\r\n");
    get_char();
}

void user_pro(cmd_key key) {
    clear_screen();
    load_program(key);
    int pid = fork();

    if (pid == 0){
        execv(0x60400+0x400*(key-1));
    }
    
    // wait();
    // clear_screen();
}


void mulpro() {
    clear_screen();
    int i;
    int pid;
    for(int i=1;i<=4;i++) {
        load_program(i);
    }

    pid =fork();
    if(pid == 0) execv(0x60400);

    pid =fork();
    if(pid == 0) execv(0x60800);   

    pid =fork();
    if(pid == 0) execv(0x60c00);

    pid =fork();
    if(pid == 0) execv(0x61000);
     
//    int p =wait();
// //    printf("exit:%d\r\n",p);
//    p =wait();
// //    printf("exit:%d\r\n",p);   
//    p =wait();
// //    printf("exit:%d\r\n",p);   
//    p =wait();


    clear_screen();
    
}

void delay(){
        int i;
        for(i=0;i<1000000;i++) ;
}

void ps_thread() {
    ProcNode * p = procReady;
    int c = 0;
    printf("\r\n");
    do{
        c++;
        printf("pid:%d name:%s\r\n",p->pproc->pid,p->pproc->p_name);
        p = p->next;
    }while(p != procReady);
    printf("there are %d threads running!\n\r",c);
}


void time_thread(){

    while (1)
    {
        get_time();
        showtime();
        delay();
    }
    
}

extern void example_fork();
extern void example_lib();

void _shell() {
    char cmd[100];
    cmd_key key;
    clear_screen();
    char s[]="hello Ares OS!\r\n"; 
    printf("%s",s);
    
    int pid = fork();
    if(pid == 0) {
        set_name("time");
        printf("time thread is running!\n\r");
        execv((uint32_t)time_thread);
    }

    while(1) {
        delay();
        printf("@Ares >");
        scanf("%s",cmd);
        key  = get_cmd_key(cmd);
        switch (key)
        {
        case HELP:
            help();
            break;
        case TIME:
            cmd_time();
            break;
        case A:
        case B:
        case C:
        case D:
            user_pro(key);
            break;
        case CLEAR:
            clear_screen();
            break;
        case MULPRO:
            mulpro();
            break;
        case PS:
            ps_thread();
            break;
        default:
            printf("\r\ncommand not found: %s\r\n",cmd);
            break;
        }
    }
}