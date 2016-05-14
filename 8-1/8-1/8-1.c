//
//  main.c
//  8-1
//
//  Created by Xueyong Qian on 26/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

void error(char *fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

void filecopy(int fd_in, int fd_out)
{
	int n;
	char buf[BUFSIZ];
	while((n = read(fd_in,buf,BUFSIZ)) >0)
		write(fd_out,buf,n);
}

int main(int argc, char *argv[])
{
	int fd;
	char *prog = argv[0];
	if(argc == 1)
		filecopy(0, 1);
	else{
		while(--argc > 0){
			if((fd = open(*++argv, O_RDONLY, 0)) == -1){
				error("cat: can't open %s", *argv);
			}
			else{
				filecopy(fd, 1);
				close(fd);
			}
		}
	}
	exit(0);
}

