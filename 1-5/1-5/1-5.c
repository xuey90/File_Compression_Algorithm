//
//  main.c
//  1-5
//
//  Created by Xueyong Qian on 23/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{

    int i;
    
    printf("Cel Fah\n");
    for(i = 300; i >= 0; i-=20)
    {
        printf("%3d %3d\n", i, 9*i/5+32);
    }
    return 0;
}

