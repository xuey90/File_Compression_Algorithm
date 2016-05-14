//
//  main.c
//  6-3
//
//  Created by Xueyong Qian on 14/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
typedef struct tnode{
    char* word;
    int count;
    int linec[MAXWORD];
    struct tnode* left;
    struct tnode* right;
} treenode;

treenode* addtree(treenode*, char*);
void treeprint(treenode*);
int getword(char*, int, FILE*);
int linec = 1;

int main(int argc, const char * argv[])
{
    treenode* root = NULL;
    char word[MAXWORD];
    FILE* ifp = fopen("6-2.c", "r");
    while (getword(word, MAXWORD, ifp) != EOF) {
        if (isalpha(word[0]) && strlen(word) > 1&& strcmp(word, "and") != 0 && strcmp(word, "the") != 0) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

treenode* addtree(treenode* p, char* w)
{
    int cond;
    
    if (!p) {
        p = (treenode*)malloc(sizeof(treenode));
        p->word = strdup(w);
        p->count = 1;
        p->linec[p->count-1] = linec;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w, p->word)) == 0)
    {
        if ((p->linec)[p->count-1] != linec) {
            p->count++;
            (p->linec)[p->count-1] = linec;
        }
    }
    else if(cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void treeprint(treenode* p)
{
    int i;
    if (p) {
        treeprint(p->left);
        printf("%s: ", p->word);
        for (i= 0; i< p->count; ++i) {
            printf((i == p->count - 1) ? "%d\n" : "%d\t", (p->linec)[i]);
        }
        treeprint(p->right);
    }
}


int getword(char* word, int lim, FILE* ifp)
{
    int c, nextc;
    char *w = word;
    while (isspace(c = getc(ifp))){
        if (c == '\n') {
            ++linec;
        }
    }
    if(c != EOF)
        *w++ = c;
    if (!(isalpha(c) || c == '_')) {
        *w = '\0';
        return c;
    }
    for (; --lim > 1; ++w) {
        if (!(isalnum(*w = getc(ifp)) || *w == '_')) {
            ungetc(*w, ifp);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

