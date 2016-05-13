//
//  main.c
//  1-15
//
//  Created by Xueyong Qian on 24/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

double fah_to_cel(int fah)
{
    return 5./9*(fah-32);
}
int main(int argc, const char * argv[])
{

    int i;
    
    printf("Fah Celsius\n");
    for(i = 0; i < 300; i+=20)
    {
        printf("%3d %6.1f\n", i, fah_to_cel(i));
    }
    return 0;
}

