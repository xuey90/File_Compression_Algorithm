//
//  rle.c
//  compress
//
//  Created by Xueyong Qian on 02/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include "compress.h"

List* rle_encode(List *ls)
{
    List *next, *temp = NULL;
    int c, prev, count = 0;
    
    prev = c = ls->letter;
    push(&temp, c);
    next = ls->next;
    
	while (next != NULL) {
        c = next->letter;
		if (c != prev) {
			if (count) {
				push(&temp, prev);
                push(&temp, count-1);
				count = 0;
			}
            
			push(&temp, c);
			prev = c;
		}
		else {
			if ((++count) == 256) {
				push(&temp, prev) ;
				push(&temp, 255);
				count = 0;
			}
		}
        next = next->next;
	}
    
	if (count) {
		push(&temp, prev);
		push(&temp,count-1);
	}
    return temp;
}

List* rle_decode(List* ls)
{
	int c, prev,count = 0;
    List *temp = NULL;
	
    prev = c = ls->letter;
    push(&temp,c);
    ls = ls->next;
	while (ls) {
        c = ls->letter;
		if (c == prev) {
			push(&temp, prev);
			if ((ls = ls->next)!=NULL) {
                count = ls->letter;
				while(count--) {
                    push(&temp, prev);
				}
			}
			else break;
		}
		else {
			push(&temp, c);
			prev = c;
		}
        ls = ls->next;
	}
    return temp;
}