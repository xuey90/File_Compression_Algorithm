//
//  main.c
//  1-13
//
//  Created by Xueyong Qian on 24/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#define IN 1
#define OUT 0
#define LEN 10

int main(int argc, const char * argv[])
{

    int i,j, max,  count,  c, state;
    int nword[20];
    FILE *ifp;
    ifp = fopen("1-13.c", "r");
    for(i = 0; i < 20; ++i)
    {
        nword[i] = 0;
    }
    state = OUT;
    count = max = 0;
    //Calculate the array nword
    while((c=getc(ifp))!=EOF)
    {
       if(isspace(c))
       {
           if(state == IN)
           {
               ++nword[count];
               count = 0;
           }
           state = OUT;
       }
       else{
           ++count;
           state = IN;
       }
    }
    
    //calculate the max of the array
    for(i = 0; i< 20; ++i)
    {
       if(nword[i] > max)
           max = nword[i];
    }
 
    //Adjust the length of each column
    for(i = 0; i< 20; ++i)
    {
        if(nword[i])
        {
            nword[i] = nword[i] * LEN / max;
            if(!nword[i])
            {
                ++nword[i];
            }
        }
    }
    
    //print horizontal
    /*
    for(i = 1; i< 20; ++i)
    {
        if(nword[i])
        {
            printf("%3d:", i);
            for (j = 0; j< nword[i]; ++j) {
                putchar('*');
            }
            putchar('\n');
        }
    }
   */
    //print vertical
    for(i = 0; i < LEN; ++i)
    {
        for(j = 1; j < 20; ++j)
        {
            if(nword[j])
            {
                if(nword[j] + i >= LEN)
                    printf(" * ");
                else
                    printf("   ");
            }
        }
        putchar('\n');
    }
    for (i = 1; i< 10; ++i) {
        if (nword[i]) {
            printf(" %d ", i);
        }
    }
    for (i = 10; i< 20; ++i) {
        if (nword[i]) {
            printf("%3d", i);
        }
    }
    putchar('\n');
    return 0;
}

