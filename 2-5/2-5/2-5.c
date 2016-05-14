//
//  main.c
//  2-5
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

char *any(char *s1, char* s2)
{
    while (*s1) {
        if (in_str(s2, *s1)) {
            return s1;
        }
        ++s1;
    }
    return NULL;
}

int main(int argc, const char * argv[])
{

    char str[] = "This is a sample string";
    char key[] = "aeiou";
    char * pch;
    printf ("Vowels in '%s': ",str);
    pch = any (str, key);
    while (pch != NULL)
    {
        printf ("%c " , *pch);
        pch = any (pch+1,key);
    }
    printf ("\n");
    return 0;
}

