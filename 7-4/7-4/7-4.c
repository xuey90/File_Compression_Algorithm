//
//  main.c
//  7-4
//
//  Created by Xueyong Qian on 16/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
void minscanf(char* fmp,...)
{
    va_list ap;
    char* p, *sval;
    int *ival;
    double *dval;
    
    va_start(ap, fmp);
    for (p = fmp; *p; ++p) {
        if (*p == '%') {
            switch (*++p) {
                case 'd':
                    ival = va_arg(ap, int*);
                    scanf("%d",ival);
                    break;
                case 'f':
                    dval = va_arg(ap, double*);
                    scanf("%lf", dval);
                    break;
                case 's':
                    sval = va_arg(ap, char*);
                    scanf("%s", sval);
                    break;
                default:
                    break;
            }
        }
        else if (*p != getchar()) {
            printf("minscanf: format not correct!\n");
            exit(EXIT_FAILURE);
        }
        
    }
    va_end(ap);
}

int main(int argc, const char * argv[])
{
    int day, year;
    char month[20];
    minscanf("%d%s%d", &day, &month, &year);
    printf("%d %s %d\n", day, month, year);
    return 0;
}

