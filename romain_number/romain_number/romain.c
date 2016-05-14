//
//  main.c
//  romain_number
//
//  Created by Xueyong Qian on 31/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int get_value(char c)
{
    switch (toupper(c)) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
    }
}

int romain_to_int(char *start, char *pos, int max)
{
    if (start != pos) {
        if (get_value(*pos) >= max) {
            max = get_value(*pos);
            return romain_to_int(start, pos-1, max) + get_value(*pos);
        }
        else
        {
            return romain_to_int(start, pos-1, max) - get_value(*pos);
        }
    }
    else
    {
        return get_value(*start);
    }
}

int romain_to_int_recursive(char *s)
{
    char *end = s;
    while (*++end) {
        ;
    }
    --end;
    return romain_to_int(s, end, 0);
}
int romain_to_int_norecursive(char *s)
{
    char *end = s;
    while (*end++)
        ;
    int value, max;
    value = max = 0;
    /*
     int size = 0;
     while (s[size])
     ++size;
     for (--size; size>=0; --size) {
     if (get_value(s[size]) >= max) {
     max = get_value(s[size]);
     value += max;
     }
     else
     {
     value -= get_value(s[size]);
     }
     }
     */
    do
    {
        --end;
        if(get_value(*end) >= max)
        {
            max = get_value(*end);
            value += max;
        }
        else
        {
            value -= get_value(*end);
        }
    }while(end != s);
    
    return value;
}
int main(int argc, const char * argv[])
{
    char *s="MDCCCXXIV";
    printf("%d\n", romain_to_int_recursive(s));
//  printf("%d\n", romain_to_int_norecursive(s));
    
    return 0;
}
