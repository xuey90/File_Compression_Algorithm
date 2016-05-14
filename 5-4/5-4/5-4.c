//
//  main.c
//  5-4
//
//  Created by Xueyong Qian on 21/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int strend(char *s, char *t)
{
    int i;
    for (i = 0; i < strlen(s) - strlen(t); ++i) {
        ++s;
    }
    while (*s == *t) {
        ++s;
        ++t;
    }
    if (*--t == '\0') {
        return 1;
    }
    else
        return 0;
}
int main(int argc, const char * argv[])
{
    char s[] = "34527";
    char t[] = "27";
    if (strend(s, t)) {
        printf("end found\n");
    }
    else
        printf("not found\n");
    return 0;
}

