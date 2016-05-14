//
//  main.c
//  1-24
//
//  Created by Xueyong Qian on 27/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
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

void single_quote(FILE *ifp)
{
    int c;
    
    while((c=getc(ifp)) != '\'')
    {
        if(c == '\\')
            getc(ifp);
    }
}

void double_quote(FILE *ifp)
{
    int c;
    
    while((c=getc(ifp)) != '"')
    {
        if(c == '\\')
            getc(ifp);
    }
}

int main(int argc, const char * argv[])
{
    int c, nextc, nparentheses, nbrackets, nbraces;
    FILE *ifp;
    
    nparentheses = nbraces = nbrackets = 0;
    ifp = fopen("1-24.c", "r");
    while ((c=getc(ifp))!=EOF) {
        switch (c) {
            case '/':
                if((nextc = getc(ifp)) == '/' || nextc == '*')
                    comment(nextc, ifp);
                else
                {
                    ungetc(nextc, ifp);
                }
                break;
            case '\'':
                single_quote(ifp);
                break;
            case '"':
                double_quote(ifp);
                break;
            case '(':
                --nparentheses;
                break;
            case ')':
                ++nparentheses;
                break;
            case '[':
                --nbrackets;
                break;
            case ']':
                ++nbrackets;
                break;
            case '{':
                --nbraces;
                break;
            case '}':
                ++nbraces;
                break;
            default:
                break;
        }
    }
    fclose(ifp);
    if(nparentheses)
    {
        printf("Unmatched Parentheses:%d\n", abs(nparentheses));
    }
    if(nbrackets)
    {
        printf("Unmatched Brackets:%d\n", abs(nbrackets));
    }
    if(nbraces)
    {
        printf("Unmatched Braces:%d\n", abs(nbraces));
    }
    return 0;
}
