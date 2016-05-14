//
//  main.c
//  3-1
//
//  Created by Xueyong Qian on 08/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int binarysearch(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if(x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
int main(int argc, const char * argv[])
{
    int v[] ={ 1, 3, 4, 5, 8, 11, 13};
    printf("%d\n", binarysearch(6, v, 7));
    return 0;
}

