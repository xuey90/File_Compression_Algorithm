//
//  main.c
//  6-2
//
//  Created by Xueyong Qian on 10/05/14.
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
    struct tnode* next;
} treenode;

treenode* addtree(treenode*, char*);
void treeprint(treenode*);
int getword(char*, int, FILE*);

int field = 6;

int main(int argc, const char * argv[])
{
    treenode* root = NULL;
    char word[MAXWORD];
    FILE* ifp = fopen("6-2.c", "r");
    
    if (argc == 2) {
        field = atoi(++argv[1]);
    }
    while (getword(word, MAXWORD,ifp) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

treenode* addtree(treenode* p, char* w)
{
    int cond;
    treenode *temp, *parent;
    if (!p) {
        p = (treenode*)malloc(sizeof(treenode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = p->next = NULL;
    }
    else if((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else
    {
        if (strncmp(w, p->word, field) == 0) {
            parent = p;
            temp = p->next;
            while (temp) {
                if (strcmp(temp->word,w) == 0) {
                    temp->count++;
                    return p;
                }
                else
                {
                    parent = temp;
                    temp = temp->next;
                }
            }
            temp = (treenode*)malloc(sizeof(treenode));
            temp->word = strdup(w);
            temp->count = 1;
            temp->left = temp->right = temp->next = NULL;
            parent->next = temp;
        }
        else if(cond < 0)
            p->left = addtree(p->left, w);
        else
            p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint(treenode* p)
{
    treenode* temp;
    if (p) {
        treeprint(p->left);
        temp =p;
        putchar('\t');
        while (temp) {
            printf("%4d %s\n", temp->count, temp->word);
            temp = temp->next;
        }
        treeprint(p->right);
    }
}

void comment(char cm, FILE *ifp)
{
    int lastc, c;
    
    lastc = ' ';
    if(cm == '*')
    {
        while((c = getc(ifp)) != EOF)
        {
            if(lastc == '*' && c == '/' )
            {
                getc(ifp);
                break;
            }
            lastc = c;
        }
    }
    else if(cm =='/')
    {
        while((c=getc(ifp)) != '\n')
            ;
    }
}

int getword(char* word, int lim, FILE* ifp)
{
    int c, nextc;
    char *w = word;
    
    while (isspace(c = getc(ifp)))
        ;
    
    if(c == '/')
    {
        if((nextc = getc(ifp)) == '/' || nextc == '*')
        {
            comment(nextc, ifp);
            while (isspace(c = getc(ifp)))
                ;
        }
        else
        {
            ungetc(nextc, ifp);
            *w++ = c;
            *w = '\0';
            return c;
        }
    }
    else if(c == '#')
    {
        while ((c = getc(ifp)) != '\n')
            ;
        c = getc(ifp);
    }
    else if(c =='\'')
    {
        while((c=getc(ifp)) != '\'')
        {
            if(c == '\\')
                getc(ifp);
        }
        c = getc(ifp);
    }
    else if(c =='"')
    {
        while((c=getc(ifp)) != '"')
        {
            if(c == '\\')
                getc(ifp);
        }
        c = getc(ifp);
    }
    if(c != EOF)
        *w++ = c;
    if (!(isalpha(c) || c == '_')) {
        *w = '\0';
        return c;
    }
    for (; --lim > 1; ++w) {
        if (!(isalnum(*w = getc(ifp)) || *w == '_')) {
            ungetc(*w,ifp);
            break;
        }
    }
    *w = '\0';
    return word[0];
}