//
//  main.c
//  6-4
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
    struct tnode* left;
    struct tnode* right;
} treenode;

typedef struct tlist{
    char* word;
    int count;
    struct tlist* next;
} list;
int maxc = 1;

treenode* addtree(treenode*, char*);
void treefill(treenode*,list** );
int getword(char*, int, FILE*);

int main(int argc, const char * argv[])
{
    treenode* root = NULL;
    int i;
    list* temp;
    char word[MAXWORD];
    
    FILE* ifp = fopen("6-2.c", "r");
    while (getword(word, MAXWORD, ifp) != EOF) {
        if (isalpha(word[0]) && strlen(word) > 1) {
            root = addtree(root, word);
        }
    }
    list *ls[maxc];
    for (i = 1; i <= maxc; ++i) {
        ls[i] = NULL;
    }
    treefill(root, ls);
    for (i = maxc; i > 0; --i) {
        temp = ls[i];
        while (temp) {
            printf("%4d %s\n", temp->count, temp->word);
            temp = temp->next;
        }
    }
    fclose(ifp);
    return 0;
}

treenode* addtree(treenode* p, char* w)
{
    int cond;
    
    if (!p) {
        p = (treenode*)malloc(sizeof(treenode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w, p->word)) == 0){
        p->count++;
        if (p->count > maxc) {
            maxc = p->count;
        }
    }
    else if(cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void treefill(treenode* p, list** ls)
{
    if (p) {
        treefill(p->left, ls);
        list *nls = (list*)malloc(sizeof(list));
        nls->count = p->count;
        nls->word = p->word;
        nls->next = NULL;
        if (!ls[p->count]) {
            ls[p->count] = nls;
        }
        else{
            list *temp = ls[p->count];
            list* parent = temp;
            
            while (temp != NULL) {
                parent = temp;
                temp = temp->next;
            }
            parent->next = nls;
            
        }
        treefill(p->right, ls);
    }
}

int getword(char* word, int lim, FILE* ifp)
{
    int c, nextc;
    char *w = word;
    while (isspace(c = getc(ifp)))
        ;
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


