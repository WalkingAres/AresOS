#include "stdio.h"

void kernel(){
    char s[] = "hello, AresOS!\n\r";
    printf(s);
    printf("hello world\n\r");
    printf("tree\r\n");
    return;
}