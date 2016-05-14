//
//  main.c
//  2-7
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p-n+1));
}
int main(int argc, const char * argv[])
{

    unsigned x= 17;
    printf("%u\n", invert(x, 3, 2));
    return 0;
}

