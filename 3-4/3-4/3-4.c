//
//  main.c
//  3-4
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
void reverse(char *s)
{
    int i, j, temp;
    for (i = 0, j = (int)strlen(s) - 1; i<j; ++i, --j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
void itoa(int n, char *s)
{
    int sign = n;
    char *t = s;
    do{
        *s++ = abs(n%10) + '0';
    }while((n /= 10)!=0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(t);
}

int main(int argc, const char * argv[])
{

    int n =  INT_MIN;
    char s[100];
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

