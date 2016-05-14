//
//  main.c
//  5-11
//
//  Created by Xueyong Qian on 22/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

void detab(char *s)
{
    int count;
    char *temp = (char*)malloc(sizeof(char)*MAXLINE);
    count = 0;
    while(*s)
    {
        ++count;
        if(*s == '\t')
        {
            while(count%TABSTOP)
            {
                *temp++ = ' ';
                ++count;
            }
        }
        else
            *temp++ = *s;
        ++s;
    }
    *temp = '\0';
    copy(s,temp);
}

void entab(char *s)
{
    int count;
    char *temp = (char*)malloc(sizeof(char)*MAXLINE);
    char *pos = s;
    while (*s) {
        for (count = 0;  count < TABSTOP ; ++count, ++pos){
            if(*pos== '\t' || *pos == '\n')
            {
                break;
            }
        }
        for (--count; count >=0 && *(s+count) == ' '; --count) {
            ;
        }
        while(count>0)
        {
            *temp++ = *s++;
            --count;
        }
        if(*pos == '\t' || *pos == ' ')
            *temp++ = '\t';
        else if(*pos =='\n')
            *temp++ = '\n';
        s = pos++;
    }
    *temp = '\0';
    copy(s, temp);
}

int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

