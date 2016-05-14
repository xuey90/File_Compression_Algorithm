//
//  main.c
//  8-3
//
//  Created by Xueyong Qian on 26/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#define QMAX 20

#define PERMS 0666
#define q_getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : fillbuf(p))
#define q_putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x): flushbuf((x),p))

typedef struct {
	unsigned int _READ:1;
	unsigned int _WRITE:1;
    unsigned int _UNBUF:1;
	unsigned int _EOF:1;
	unsigned int _ERR:1;
} flags;

typedef struct{
	int cnt;
	char *ptr;
	char *base;
	flags flag;
	int fd;
} qFILE;

flags make_flag(char read, char write, char unbuf){
	flags f;
	f._READ = read;
	f._WRITE = write;
	f._UNBUF = unbuf;
	return f;
}
qFILE iob[QMAX];

qFILE *qfopen(char *name, char *mode)
{
	int fd;
	qFILE* fp;
	if(*mode !='r'&& *mode != 'w' && *mode != 'a')
		return NULL;
	for(fp = &iob[3]; fp < iob+QMAX; ++fp){
		if(fp->flag._READ == 0 && fp->flag._WRITE ==0)
			break;
	}
	if(fp >= iob+QMAX)
		return NULL;
	if(*mode == 'w')
		fd = creat(name, PERMS);
	else if(*mode =='a'){
		if((fd = open(name, O_RDONLY, 0)) ==-1)
			fd = creat(name, PERMS);
		lseek(fd, 0, 2);
	}
	else{
		fd = open(name, O_RDONLY, 0);
	}
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ?make_flag(1,0,0) : make_flag(0,1,0);
	return fp;
}

int fillbuf(qFILE *fp)
{
    int bufsize;
    if(fp->flag._READ == 0)
        return EOF;
    bufsize = fp->flag._UNBUF == 1 ? 1 : 1024;
    if (fp->base == NULL) {
        if((fp->base = (char*)malloc(bufsize)) == NULL)
            return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt <0) {
        if(fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int flushbuf(int x, qFILE *fp)
{
    int bufsize;
    if(fp->flag._WRITE == 0)
        return EOF;
    bufsize = fp->flag._UNBUF == 1 ? 1 : 1024;
    if (fp->base == NULL) {
        if((fp->base = (char*)malloc(bufsize)) == NULL)
            return EOF;
        else{
            
            fp->ptr = fp->base;
            *fp->ptr++ = x;
            fp->cnt = bufsize - 1;
            return x;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = write(fp->fd, fp->base, bufsize);
    if (--fp->cnt <0) {
        if(fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    
    return x;
}

int q_fflush(qFILE *fp)
{
    if (fp->flag._WRITE !=1) {
        return EOF;
    }
    if(write(fp->fd, fp->base, 1024) == -1){
        fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return 0;
}

int q_fclose(qFILE *fp)
{
    if (fp->flag._WRITE == 1) {
        if(q_fflush(fp) == EOF)
            return  EOF;
    }
    fp->cnt = 0;
    fp->ptr = fp->base;
    fp->flag._WRITE = fp->flag._READ = fp->flag._UNBUF = fp->flag._ERR = fp->flag._EOF = 0;
    return 0;
}

int main(int argc, const char * argv[])
{
    qFILE *fp;
    int c;
    if((fp = qfopen("abc","w")) == NULL)
        printf("error\n");
    else{
        
        while((c = getchar())!=EOF)
            q_putc(c, fp);
    }
    q_fclose(fp);
}

