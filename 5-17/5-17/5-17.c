//
//  main.c
//  5-17
//
//  Created by Xueyong Qian on 07/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

int f_strcmp(char *s1, char* s2)
{
    char t1[MAXN], t2[MAXN];
    strcpy(t1, s1);
    strcpy(t2, s2);
    int i;
    for (i = 0; t1[i]; ++i) {
        t1[i] = tolower(t1[i]);
    }
    for (i = 0; t2[i]; ++i) {
        t2[i] = tolower(t2[i]);
    }
    return strcmp(t1, t2);
}

int fr_strcmp(char *s1, char* s2)
{
    char t1[MAXN], t2[MAXN];
    strcpy(t1, s1);
    strcpy(t2, s2);
    int i;
    for (i = 0; t1[i]; ++i) {
        t1[i] = tolower(t1[i]);
    }
    for (i = 0; t2[i]; ++i) {
        t2[i] = tolower(t2[i]);
    }
    return -strcmp(t1, t2);
}

int d_strcmp(char *s1, char* s2)
{
    while (*s1) {
        while (!(isspace(*s1) || isalnum(*s1))) {
            ++s1;
        }
        while (!(isspace(*s2) || isalnum(*s2))) {
            ++s2;
        }
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        else{
            ++s1;
            ++s2;
        }
    }
        return *s1 - *s2;
}

int dr_strcmp(char *s1, char* s2)
{
    while (*s1) {
        while (!(isspace(*s1) || isalnum(*s1))) {
            ++s1;
        }
        while (!(isspace(*s2) || isalnum(*s2))) {
            ++s2;
        }
        if (*s1 != *s2) {
            return *s2 - *s1;
        }
        else{
            ++s1;
            ++s2;
        }
    }
    return *s2 - *s1;
}
int fd_strcmp(char *s1, char* s2)
{
    char t1[MAXN], t2[MAXN];
    strcpy(t1, s1);
    strcpy(t2, s2);
    int i;
    for (i = 0; t1[i]; ++i) {
        t1[i] = tolower(t1[i]);
    }
    for (i = 0; t2[i]; ++i) {
        t2[i] = tolower(t2[i]);
    }
    return d_strcmp(t1, t2);
}

int fdr_strcmp(char *s1, char* s2)
{
    char t1[MAXN], t2[MAXN];
    strcpy(t1, s1);
    strcpy(t2, s2);
    int i;
    for (i = 0; t1[i]; ++i) {
        t1[i] = tolower(t1[i]);
    }
    for (i = 0; t2[i]; ++i) {
        t2[i] = tolower(t2[i]);
    }
    return -d_strcmp(t1, t2);
}

char* getfield(char *s, int p1, int p2)
{
    int i;
    char *field = (char*)malloc(sizeof(char)*MAXN);
    char *temp = field;
    while (isspace(*s)) {
        ++s;
    }
    for (i = 1; i < p1; ++i) {
        while (!isspace(*s)) {
            ++s;
        }
        while (isspace(*s)) {
            ++s;
        }
    }
    for (i = p1; i <= p2; ++i) {
        while (*s && !isspace(*s)) {
            *temp++ = *s;
            ++s;
        }
        while (isspace(*s)) {
            ++s;
        }
    }
    *temp = '\0';
    return field;
}

void qk_sort(void *v[], int field1, int field2, int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if ((*comp)(getfield(v[i], field1, field2), getfield(v[left], field1, field2) ) < 0) {
            swap(v, i, ++last);
        }
    }
    swap(v, left, last);
    qk_sort(v, field1, field2, left, last -1 , comp);
    qk_sort(v, field1, field2, last + 1, right, comp);
}
int main(int argc, const char * argv[])
{
    
    int nlines, numeric, num1, num2, reverse, fold, dic, field, c;
    int p1, p2, p3, p4, fre, i;
    p1 = p2 = p3 = p4 = fre = 0;
    numeric = num1 = num2 = reverse = fold = dic = field = 0;
    
    while (--argc >0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                case 'd':
                    dic = 1;
                    break;
                case 'k':
                {
                    int n1, n2;
                    n1 = n2 = 0;
                    field = 1;
                    while ((c = *++argv[0]) >= '0' && c <= '9' ){
                        n1 = 10 * n1 + c - '0';
                    }
                    while ((c = *++argv[0]) >= '0' && c <= '9' ){
                        n2 = 10 * n2 + c - '0';
                    }
                    if (fre == 0) {
                        p1 = n1;
                        p2 = n2;
                        if (c == 'n') {
                            num1 = 1;
                        }
                    }
                    else{
                        p3 = n1;
                        p4 = n2;
                        if (c == 'n') {
                            num2 = 1;
                        }
                    }
                    ++fre;
                    if(!*argv[0])
                        --argv[0];
                    break;
                }
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
        if ((nlines = readlines(lineptr, MAXN)) >= 0)
        {
            if (numeric)
            {
                if(reverse)
                    q_sort((void**)lineptr, 0, nlines -1, r_numcmp);
                else
                    q_sort((void**)lineptr, 0, nlines -1, numcmp);
            }
            else if (field)
            {
                if (num1) {
                    qk_sort(lineptr, p1, p2, 0, nlines -1,  numcmp);
                }
                else
                    qk_sort(lineptr, p1, p2, 0, nlines -1,strcmp);
                if (!p3 && !p4) {
                    int first, last;
                    first = last = 0;
                    for (i = 0; i < nlines -1; ++i) {
                        if (strcmp(getfield(lineptr[i], p1, p2), getfield(lineptr[i+1], p1, p2)) == 0) {
                            first = i;
                            while (i+2 < nlines && strcmp(getfield(lineptr[first], p1, p2), getfield(lineptr[i+2], p1, p2)) == 0) {
                                ++i;
                            }
                            last = ++i;
                            if (num2) {
                                qk_sort(lineptr, p3, p4, first, last, numcmp);
                            }
                            else{
                                qk_sort(lineptr, p3, p4, first, last, strcmp);
                            }
                        }
                    }
                }
                
            }
            else
            {
                if (fold) {
                    if (reverse)
                    {
                        if (dic) {
                            q_sort(lineptr, 0, nlines - 1, fdr_strcmp);
                        }
                        else
                            q_sort(lineptr, 0, nlines - 1, fr_strcmp);
                    }
                    else{
                        if (dic) {
                            q_sort(lineptr, 0, nlines - 1, fd_strcmp);
                        }
                        else
                            q_sort(lineptr, 0, nlines - 1, f_strcmp);
                    }
                }
                else
                {
                    if (reverse)
                    {
                        if (dic) {
                            q_sort(lineptr, 0, nlines - 1, dr_strcmp);
                        }
                        else
                            q_sort((void**)lineptr, 0, nlines -1, r_strcmp);
                    }
                    else
                    {
                        if (dic) {
                            q_sort(lineptr, 0, nlines - 1, d_strcmp);
                        }
                        else
                            q_sort((void**)lineptr, 0, nlines -1, strcmp);
                    }
                }
            }
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


