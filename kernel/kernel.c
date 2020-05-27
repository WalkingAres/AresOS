#include "stdio.h"
#include "keyboard.h"

void kernel(){
    char s[] = "hello, AresOS!\n\r";
    printf(s);
    printf("hello world\n\r");

    char ch ='a';
    while (1)
    {
        ch = get_char();
        //put_char(kb.readcount+'0');
        put_char(ch);
    }

    printf("end");
    
    while (1)
    {
        /* c   ode */
    }
    
    
    return;
}