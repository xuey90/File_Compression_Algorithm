//
//  mtf.c
//  compress
//
//  Created by Xueyong Qian on 02/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include "compress.h"

int mtf(List** ls, int c)
{
	int count = 0;
	List *temp, *parent;
	parent = temp = *ls;
    
	while(temp->letter != c ){
		++count;
		parent = temp;
		temp = temp->next;
	}
    if (temp != *ls) {
        parent->next = temp->next;
        temp->next = *ls;
        *ls = temp;
    }
	return count;
}

int get_mtf(List **ls, int i )
{
	List *parent, *temp ;
    parent = temp = *ls;
    
	while( i-- ) {
        parent = temp;
		temp = temp->next;
	}
	if (temp != *ls) {
        parent->next = temp->next;
        temp->next = *ls;
        *ls = temp;
    }
    return temp->letter;
}

List* mtf_encode(List *ls)
{
	int c;
	List *table = NULL;
    List *temp = NULL;
	for(c = 0; c < 256; ++c){
		push(&table, c);
	}
	while (ls) {
        push(&temp,mtf(&table, ls->letter));
        ls = ls->next;
	}
    return temp;
}

List* mtf_decode (List *ls)
{
	int i;
	
	List *table = NULL;
    List *temp = NULL;
	for(i = 0; i < 256; ++i){
		push(&table, i);
	}
	while (ls) {
		push(&temp, get_mtf(&table,ls->letter));
        ls = ls->next;
	}
    return temp;
}
