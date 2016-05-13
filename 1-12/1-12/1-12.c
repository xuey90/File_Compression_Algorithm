//
//  main.c
//  1-12
//
//  Created by Xueyong Qian on 24/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#define IN 1
#define OUT 0

int main(int argc, const char * argv[])
{
    
    int c, state;
    FILE *ifp;
    
    state = OUT;
    ifp = fopen("1-12.c", "r");
    while((c=getc(ifp))!= EOF)
    {
        if(c == ' ' ||c == '\t' ||c == '\n')
        {
            if(state == IN)
                putchar('\n');
            state = OUT;
        }
        else
        {
            state = IN;
            putchar(c);
        }
    }
    fclose(ifp);
    return 0;
}

