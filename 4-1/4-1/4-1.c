//
//  main.c
//  4-1
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int strrindex(char source[], char searchfor[]);

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

int main(int argc, const char * argv[])
{
    char pattern[] = "in";
    char line[MAXLINE];
    int count = 0;
    int found = 0;
    FILE *ifp = fopen("4-1.c", "r");
    while (getl(line, MAXLINE, ifp) > 0) {
        if ((count = strrindex(line, pattern)) >= 0) {
            printf("%d\t%s", count,line);
            ++found;
        }
    }
    fclose(ifp);
    return found;
}

int strrindex(char s[], char t[])
{
    int i, j, k;
    int pos = -1;
    for (i = 0;  i <= (int)(strlen(s) - strlen(t)) ; ++i) {
        for (j = i, k = 0; t[k] && s[j]==t[k]; ++j, ++k) {
            ;
        }
        if (k > 0 && !t[k]) {
            pos = i;
            i += k;
        }
    }
    return pos;
}

