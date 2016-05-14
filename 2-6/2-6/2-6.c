//
//  main.c
//  2-6
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    int setbit = (~(~0 << n) & y) << (p-n+1);
    return (x & ~(~(~0 << n) << (p-n+1)) )| setbit;
}
int main(int argc, const char * argv[])
{

    unsigned x = 30;
    unsigned y = 2;
    x = setbits(x, 4, 1, y);
    printf("%u\n", x);
    return 0;
}

