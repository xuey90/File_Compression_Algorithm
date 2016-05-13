//
//  main.c
//  5-5
//
//  Created by Xueyong Qian on 21/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

void q_strncpy(char *s, char *t, int n)
{
    while (n) {
        --n;
        if(!(*s++ = *t++))
            break;
    }
    if (!n) {
        *s = '\0';
    }
}

void q_strncat(char *s, char *t, int n)
{
    while (*s) {
        ++s;
    }
    while (n) {
        --n;
        if (!(*s++ = *t++)) {
            break;
        }
    }
    if(!n)
        *s = '\0';
}

int q_strncmp(char *s, char *t, int n)
{
    for (; n; --n, ++s, ++t) {
        if (*s != *t) {
            return *s - *t;
        }
        else if(!*s)
            return 0;
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    char s[20];
    char t[] = "12345";
    q_strncpy(s, t, 6);
    q_strncat(s, t, 4);
    printf("%d\n", q_strncmp(s, t, 7));
    printf("%s\n",s);
    return 0;
}

