//
//  main.c
//  1-23
//
//  Created by Xueyong Qian on 27/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
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

int main(int argc, const char * argv[])
{
    
    int c, nextc;
    FILE *ifp;
    
    ifp = fopen("1-16.c", "r");
    while ((c=getc(ifp))!=EOF) {
        if(c == '/')
        {
            if((nextc = getc(ifp)) == '/' || nextc == '*')
                comment(nextc, ifp);
            else if (nextc == EOF)
            {
                putchar(c);
                break;
            }
            else
            {
                putchar(c);
                putchar(nextc);
            }
        }
        else
            putchar(c);
    }
    fclose(ifp);
    return 0;
}

