//
//  bwt.c
//  compress
//
// The Burrows-Wheeler Transform; suitable for discrete text files. I include here as a optional parts of our project.
//  Created by Xueyong Qian on 02/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include "compress.h"

#define BWT_SIZE 255

unsigned char *bwt_buf;
unsigned int index_table[ BWT_SIZE ];
unsigned int freq[ 256 ];
unsigned int count = 0;
int bwt_comp( unsigned int *a, unsigned int *b );

List* bwt_encode (List* ls )
{
	unsigned int i = 0, last_index = BWT_SIZE;
	bwt_buf = (unsigned char *) malloc( BWT_SIZE * sizeof(unsigned char));
    List *bwt_ls = NULL;
    
	while( 1 ) {
        count = 0;
		for (i = 0; i< BWT_SIZE; ++i ){
            if (!ls) {
                break;
            }
            bwt_buf[i] = ls->letter;
            ls = ls->next;
            ++count;
        }
		if (count == 0) {
            return bwt_ls;
        }
		for ( i = 0; i < count; i++ ) {
			index_table[i] = i;
		}
        
		qsort( index_table,count, sizeof(int),
              (int (*) (const void *, const void *)) bwt_comp );
        
		last_index = count;
		for ( i = 0; i < count; i++ ){
			if ( index_table[i] == 0 ){
				push(&bwt_ls, bwt_buf[count-1]);
				last_index = i;
			}
			else push(&bwt_ls, bwt_buf[index_table[i] - 1]);
		}
        push(&bwt_ls, last_index);
	}
}

List* bwt_decode (List* ls )
{
	unsigned int i, findex, last_index;
	unsigned int sum, temp;
    List *bwt_ls = NULL;
	
	bwt_buf = (unsigned char *) malloc( BWT_SIZE * sizeof(unsigned char));
	while ( 1 ) {
        count = 0;
		for (i = 0; i< BWT_SIZE; ++i ){
            if (!ls) {
                break;
            }
            bwt_buf[i] = ls->letter;
            ls = ls->next;
            ++count;
        }
		if (count == 0) {
            return bwt_ls;
        }
        if (i == BWT_SIZE) {
            last_index = ls->letter;
            ls = ls->next;
        }
        else{
            last_index = bwt_buf[i-1];
            --count;
        }
		for ( i = 0; i < 256; i++ ) {
			freq[i] = 0;
		}
		
		for ( i = 0; i <count; i++ ) {
			freq[ bwt_buf[i] ]++;
		}
        
		sum = 0;
		for ( i = 0; i < 256; i++ ) {
			if ( freq[i] ) {
				temp = freq[i];
				freq[i] = sum;
				sum += temp;
			}
		}
		
		for ( i = 0; i <count; i++ ) {
			index_table[ freq[bwt_buf[i]]++ ] = i;
		}
		
		findex = index_table[last_index];
		while ( count-- ){
			push(&bwt_ls, bwt_buf[findex]);
			findex = index_table[ findex ];
		}
	}
}

int bwt_comp( unsigned int *a, unsigned int *b )
{
	register int a1 = *a, b1 = *b, tmp = a1;
	
	if ( bwt_buf[a1] != bwt_buf[b1] ) {
		if ( bwt_buf[a1] > bwt_buf[b1] ) return 1;
		else return -1;
	}
	else {
		do {
			if ( bwt_buf[++a1 ==count? a1 = 0 : a1]
                != bwt_buf[++b1 == count? b1 = 0 : b1] ) {
				if ( bwt_buf[a1] > bwt_buf[b1] ) return 1;
				else return -1;
			}
		} while ( a1 != tmp );
	}
	return 0;
}
