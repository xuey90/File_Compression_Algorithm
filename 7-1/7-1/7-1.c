//
//  main.c
//  7-1
//
//  Created by Xueyong Qian on 12/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
int main(int argc, const char * argv[])
{
    int c;
    if(*argv[1]=='l')
        while((c=getchar())!=EOF)
            putchar(tolower(c));
    else if(*argv[1]=='u')
        while((c=getchar())!=EOF)
            putchar(toupper(c));
    return 0;
}

