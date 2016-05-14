//
//  utility.c
//  compress
//
//  Created by Xueyong Qian on 30/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include "compress.h"

char *concat(char *prefix, char letter)
{
    char *result = (char *)malloc(strlen(prefix) + 2);
    sprintf(result, "%s%c", prefix, letter);
    return result;
}

long long str_bit(char* c)
{
    long long value = 0;
    while (*c) {
        value |= *c - '0';
        value <<= 1;
        ++c;
    }
    value >>= 1;
    return value;
}

char* bit_str(long long c, int len)
{
	char *p = (char*)malloc(sizeof(char) * (len + 1));
	char *cp = p;
    while (len) {
		*cp++ =( (c & 1 << (len-1) ) >> (len-1) )+ '0';
		--len;
	}
	*cp = '\0';
	return p;
}

void print_cano(Canonical_code *cacocode)
{
    while (cacocode) {
        printf("%d %d %lld\n", cacocode->letter,cacocode->length, cacocode->value);
        cacocode = cacocode->next;
    }
}

void print_table(char codetable[Num][CodeLength])
{
    int i;
    for (i = 0; i< Num; ++i) {
        if (strlen(codetable[i]) > 0) {
            printf("%d %s\n", i, codetable[i]);
        }
    }
}

int depth(Node*tree)
{
    if (tree == NULL) {
        return 0;
    }
    int left = depth(tree->left);
    int right = depth(tree->right);
    return (left<right)? right+1 : left+1;
}

void push(List** ls, int letter)
{
	static List* tail = NULL;
    List * temp ;
	if(*ls == NULL){
        temp= (List*)malloc(sizeof(List));
		temp->letter = letter;
		temp->next = NULL;
        *ls = temp;
		tail = *ls;
	}
	else{
       	temp= (List*)malloc(sizeof(List));
		temp->letter = letter;
		temp->next = NULL;
        tail->next = temp;
        tail = temp;
	}
}

void print_list(List *ls, FILE* ifp)
{
    while (ls) {
        fputc(ls->letter, ifp);
        //fprintf(ifp, "%d ", ls->letter);
        ls = ls->next;
    }
}

void delete_list(List *ls)
{
    List *temp = ls;
    while (ls) {
        temp = ls->next;
        free(ls);
        ls = temp;
    }
}
