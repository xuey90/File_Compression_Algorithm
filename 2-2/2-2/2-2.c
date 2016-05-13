//
//  main.c
//  2-2
//
//  Created by Xueyong Qian on 07/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int getl(char *s, int lim)
{
    int c,i;
    
    for(i = 0; i< lim -2; ++i)
    {
        if ((c = getchar()) != EOF) {
            if(c != '\n')
            {
                s[i] = c;
            }
            else
            {
                s[i++] = c;
                break;
            }
        }
        else
            break;
    }
    s[i] = '\0';
    return i;
    
}
int main(int argc, const char * argv[])
{
    
    char line[1000];
    while (getl(line, 1000)>0) {
        printf("%s",line);
    }
    return 0;
}

