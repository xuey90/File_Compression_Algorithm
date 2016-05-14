//
//  main.c
//  7-2
//
//  Created by Xueyong Qian on 12/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#define LIMIT 20
int main(int argc, const char * argv[])
{

    int c,n;
    n=0;
    while((c=getchar())!=EOF){
        if(isgraph(c)){
            ++n;
            printf("%x",c);
        }
        
        if(c=='\n'||n>=LIMIT){
            n=0;
            putchar('\n');
        }
    }
    return 0;
}

