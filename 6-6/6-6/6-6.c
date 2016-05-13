//
//  main.c
//  6-6
//
//  Created by Xueyong Qian on 14/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define HASHSIZE 101

typedef struct nlist{
    struct nlist* next;
    char* name;
    char* defn;
}list;

static list* hashtab[HASHSIZE];

unsigned hash(char* s)
{
    unsigned hashval;
    for (hashval = 0; *s; ++s) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

list* lookup(char* s)
{
    list* np;
    for (np = hashtab[hash(s)]; np; np = np ->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

list* install(char* name, char* defn)
{
    list* np;
    
    if ((np = lookup(name)) == NULL) {
        np = (list*) malloc(sizeof(*np));
        np->name = strdup(name);
        np->next = hashtab[hash(name)];
        hashtab[hash(name)] = np;
    }
    else
        free(np->defn);
    np->defn = strdup(defn);
    return np;
}

void undef(char* s)
{
    list* np, *parent;
    
    for (np = parent= hashtab[hash(s)]; np; parent = np, np = np->next) {
        if (strcmp(s, np->name) == 0) {
            if (np == hashtab[hash(s)]) {
                hashtab[hash(s)] = NULL;
            }
            else{
                parent ->next = np->next;
            }
            free(np);
            return;
        }
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

int main(int argc, const char * argv[])
{
    char word[100];
    char name[100], defn[100];
    list* np;
    
    while (getword(word, 100, stdin) != EOF) {
        if(word[0] == '#')
        {
            getword(word, 100, stdin);
            if (strcmp(word, "define") == 0) {
                getword(name, 100, stdin);
                getword(defn, 100, stdin);
                install(name, defn);
            }
        }
        else{
            if ((np = lookup(word)) != NULL) {
                printf("%s: %s\n", np->name, np->defn);
            }
        }
    }
}


