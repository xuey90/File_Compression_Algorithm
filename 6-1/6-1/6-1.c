//
//  main.c
//  6-1
//
//  Created by Xueyong Qian on 09/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key{
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "double", 0,
    "if", 0,
    "int", 0,
    "unsigned", 0,
    "void", 0,
    "while", 0
};

#define MAXWORD 100

int getword(char*, int);
int binsearch(char*, struct key*, int);

int main(int argc, const char * argv[])
{
    int n;
    char word[MAXWORD];
    int NKEYS = sizeof(keytab)/ sizeof(keytab[0]);
    
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    }
    for (n = 0; n < NKEYS; ++n) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

int binsearch(char* word, struct key tab[], int n)
{
    int cond, low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        }
        else if(cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

void comment(char cm, FILE *ifp)
{
    int lastc, c;
    
    lastc = ' ';
    if(cm == '*')
    {
        while((c = getc(ifp)) != EOF)
        {
            if(lastc == '*' && c == '/' )
            {
                getc(ifp);
                break;
            }
            lastc = c;
        }
    }
    else if(cm =='/')
    {
        while((c=getc(ifp)) != '\n')
            ;
    }
}

int getword(char* word, int lim)
{
    int c, nextc;
    char *w = word;
    
    while (isspace(c = getchar()))
        ;
    
    if(c == '/')
    {
        if((nextc = getchar()) == '/' || nextc == '*')
        {
            comment(nextc, stdin);
            while (isspace(c = getchar())) 
                ;
        }
        else
        {
            ungetc(nextc, stdin);
            *w++ = c;
            *w = '\0';
            return c;
        }
    }
    else if(c == '#')
    {
        while ((c = getchar()) != '\n')
            ;
        c = getchar();
    }
    else if(c =='\'')
    {
        while((c=getchar()) != '\'')
        {
            if(c == '\\')
                getchar();
        }
        c = getchar();
    }
    else if(c =='"')
    {
        while((c=getchar()) != '"')
        {
            if(c == '\\')
                getchar();
        }
        c = getchar();
    }
    if(c != EOF)
        *w++ = c;
    if (!(isalpha(c) || c == '_')) {
        *w = '\0';
        return c;
    }
    for (; --lim > 1; ++w) {
        if (!(isalnum(*w = getchar()) || *w == '_')) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
