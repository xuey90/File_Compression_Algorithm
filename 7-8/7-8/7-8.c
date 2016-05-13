//
//  main.c
//  7-8
//
//  Created by Xueyong Qian on 17/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

int main(int argc, const char * argv[])
{
    FILE* ifp;
    char* name, line[MAXLINE];
    int lineno, page;
    
    lineno = page = 0;
    while (--argc > 0) {
        ++page;
        name = *++argv;
        ifp = fopen(name, "r");
        printf("\t\t%s\n", name);
        lineno = 0;
        while(fgets(line, MAXLINE, ifp)){
            ++lineno;
            printf("%d ", lineno);
            printf("%s", line);
        }
        printf("\t\tPage %d\n\n\n", page);
        fclose(ifp);
    }
    
    return 0;
}

