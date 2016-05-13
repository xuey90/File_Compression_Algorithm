//
//  main.c
//  7-6
//
//  Created by Xueyong Qian on 16/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    FILE* if1, *if2;
    char s1[100], s2[100];
    
    if (argc != 3) {
        printf("error: you must specify too file names to compare!\n");
        exit(EXIT_FAILURE);
    }
    if((if1 = fopen(argv[1], "r")) == NULL){
        printf("error: cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if((if2 = fopen(argv[2], "r")) == NULL){
        printf("error: cannot open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    while (fgets(s1, 100, if1) && fgets(s2, 100, if2)) {
        if (strcmp(s1,s2)) {
            printf("%s: %s\n%s: %s\n", argv[1], s1, argv[2], s2);
        }
    }
    return 0;
}

