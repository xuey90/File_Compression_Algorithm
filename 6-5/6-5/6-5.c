//
//  main.c
//  6-5
//
//  Created by Xueyong Qian on 14/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int main(int argc, const char * argv[])
{
    install("book", "0");
    install("computer", "1");
    //undef("book");
    if (lookup("book")) {
        printf("found\n");
    }
    else
        printf("not found\n");
    return 0;
}

