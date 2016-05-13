//
//  main.c
//  7-3
//
//  Created by Xueyong Qian on 12/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
void minprintf(char* fmt, ...)
{
    va_list ap;
    char *p, *sval,c;
    int ival,num,temp;
    int field, precision;
    double dval;
    num = 0;
    field = precision = 0;
    va_start(ap, fmt);
    for(p = fmt; *p; ++p){
        if(*p == '%'){
            while(isdigit(*++p)){
                field = 10* field + *p - '0';
            }
            if(*p == '.'){
                while(isdigit(*++p)){
                    precision = 10* precision + *p - '0';
                }

            }
            switch (*p) {
                case 'd':
                    ival = va_arg(ap, int);
                    if(field){
                        temp = ival;
                        while(temp){
                            temp /= 10;
                            ++num;
                        }
                        while(num + precision < field){
                            ++num;
                            putchar('*');
                        }
                    }
                    printf("%d",ival);
                    break;
                case 'f':
                    dval = va_arg(ap, double);
                    printf("%f",dval);
                    break;
                case 's':
                    
                    for (sval = va_arg(ap, char*); *sval; sval++) {
                        putchar(*sval);
                    }
                    break;
                case 'c':
                    c = va_arg(ap, int);
                    putchar(c);
                    break;
                default:
                    putchar(*p);
                    break;
            }
        }
        else{
            putchar(*p);
        }
    }
    va_end(ap);
}
int main(int argc, const char * argv[])
{
    
    // insert code here...
    minprintf("%c\n",68);
    return 0;
}

