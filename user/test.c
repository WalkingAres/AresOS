#include "global.h"
#include "unistd.h"
#include "string.h"

void example_fork(){
    int pid;
    pid = fork();
    if(pid == 0) {
        printf("This is child thread!\r\n");
    }
    else {
        printf("This is parent thread!\r\n");
    }
    exit(0);
}

void example_lib() {
    char *s = malloc(sizeof(char)*100);
    printf("input a string:");
    scanf("%s",s);
    printf("\r\nyour string is %s with %d characters",s, strlen(s));
    free(s);
    exit(0);
}