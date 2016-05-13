//
//  main.c
//  1-10
//
//  Created by Xueyong Qian on 23/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{

    int c;
    FILE *ifp;
    ifp = fopen("1-10.c","r");
    while((c = getc(ifp))!= EOF)
    {
        if(c =='\t')
            printf("\\t");
        else if(c == '\\')
            printf("\\\\");
        else
            putchar(c);
    }
    fclose(ifp);
    return 0;
}

