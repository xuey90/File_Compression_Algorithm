//
//  main.c
//  1-11
//
//  Created by Xueyong Qian on 24/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#define IN 1
#define OUT 0
int main(int argc, const char * argv[])
{
    int c, nl, nw, nc, state;
    FILE *ifp;
    ifp = fopen("1-11.c","r");

    nl = nw = nc = 0;
    state = OUT;
    while((c=getc(ifp))!=EOF)
    {
        ++nc;
        if(c == '\n')
        {
            ++nl;
            state = OUT;
        }
        else if(c == ' ' || c == '\t')
        {
            state = OUT;
        }
        else{
            if(state == OUT)
            {
                state = IN;
                ++nw;
            }
        }
            
    }
    printf("Number of lines:%d\twords:%d\tcharacters:%d\n", nl, nw, nc);
    fclose(ifp);
    return 0;
}

