//
//  main.c
//  5-13
//
//  Created by Xueyong Qian on 23/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 1000

char *lineptr[MAXN];

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

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXN];
    
    nlines = 0;
    while ((len = getl(line, MAXN, stdin)) > 0) {
        if(nlines >= maxlines || (p = (char*)malloc(len * sizeof(char))) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int main(int argc, const char * argv[])
{
    int len = 0;
    int nlines, i;
    
    if (argc == 2) {
        if (*argv[1] == '-') {
            while (*++argv[1]) {
                len = 10 *len + *argv[1] - '0';
            }
        }
        else
        {
            printf("Unknown command:%c\n", *argv[1]);
            exit(EXIT_FAILURE);
        }
    }
    else
        len = 3;
    
    if((nlines = readlines(lineptr, MAXN)) < len)
    {
        len = nlines;
    }
    for (i = nlines - len; i < nlines ; ++i) {
        printf("%s\n", lineptr[i]);
    }
    
}