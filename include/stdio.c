#include "stdarg.h"
#include "stdio.h"

int printf(const char * format, ...) {
    va_list ap;
    va_start(ap,format);
    const char * p = format;
    int count , num, top;
    char * str;
    count = 0;
    char s[20];
    while (*p != '\0'){
        switch (*p){
            case '%':
            {
                p++;
                switch (*p){
                    case 'd':
                        num = va_arg(ap,int);
                        top = 0;
                        do {
                            s[top] = num%10 + '0';
                            num /= 10;
                            top++;
                        }while(num > 0);
                        top--;
                        while(top >= 0) {
                            count++;
                            put_char(s[top]);
                            top--;
                        }
                        break;

                    case 's':
                        str = va_arg(ap,char *);
                        while(*str != '\0') {
                            put_char(*str);
                            count++;
                            str++;
                        }
                        break;
                }
                p++;
                break;
            }
            default:
                put_char(*p);
                count++;
                p++;
            break;
        }
    }
    return count;
}

int scanf(const char * format, ... ){
    va_list ap;
    va_start(ap,format);
    const char *p = format;
    int count = 0;
    int *num;
    char *str;
    char ch;
    while (*p != '\0')
    {
        switch (*p)
        {
        case '%':
            {
                p++;
                switch (*p)
                {
                case 'd':
                    num = va_arg(ap,int *);
                    *num = 0;
                    while(1) {
                        ch = get_char();
                        if(ch < '0' || ch > '9') break;
                        *num = (*num)*10 + ch - '0';
                    }
                    break;
                case 's':
                    str = va_arg(ap,char *);
                    get_string(str);
                    break;

                default:
                    break;
                }
            }
            p++;
            break;
        
        default:
            //get_char();
            p++;
            break;
        }
    }
    
}
