//
//  main.c
//  5-18
//
//  Created by Xueyong Qian on 07/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS};
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl(void);
void dirdcl(void);

int gettoken(void)
{
    int c;
    char *p = token;
    while ((c = getchar()) == ' ' || c == '\t') {
        ;
    }
    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else{
            ungetc(c, stdin);
            return tokentype = '(';
        }
    }
    else if(c == '[')
    {
        for (*p++ = c; (*p++ = getchar()) != ']'; ) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getchar()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; ) {
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

void dirdcl(void)
{
    int type;
    
    if(tokentype == '(')
    {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(tokentype == NAME)
        strcpy(name, token);
    else
    {
        printf("error: expected name or (dcl)\n");
        exit(EXIT_FAILURE);
    }
    
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        }
        else{
            strcat(out, "array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

int main(int argc, const char * argv[])
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n') {
            printf("systax error\n");
            exit(EXIT_FAILURE);
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

