//
//  main.c
//  1-6
//
//  Created by Xueyong Qian on 23/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
int main(int argc, const char * argv[])
{

    int c;
    while(c = getchar()!= EOF)
        printf("%d\n", c);
    return 0;
}

