//
//  main.c
//  1-19
//
//  Created by Xueyong Qian on 25/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

void reverse(char *s)
{
    char *p, temp;
    
    p = s;
    while (*p) {
        ++p;
    }
    --p;
    if(*p == '\n')
        --p;
    while(s < p)
    {
        temp = *s;
        *s = *p;
        *p = temp;
        ++s;
        --p;
    }
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
int main(int argc, const char * argv[])
{

    FILE *ifp;
    
    ifp = fopen("1-16.c", "r");
    char line[1000];
    while (getl(line, 1000, ifp)>0) {
        reverse(line);
        printf("%s",line);
    }
    return 0;
}

