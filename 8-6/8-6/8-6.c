//
//  main.c
//  8-6
//
//  Created by Xueyong Qian on 27/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#define NALLOC 1024

typedef long Align;
typedef union header {
    struct {
        union header *ptr;
        unsigned size;
    }s;
    Align x;
} Header;

static Header base;
static Header *freep = NULL;

void q_free(void *ap);
static Header *morecore(unsigned nu);

void *q_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits = (nbytes + sizeof(Header)-1)/sizeof(Header) + 1;
    
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            }
            else{
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void*)(p+1);
        }
        if (p == freep) {
            if ((p = morecore(nunits)) ==  NULL) {
                return NULL;
            }
        }
    }
}

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;
    
    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if(cp == (char*)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    q_free((void*)(up+1));
    return freep;
}

void q_free(void *ap)
{
    Header *bp, *p;
    bp = (Header*)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr &&(bp>p || bp < p->s.ptr)) {
            break;
        }
    }
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}

void* q_calloc(unsigned n, unsigned size)
{
    unsigned len = n * size;
    int i;
    
    char *cp = (char*)q_malloc(len);
    for (i = 0; i< len; ++i) {
        cp[i] = 0;
    }
    return (void *)cp;
}
int main(int argc, const char * argv[])
{

    int *p = (int*)q_calloc(7, sizeof(int));
    
    printf("%d\n", p[5]);
    return 0;
}

