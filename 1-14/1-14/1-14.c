//
//  main.c
//  1-14
//
//  Created by Xueyong Qian on 24/03/14.
//  Copyright (c) 2614 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#define LEN 10

int main(int argc, const char * argv[])
{

    int i, j, c, max;
    FILE*ifp;
    int nchar[26];
    
    max  = 0;
    ifp = fopen("1-14.c", "r");
    for(i = 0; i< 26; ++i)
        nchar[i] = 0;
    
    while((c = getc(ifp)) != EOF)
    {
        if(c >= 'a' && c <= 'z')
        {
            nchar[c-'a']++;
        }
    }
    
    //calculate the max of the array
    for(i = 0; i< 26; ++i)
    {
        if(nchar[i] > max)
            max = nchar[i];
    }
    
    //Adjust the length of each column
    for(i = 0; i< 26; ++i)
    {
        if(nchar[i])
        {
            nchar[i] = nchar[i] * LEN / max;
            if(!nchar[i])
            {
                ++nchar[i];
            }
        }
    }
    
    //print horizontal
    /*
     for(i = 0; i< 26; ++i)
     {
     if(nchar[i])
     {
     printf("%3d:", i);
     for (j = 0; j< nchar[i]; ++j) {
     putchar('*');
     }
     putchar('\n');
     }
     }
     */
    //print vertical
    for(i = 0; i < LEN; ++i)
    {
        for(j = 0; j < 26; ++j)
        {
            if(nchar[j])
            {
                if(nchar[j] + i >= LEN)
                    printf(" * ");
                else
                    printf("   ");
            }
        }
        putchar('\n');
    }
    for (i = 0; i< 26; ++i) {
        if (nchar[i]) {
            printf(" %c ", 'a'+i);
        }
    }
    putchar('\n');
    return 0;
}

