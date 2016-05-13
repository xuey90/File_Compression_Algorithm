//
//  main.c
//  4-3
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAXN 100
#define NUMBER '0'
#define COMMAND 'c'

int getop(char *);
void push(double);
double pop(void);
double qatof(char *s);
int q_getch(void);
void q_ungetch(int c);

int sp = 0;
double val[MAXN];

int main(int argc, const char * argv[])
{
    int type;
    double op2;
    char s[MAXN];
    
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(qatof(s));
                break;
            case COMMAND:
            {
                if (strcmp(s,"top") == 0) {
                    op2 = pop();
                    printf("top element:%g\n",op2);
                    push(op2);
                }
                else if(strcmp(s, "dup") == 0)
                {
                    op2 = pop();
                    push(op2);
                    push(op2);
                }
                else if(strcmp(s, "swap") == 0)
                {
                    double op1;
                    op2 = pop();
                    op1 = pop();
                    push(op2);
                    push(op1);
                }
                else if (strcmp(s, "clear") == 0)
                {
                    sp = 0;
                }
                else if (strcmp(s, "sin") == 0)
                {
                    push(sin(pop()));
                }
                else if (strcmp(s, "cos") == 0)
                {
                    push(cos(pop()));
                }
                else if (strcmp(s, "exp") == 0)
                {
                    push(exp(pop()));
                }
                else if (strcmp(s, "pow") == 0)
                {
                    double exponent = pop();
                    push(pow(pop(), exponent));
                }
                break;
            }
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2) {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '%':
                op2 = pop();
                if (op2) {
                    push((int)pop() % (int)op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '\n':
                printf("%.2g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                exit(EXIT_FAILURE);
                break;
        }
    }
    return 0;
}

char buf[MAXN];
int bufp = 0;

int q_getch(void)
{
    return (bufp>0) ? buf[--bufp] : getchar();
}

void q_ungetch(int c)
{
    if (c == EOF) {
        printf("q_ungetch: end of file\n");
        exit(EXIT_FAILURE);
    }
    if(bufp >= MAXN)
        printf("q_ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}



void push(double f)
{
    if(sp < MAXN)
    {
        //printf("push %.2f\n", f);
        val[sp++] = f;
    }
    else
    {
        printf("push: stack full, cannot push %g\n", f);
        exit(EXIT_FAILURE);
    }
}

double pop(void)
{
    if (sp >0) {
        double f = val[--sp];
        //printf("pop %.2f\n", f);
        return f;
    }
    else
    {
        printf("pop: stack empty\n");
        exit(EXIT_FAILURE);
    }
}

int getop(char *s)
{
    int c, i;
    
    i = 0;
    while ((s[0] = c = q_getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = q_getch())) {
            ;
        }
        s[i] = '\0';
        q_ungetch(c);
        return COMMAND;
    }
    else if (c == '-') {
        if (isdigit(s[++i] = c = q_getch())) {
            while (isdigit(s[++i] = c = q_getch()))
                ;
        }
        else
        {
            q_ungetch(c);
            return '-';
        }
    }
   
    else if (!isdigit(c) && c != '.' )
    {
        return c;
    }
    else {
        while (isdigit(s[++i] = c = q_getch())) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] =c = q_getch())) {
            ;
        }
    }
    s[i] = '\0';
    q_ungetch(c);
    return NUMBER;
}


double qatof(char *s)
{
    double val, power;
    int i, sign, sign_exp, exp;
    
    for (i = 0; isspace(s[i]); ++i) {
        ;
    }
    sign = (s[i] =='-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }
    for (val = 0.; isdigit(s[i]); ++i) {
        val = 10. * val + s[i] - '0';
    }
    if (s[i] == '.') {
        ++i;
    }
    for (power = 1.; isdigit(s[i]); ++i) {
        val = 10. *val + s[i] - '0';
        power *= 10.;
    }
    if (s[i] == 'e' || s[i] =='E') {
        ++i;
        sign_exp = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            ++i;
        }
        for (exp = 0; isdigit(s[i]); ++i) {
            exp = 10 * exp + s[i] - '0';
        }
        if(sign_exp < 0)
        {
            while (exp) {
                val /= 10.;
                --exp;
            }
        }
        else
        {
            while (exp) {
                val *= 10.;
                --exp;
            }
        }
    }
    return sign * val / power;
}


