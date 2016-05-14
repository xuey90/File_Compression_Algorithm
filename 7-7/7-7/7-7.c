//
//  main.c
//  7-7
//
//  Created by Xueyong Qian on 16/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

int main(int argc, const char * argv[])
{
    char line[MAXLINE], *name;
    long lineno = 0;
    int c, except = 0, number = 0;
    FILE *ifp;
    
    char pattern[100];
    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                    
                default:
                    printf("find: illegal option %c\n", c);
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }
    strcpy(pattern, *argv);
    if (argc < 1) {
        printf("usage: find -x -n pattern\n");
        exit(EXIT_FAILURE);
    }
    else if(argc == 1)
    {
        while(fgets(line, MAXLINE, stdin)){
            ++lineno;
            if (strstr(line, pattern) != NULL) {
                if(number)
                    printf("%ld:", lineno);
                printf("%s", line);
            }
        }
    }
    else {
        while (--argc > 0) {
            name = *++argv;
            ifp = fopen(name, "r");
            lineno = 0;
            while(fgets(line, MAXLINE, ifp)){
                ++lineno;
                if (strstr(line, pattern) != NULL) {
                    printf("%s: ", name);
                    if(number)
                        printf("%ld ", lineno);
                    printf("%s", line);
                }
            }
            fclose(ifp);
        }
    }
    return 0;
}

