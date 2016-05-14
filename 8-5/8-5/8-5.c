//
//  main.c
//  8-5
//
//  Created by Xueyong Qian on 26/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dirent.h>
#define QMAX 20

typedef struct{
    long ino;
    char name[QMAX];
}Dirent;

typedef struct {
    int fd;
    Dirent d;
}Dir;

Dir * qopendir(char*);
Dirent *qreaddir(Dir*dfd);
void qclosedir(Dir *dfd);

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[QMAX];
    Dirent *dp;
    Dir *dfd;
    
    if((dfd = qopendir(dir)) == NULL){
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return ;
    }
    while ((dp = qreaddir(dfd))!=NULL) {
        if(strcmp(dp->name, ",")==0
           || strcmp(dp->name, "..") ==0)
            continue;
        if (strlen(dir) + strlen(dp->name) +2 > QMAX) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
        }
        else{
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    qclosedir(dfd);
}

void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("%8lld %s %lld %d %d %d\n", stbuf.st_size, name, stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_uid);
}

Dir * qopendir(char *dirname)
{
    int fd;
    struct stat stbuf;
    Dir *dp;
    
    if((fd = open(dirname, O_RDONLY, 0)) == -1
       || fstat(fd, &stbuf) == -1
       || (stbuf.st_mode & S_IFMT) != S_IFDIR
       || (dp = (Dir*)malloc(sizeof(Dir))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

void qclosedir(Dir *dp)
{
    if(dp){
        close(dp->fd);
        free(dp);
    }
}

Dirent *qreaddir(Dir *dp)
{
    struct dirent dirbuf;
    static Dirent d;
    
    while (read(dp->fd, (char*)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) {
            continue;
        }
        d.ino = dirbuf.d_ino;
        strcpy(d.name, dirbuf.d_name);
        return &d;
    }
    return NULL;
}

int main(int argc, const char * argv[])
{
    
    if(argc == 1)
        fsize(".");
    else{
        while (--argc >0) {
            fsize(*++argv);
        }
    }
}

