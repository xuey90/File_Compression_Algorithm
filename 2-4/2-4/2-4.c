//
//  main.c
//  2-4
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int in_str(char *s, char c)
{
    while (*s) {
        if (c == *s) {
            return 1;
        }
        ++s;
    }
    return 0;
}
void squeeze(char *s1, char *s2)
{
    int i, j;
    for (i = j = 0; s1[i]; ++i) {
        if (!in_str(s2,s1[i])) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}
int main(int argc, const char * argv[])
{

    char s1[] = "tobeornot";
    char s2[] = "ot";
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}

