//
//  main.c
//  1-18
//
//  Created by Xueyong Qian on 25/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000


int getl(char[], int, FILE*);

void trail(char *s)
{
    char *p;
    int nl;
    if(*s == '\n')
    {
        *s = '\0';
        return;
    }
    p = s;
    nl = 0;
    while (*p) {
        ++p;
    }
    --p;
    if (*p == '\n') {
        --p;
        nl = 1;
    }
    while(*p == ' ' || *p =='\t')
    {
        --p;
    }
    if(nl)
        *++p = '\n';
    *++p = '\0';
}
int main(int argc, const char * argv[])
{
    int len;
    char line[MAXLINE];
    FILE *ifp;
    if(!(ifp = fopen("1-16.c", "r")))
        exit(1);
    while ((len = getl(line, MAXLINE, ifp))>0) {
        trail(line);
        if(len > 1)
            printf("%s", line);
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
