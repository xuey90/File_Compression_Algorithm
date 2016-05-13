//
//  main.c
//  5-3
//
//  Created by Xueyong Qian on 21/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

void q_strcat(char *s, char *t)
{
    while (*s) {
        ++s;
    }
    while (*s++ = *t++) {
        ;
    }
}
int main(int argc, const char * argv[])
{
    char s[] = "123";
    char t[] = "45678";
    q_strcat(s,t);
    printf("%s\n",s);
    return 0;
}

