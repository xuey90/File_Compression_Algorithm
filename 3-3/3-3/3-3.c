//
//  main.c
//  3-3
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i= gap; i<n; ++i) {
            for (j = i - gap; j>= 0 && v[j] > v[j+gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

void expand(char *s1, char* s2)
{
    char i, j;
    for (i= 0; s1[i]; ++i) {
        if(s1[i] == '-' && i)
        {
            if (!s1[i+1]) {
                *s2++ = '-';
                break;
            }
            for(j = s1[i-1]+1; j< s1[i+1]; ++j){
                *s2++ = j;
            }
        }
        else
            *s2++ = s1[i];
    }
    *s2 = '\0';
}
int main(int argc, const char * argv[])
{
    /*
     int i, n;
     int v[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
     n = sizeof(v) / sizeof(v[0]);
     shellsort(v, n);
     for (i = 0; i < n; ++i) {
     printf("%d\t", v[i]);
     }
     */
    char s1[] = "-sdg-s-x02-9-";
    char s2[100];
    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
}

