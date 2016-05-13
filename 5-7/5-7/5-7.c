//
//  main.c
//  5-7
//
//  Created by Xueyong Qian on 21/04/14.
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

int readlines(char *lineptr[], int maxlines, char *argv[])
{
    int len, nlines;
    char *p, line[MAXN];
    
    nlines = 0;
    while ((len = getl(line, MAXN, stdin)) > 0) {
        if(nlines >= maxlines)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(*argv, line);
            lineptr[nlines++] = *argv;
            ++argv;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void q_qsort(char *v[], int left, int right)
{
    int i, last;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) /2);
    last = left;
    for (i = left +1 ; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    q_qsort(v, left, last -1);
    q_qsort(v, last + 1, right);
}
int main(int argc, const char * argv[])
{
    int nlines;
    
    if((nlines = readlines(lineptr, MAXN, argv)) >= 0)
    {
        q_qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

