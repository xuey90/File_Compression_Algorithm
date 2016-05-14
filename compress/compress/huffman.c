//
//  compress.c
//  compress
//
//  Created by Xueyong Qian on 30/05/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include "compress.h"

long long letter_freq[Num];

Node* makenode(int letter, long long value);
Node* insert(Node** ls, int letter, long long value);
Canonical_code* makecanonical(int letter, int length, long long value);
Canonical_code *insert_canonical(Canonical_code** cacocode, int letter,int length, long long value);

void compress(List *ls, FILE *output, char codetable[Num][CodeLength], Canonical_code* canocode, char field)
{
    int length_of_table = 0, length_of_fake_eof = 0, x = 0;
    int c,bitsLeft = 8;
    char *cp;
    
    Canonical_code* temp = canocode;
    while (temp) {
        ++length_of_table;
        if (temp->letter == Num - 1) {
            length_of_fake_eof = temp->length;
        }
        temp = temp->next;
    }
    length_of_table -= 2;
    putc(field, output);            //We put the choice of algorithm.
    putc(length_of_table, output);  //We put the length of canonical table in the first byte of compressed file.
    putc(length_of_fake_eof, output);
    
    temp = canocode;
    while (temp) {
        if (temp->letter != Num - 1) {
            putc(temp->letter, output);
            putc(temp->length, output);
        }
        temp = temp->next;
    }
    
    while (1){
        if (ls == NULL) {
            c = Num - 1;
        }
        else{
            c = ls->letter;
        }
        cp = codetable[c];
        while (*cp){
            x = x | (*cp - '0');
            bitsLeft--;
            if (bitsLeft==0){
                putc(x,output);
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
            ++cp;
        }
        if (c == Num - 1) {
            break;
        }
        ls = ls->next;
    }
    if (bitsLeft!=8){
        x = x << (bitsLeft-1);
        fputc(x,output);
    }
    return;
}

char getbit(FILE* input)
{
	static char buffer;
	static unsigned char mask = 1 << 7;
	static char count = 0;
	if(count == 8)
		count = 0;
	if(count == 0){
		if((buffer = getc(input)) == EOF && feof(input)){
            count = 0;
            return 2;
		}
		else{
			++count;
			return (buffer & mask) != 0;
		}
	}
	else{
		++count;
		buffer <<= 1;
		return (buffer & mask) != 0;
	}
}

List* decompress(FILE* input, char* field)
{
    int c, letter, length, length_of_table = 0, length_of_fake_eof = 0;
    long long code = 0;
    long i = 0;
    Canonical_code* canocode = NULL;
    Canonical_code* temp;
    List *ls = NULL;
    *field = getc(input);
    length_of_table = getc(input);
    length_of_fake_eof = getc(input);
    for (i = 0; i <= length_of_table ; ++i) {
        letter = getc(input);
        length = getc(input);
        insert_canonical(&canocode, letter, length, 0);
    }
    insert_canonical(&canocode, Num - 1, length_of_fake_eof, 0);
    
    temp = canocode;
    temp->value = code;
    while (temp && temp->next) {
        code = (code + 1) << (temp->next->length - temp->length);
        temp->next->value = code;
        temp = temp->next;
    }
    
    long max = 0;
    temp = canocode;
    while (temp) {
        if (temp->length > max) {
            max = temp->length;
        }
        temp = temp->next;
    }
    long *length_table = (long*)malloc(sizeof(long)*(max+1));
    for (i = 0; i < max+1; ++i) {
        length_table[i] = 0;
    }
    temp = canocode;
    while (temp) {
        ++length_table[temp->length];
        temp =  temp->next;
    }
    long long first_code = 0, first_index = 0, row = 0, pos = 0, bit = 0;
    while ((c = getbit(input)) != 2) {
        bit |= c;
        first_code <<= 1;
        ++row;
        temp = canocode;
        if (bit - first_code < length_table[row]) {
            pos = bit - first_code + first_index;
            while (pos) {
                temp = temp->next;
                --pos;
            }
            if (temp->letter == Num - 1) {
                return ls;
            }
            push(&ls, temp->letter);
            bit = first_code = first_index = row = pos = 0;
        }
        else{
            first_code += length_table[row];
            first_index += length_table[row];
            bit <<= 1;
        }
    }
    
    delete_canonical(canocode);
    return ls;
}

void init_freq(List *list, Node** nls)
{
    int i;
    while (list) {
        ++letter_freq[list->letter];
        list = list->next;
    }
    letter_freq[Num-1] = 1;     //Num-1 signal the end of file
    for (i = 0; i < Num; ++i) {
        if(letter_freq[i])
            insert(nls, i, letter_freq[i]);
    }
}

void build_huffman(Node **tree, Node* ls)
{
    Node *temp = NULL;
    while (ls && ls->next) {
        temp = insert(&ls, Num, ls->value + ls->next->value);
        temp->left = ls;
        temp->right = ls->next;
        ls = ls->next->next;
    }
    *tree = temp;
    return;
}

void fill_table(char codetable[Num][CodeLength], Node *tree, char* code)
{
    if (tree->letter < Num){
        strcpy(codetable[tree->letter], code);
    }
    else{
        fill_table(codetable, tree->left, concat(code, '0'));
        fill_table(codetable, tree->right, concat(code, '1'));
    }
    return;
}

void delete_tree(Node *tree)
{
    if (tree) {
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree);
    }
}

