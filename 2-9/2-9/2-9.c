//
//  main.c
//  2-9
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int bitcount(unsigned x)
{
    int count;
    for (count = 0; x; ++count) {
        x &= x-1;
    }
    return count;
}
int main(int argc, const char * argv[])
{

    printf("%d\n", bitcount(6));
    return 0;
}

