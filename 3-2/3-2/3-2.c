//
//  main.c
//  3-2
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {int temp = a; b = a; a = temp;}
void escape(char *s,char *t)
{
    while (*t) {
        switch (*t) {
            case '\t':
                *s++ = '\\';
                *s++ = 't';
                break;
            case '\n':
                *s++ = '\\';
                *s++ = 'n';
            default:
                *s++ = *t;
                break;
        }
        ++t;
    }
    *s = '\0';
}

void deescape(char *s, char *t)
{
    while (*t) {
        if (*t == '\\') {
            switch (*++t) {
                case 't':
                    *s++ = '\t';
                    break;
                case 'n':
                    *s++ = '\n';
                    break;
                default:
                    *s++ = *t;
                    break;
            }
        }
        else
        {
            *s++ = *t;
        }
        ++t;
    }
    *s = '\0';
}
int main(int argc, const char * argv[])
{
    char s[9999], t[9999];
    char *pos = t;
    FILE *ifp = fopen("3-2.c", "r");
    while ((*pos = fgetc(ifp))!=EOF) {
        ++pos;
    }
    *pos = '\0';
    deescape(s, t);
    printf("%s", s);
    fclose(ifp);
    return 0;
}

