//
//  main.c
//  1-3
//
//  Created by Xueyong Qian on 11/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{
    
    int i;
    
    printf("Fah Celsius\n");
    for(i = 0; i < 300; i+=20)
    {
        printf("%3d %6.1f\n", i, 5./9*(i-32));
    }
    return 0;
}

