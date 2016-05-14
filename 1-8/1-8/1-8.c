//
//  main.c
//  1-8
//
//  Created by Xueyong Qian on 23/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{

    int nb, nt, nl, c;
    FILE *ifp;
    nb = nt = nl = 0;
    ifp = fopen("1-8.c","r");
    
    while((c = getc(ifp))!= EOF){
        if(c == ' ')
            ++nb;
        else if(c=='\t')
            ++nt;
        else if(c == '\n')
            ++nl;
    }
    printf("\nnumber of blanks, tabs, lines:%d\t%d\t%d\n", nb, nt, nl);
    fclose(ifp);
    return 0;
}

