//
//  compress.h
//  compress
//
//  Created by Xueyong Qian on 30/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#ifndef compress_compress_h
#define compress_compress_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define Num 257
#define CodeLength 128

typedef struct list_t{
	unsigned char letter;
	struct list_t* next;
}List;

struct node{
    long long value;
    int letter;
    struct node *left, *right, *next;
};
typedef struct node Node;

typedef struct canonical{
    int letter;
    int length;
    long long value;
    struct canonical*next;
} Canonical_code;

List* decompress(FILE*, char*);
char *concat(char *prefix, char letter);
long long str_bit(char* c);
char* bit_str(long long c, int len);
int depth(Node*tree);
Canonical_code *insert_canonical(Canonical_code** cacocode, int letter,int length, long long value);

void init_freq(List* ls, Node** nls);
void build_huffman(Node **tree, Node* ls);
void fill_table(char codetable[Num][CodeLength], Node *tree, char* code);
void delete_tree(Node *tree);
void fill_canonical(char codetable[Num][CodeLength], Canonical_code** canocode);
void delete_canonical(Canonical_code* cacocode);
void print_cano(Canonical_code *cacocode);
void print_table(char codetable[Num][CodeLength]);
void compress(List *ls, FILE *output, char codetable[Num][CodeLength], Canonical_code* canocode, char field);

void push(List** ls, int letter);
void print_list(List *ls, FILE* ifp);
List* mtf_decode (List *ls);
List* mtf_encode(List *ls);
List* rle_decode(List*);
List* rle_encode(List *ls);
void delete_list(List *ls);

List* bwt_encode (List* ls );
List* bwt_decode (List* ls );
#endif
