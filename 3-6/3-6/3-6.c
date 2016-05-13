//
//  main.c
//  3-6
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
void itoa(int n, char *s, int field)
{
    int i;
    int sign = n;
    char *t = s;
    do{
        *s++ = abs(n%10) + '0';
    }while((n /= 10)!=0);
    if (sign < 0) {
        *s++ = '-';
    }
    for (*s = '\0',i = strlen(t); i < field; ++i) {
        *s++ = ' ';
    }
    *s = '\0';
    reverse(t);
}

int main(int argc, const char * argv[])
{

    char s[999];
    itoa(-342, s, 3);
    printf("%s\n", s);
    return 0;
}

