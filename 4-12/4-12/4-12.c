//
//  main.c
//  4-12
//
//  Created by Xueyong Qian on 19/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(t,x,y){ t temp = x; x = y; y = temp;}

void reverse(char *start, char *end)
{
    if(start < end){
        swap(char, *start, *end);
        reverse(++start, --end);
    }
}
void itoa(int n, char *s)
{
    static int i = 0;
    if(n/10)
    {
        itoa(n/10 , s);
        s[i++] = abs(n%10) +'0';
        s[i] = '\0';
    }
    else{
        if (n < 0) {
            s[i++] = '-';
        }
        s[i++] = abs(n) + '0';
        s[i] = '\0';
    }
    
}

int main(int argc, const char * argv[])
{
    char *s = malloc(sizeof(char)*10);
    itoa(-1234, s);
    //reverse(s, &s[strlen(s)-1]);
    printf("%s\n", s);
    return 0;
}

