//
//  main.c
//  1-9
//
//  Created by Xueyong Qian on 23/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#define IN 1
#define OUT 0
int main(int argc, const char * argv[])
{
    
    int c, state;
    FILE* ifp;
    
    ifp = fopen("1-9.c","r");
    state = IN;
    while((c=getc(ifp)) != EOF){
        if(c == ' ' ){
            if( state == IN){
                putchar(' ');
                state =OUT;
            }
        }
        else{
            putchar(c);
            state = IN;
        }
    }
    fclose(ifp);
    return 0;
}

