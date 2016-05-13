//
//  main.c
//  2-10
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int lower(char c)
{
    return (c>='A' && c<='Z') ? (c-'A'+'a') : c;
}
int main(int argc, const char * argv[])
{
    char c = 'F';
    printf("tolower %c->%c\n", c, lower(c));
    return 0;
}