void fill_canonical(char codetable[Num][CodeLength], Canonical_code** canocode)
{
    int len;
    int i;
    long long code = 0;
    Canonical_code* temp;
    for (i = 0; i < Num; ++i) {
        if ((len = (int)strlen(codetable[i])) >0) {
            insert_canonical(canocode, i, len, str_bit(codetable[i]));
        }
    }
    temp = *canocode;
    temp->value = code;
    while (temp && temp->next) {
        code = (code + 1) << (temp->next->length - temp->length);
        temp->next->value = code;
        temp = temp->next;
    }
    temp = *canocode;
    while (temp) {
        strcpy(codetable[temp->letter], bit_str(temp->value, temp->length));
        temp = temp->next;
    }
}

void delete_canonical(Canonical_code* cacocode)
{
    Canonical_code* next = cacocode;
    while (cacocode) {
        next = cacocode->next;
        free(cacocode);
        cacocode = next;
    }
}

Node* makenode(int letter, long long value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = letter;
    node->value = value;
    node->left = node->right = node->next = NULL;
    return node;
}

Node* insert(Node** ls, int letter, long long value)
{
    Node* temp, *current;
    if (*ls == NULL || value < (*ls)->value) {
        temp = makenode(letter, value);
        temp->next = *ls;
        *ls = temp;
        return *ls;
    }
    else{
        current = *ls;
        while (current->next && (value > current->next->value )) {
            current = current->next;
        }
        temp = makenode(letter, value);
        temp->next = current->next;
        current->next = temp;
        return temp;
    }
}

Canonical_code* makecanonical(int letter, int length, long long value)
{
    Canonical_code* temp = (Canonical_code*)malloc(sizeof(Canonical_code));
    temp->letter = letter;
    temp->length= length;
    temp->value = value;
    temp->next = NULL;
    return temp;
}

Canonical_code *insert_canonical(Canonical_code** cacocode, int letter,int length, long long value)
{
    Canonical_code* temp, *current;
    if (*cacocode == NULL || length < (*cacocode)->length ||((length == (*cacocode)->length) && letter < (*cacocode)->letter)) {
        temp = makecanonical(letter, length, value);
        temp->next = *cacocode;
        *cacocode = temp;
        return *cacocode;
    }
    else{
        current = *cacocode;
        while (current->next && (length > current->next->length)) {
            current= current->next;
        }
        while (current->next && current->next->length == length && letter > current->next->letter) {
            current = current->next;
        }
        temp = makecanonical(letter, length, value);
        temp->next = current->next;
        current->next = temp;
        return temp;
    }
}


