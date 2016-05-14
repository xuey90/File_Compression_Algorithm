//
//  main.c
//  1-16
//
//  Created by Xueyong Qian on 25/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#define MAXLINE 100

int getl(char[], int, FILE*);
void copy(char [], char from[]);

int main(int argc, const char * argv[])
{
    int len, max;
    char line[MAXLINE];
    char longest[MAXLINE];
    FILE *ifp;
    max = 0;
    ifp = fopen("1-16.c", "r");
    while ((len = getl(line, MAXLINE, ifp))>0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if(max)
    {
        printf("%d\t%s", max,longest);
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

void copy(char to[], char from[])
{
    int i;
    
    i = 0;
    while((to[i] = from[i])!='\0')
        ++i;
}

