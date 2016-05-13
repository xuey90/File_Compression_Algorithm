//
//  main.c
//  3-5
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *s)
{
    int i, j, temp;
    for (i = 0, j = (int)strlen(s) - 1; i<j; ++i, --j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void qitob(int n, char *s, int b)
{
    int sign = n;
    char *pos = s;
    switch (b) {
        case 8:
            while (n) {
                *pos++ = abs(n%8) + '0';
                n /= 8;
            }
            *pos++ = '0';
            if (sign < 0) {
                *pos ++ = '-';
            }
            *pos = '\0';
            break;
        case 2:
            while (n) {
                *pos++ =abs(n%2) + '0';
                n /= 2;
            }
            if (sign < 0) {
                *pos ++ = '-';
            }
            *pos = '\0';
            break;
        case 16:
            while (n) {
                *pos++ = abs(n%16) < 10 ? abs(n%16) + '0' : abs(n % 16) +'a';
                n /= 16;
            }
            *pos++ = 'x';
            *pos++ = '0';
            if (sign < 0) {
                *pos ++ = '-';
            }
            *pos = '\0';
            break;
        default:
            printf("Unknown base\n");
            break;
    }
    reverse(s);
}

int main(int argc, const char * argv[])
{
    char s[999];
    qitob(-35, s, 2);
    printf("%s\n",s);
    return 0;
}

