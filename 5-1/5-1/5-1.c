//
//  main.c
//  5-1
//
//  Created by Xueyong Qian on 19/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getchar())) {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetc(c, stdin);
        return EOF;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c =='-') {
        if (!isdigit(c = getchar())) {
            ungetc(c, stdin);
            return EOF;
        }
    }
    for (*pn = 0; isdigit(c); c = getchar()) {
        *pn = 10 * *pn + c - '0';
    }
    *pn *= sign;
    //if(c != EOF)
    ungetc(c, stdin);
    return c;
}

int getfloat(double *dl)
{
    int c, sign, pow;
    while (isspace(c = getchar())) {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetc(c, stdin);
        return EOF;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c =='-') {
        if (!isdigit(c = getchar())) {
            ungetc(c, stdin);
            return EOF;
        }
    }
    for (*dl = 0; isdigit(c); c = getchar()) {
        *dl = 10 * *dl + c - '0';
    }
    if (c == '.') {
        c = getchar();
    }
    for (pow = 1; isdigit(c); c = getchar()) {
        *dl = 10 * *dl + c - '0';
        pow *= 10;
    }
    *dl = *dl * sign / pow;
    //if(c != EOF)
    ungetc(c, stdin);
    return c;
}
int main(int argc, const char * argv[])
{
    int n;
    double dl;
    while(getfloat(&dl) != EOF)
        printf("%g\n", dl);
    return 0;
}

