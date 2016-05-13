//
//  main.c
//  1-17
//
//  Created by Xueyong Qian on 25/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000


int getl(char[], int, FILE*);

int main(int argc, const char * argv[])
{
    int len;
    char line[MAXLINE];
    FILE *ifp;
    if(!(ifp = fopen("1-16.c", "r")))
        exit(1);
    while ((len = getl(line, MAXLINE, ifp))>0) {
        if (len > 40) {
            printf("%s", line);
        }
    }
    fclose(ifp);
    return 0;
}

int getl(char s[], int lim, FILE*ifp)
{
    int c, i, n;
    
    for(i = n = 0; (c = getc(ifp))!=EOF && c!='\n'; ++n)
    {
        if(i<lim-2){
            s[i++] = c;
        }
    }
    if(c == '\n')
    {
        s[i++] = c;
        ++n;
    }
    s[i] = '\0';
    return n;
}

