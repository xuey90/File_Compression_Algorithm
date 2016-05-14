//
//  main.c
//  2-3
//
//  Created by Xueyong Qian on 07/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <ctype.h>

int htoi(char *s)
{
    int value = 0;
    if (*s == '0') {
        ++s;
        if(*s == 'x' || *s == 'X')
        {
            ++s;
        }
    }
    while (*s) {
        if (isdigit(*s)) {
            value = 16 * value+ *s - '0';
        }
        else if(*s>='a' && *s <='f')
        {
            value = 16 *value + *s - 'a'+ 10;
        }
        else if(*s>='A' && *s <='F')
        {
            value = 16 *value + *s - 'A'+ 10;
        }
        ++s;
    }
    return value;
}
int main(int argc, const char * argv[])
{
    
    printf("%d\n", htoi("0x12"));
    return 0;
}

