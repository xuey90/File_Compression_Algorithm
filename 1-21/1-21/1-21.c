//
//  main.c
//  1-21
//
//  Created by Xueyong Qian on 26/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define TABSTOP 4
#define MAXLINE 1000

int getl(char[], int, FILE*);
void copy(char[], char[]);

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
    int count;
    FILE *ifp;
    char s[MAXLINE];
    count = 0;
    ifp = fopen("1-16.c", "r");
    
    while(getl(s, MAXLINE, ifp)>0)
    {
        entab(s);
        printf("%s",s);
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