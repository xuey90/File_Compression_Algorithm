//
//  main.c
//  2-1
//
//  Created by Xueyong Qian on 06/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, const char * argv[])
{

    printf("char:%d\t%d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char:%d\n", UCHAR_MAX );
    printf("short:%d\t%d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short:%d\n", USHRT_MAX);
    printf("int:%d\t%d\n", INT_MIN, INT_MAX);
    printf("unsigned int:%u\n", UINT_MAX);
    printf("long:%ld\t%ld\n", LONG_MIN, LONG_MAX);
    
    printf("float%e\t%e\n", FLT_MIN, FLT_MAX);
    printf("double%e\t%e\n", DBL_MIN, DBL_MAX);
    printf("long double%Le\n", LDBL_MAX);
    return 0;
}

