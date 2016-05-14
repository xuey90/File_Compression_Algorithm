//
//  main.c
//  5-14
//
//  Created by Xueyong Qian on 24/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000
char* lineptr[MAXN];

void swap(void* v[], int i, int j)
{
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int getl(char s[], int lim, FILE*ifp)
{
    int c, i, n;
    
    for(i = n = 0; (c = getc(ifp))!=EOF && c!='\n'; ++n)
    {
        if(i<lim-2){
            s[i++] = c;
        }
    }
    if(c == '\n')
    {
        s[i++] = c;
        ++n;
    }
    s[i] = '\0';
    return n;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXN];
    
    nlines = 0;
    while ((len = getl(line, MAXN, stdin)) > 0) {
        if(nlines >= maxlines || (p = (char*)malloc(len * sizeof(char))) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char* lineptr[], int nlines)
{
    while (nlines -- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void q_sort(void *v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, i, ++last);
        }
    }
    swap(v, left, last);
    q_sort(v, left, last -1 , comp);
    q_sort(v, last + 1, right, comp);
}

int numcmp(char* s1, char* s2)
{
    double res = atof(s1) - atof(s2);
    if (res < 0)
        return -1;
    else if (res > 0)
        return 1;
    else
        return 0;
}

int r_numcmp(char* s1, char* s2)
{
    double res = atof(s1) - atof(s2);
    if (res < 0)
        return 1;
    else if (res > 0)
        return -1;
    else
        return 0;
}

int r_strcmp(char* s1, char* s2)
{
    return -strcmp(s1, s2);
}

int main(int argc, const char * argv[])
{
    int nlines, numeric, reverse, c;
    numeric = reverse = 0;
    
    while (--argc >0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                   case 'r':
                    reverse = 1;
                    break;
                default:
                    printf("sort: illegal option %c\n", c);
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }
    if (argc != 0) {
        printf("usage: sort -r -n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if ((nlines = readlines(lineptr, MAXN)) >= 0) {
            if (numeric && reverse)
                q_sort((void**)lineptr, 0, nlines -1, r_numcmp);
            if (numeric && !reverse)
                q_sort((void**)lineptr, 0, nlines -1, numcmp);
            if (!numeric && reverse)
                q_sort((void**)lineptr, 0, nlines -1, r_strcmp);
            if (!numeric && !reverse)
                q_sort((void**)lineptr, 0, nlines -1, strcmp);
            writelines(lineptr, nlines);
        }
        else
        {
            printf("input too big to sort\n");
            exit(EXIT_FAILURE);
        }
        
    }
    return 0;
}

