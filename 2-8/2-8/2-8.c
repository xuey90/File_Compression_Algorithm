//
//  main.c
//  2-8
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

unsigned  rightrot(unsigned  x, int n)
{
    n %= 32;
    return (x >> n) | (x << (32-n));
}

int main(int argc, const char * argv[])
{
    printf("%u\n", rightrot(13, 3));
    return 0;
}

