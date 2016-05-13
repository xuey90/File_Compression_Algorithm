#include "compress.h"

int main()
{
    Node *tree, *nls;
    List *mtf_ls, *bwt_ls, *in_ls = NULL;
    Canonical_code* canocode = NULL;
    char code[CodeLength] = {'\0'};
    char codetable[Num][CodeLength] ;
    int compressed;
    char filename[20];
    FILE *input, *output;
    int i;
    for (i = 0; i < Num; ++i) {
        codetable[i][0] ='\0';
    }
    
    printf("Type the name of the file to process:\n");
    scanf("%s",filename);
    printf("Type 1 to zip and 2 to unzip\n");
    scanf("%d",&compressed);
    
    if((input = fopen(filename, "r")) == NULL){
        printf("error: cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
   
    if (compressed == 1) {
        printf("Please choose the combination of algorithm:\nType b for discrete files like normal text files, html files, etc...\nType m for highly duplicated files like uncompressed image files, bmp, etc...\nType h for others!\n");
        char algorithm_filed;
        char str_temp [10];
        scanf("%s", str_temp);
        algorithm_filed = str_temp[0];
        
        while ((i = getc(input)) != EOF) {
            push(&in_ls, i);
        }
        switch (tolower(algorithm_filed)) {
            case 'b':
                bwt_ls = bwt_encode(in_ls);
                mtf_ls = mtf_encode(bwt_ls);
                in_ls = rle_encode(mtf_ls);
                delete_list((bwt_ls));
                delete_list(mtf_ls);
                break;
            case 'm':
                mtf_ls = mtf_encode(in_ls);
                in_ls = rle_encode(mtf_ls);
                delete_list(mtf_ls);
                break;
        }
        init_freq(in_ls, &nls);
        
        build_huffman(&tree, nls);
        fill_table(codetable, tree, code);
        delete_tree(tree);
        fill_canonical(codetable, &canocode);
        if ((output =fopen("zip", "w")) == NULL) {
            printf("error: cannot open file zip\n");
            exit(EXIT_FAILURE);
        }
        compress(in_ls,output,codetable, canocode, algorithm_filed);
        delete_list(in_ls);
        delete_canonical(canocode);
    }
    else{
        if ((output=fopen("unzip", "w")) == NULL) {
            printf("error: cannot open file unzip\n");
            exit(EXIT_FAILURE);
        }
        List *dels, *mtf_dels, *rle_dels;
        char field;
        dels = decompress(input, &field);
        switch (field) {
            case 'b':
                rle_dels =rle_decode(dels);
                mtf_dels = mtf_decode(rle_dels);
                dels =bwt_decode(mtf_dels);
                delete_list(rle_dels);
                delete_list(mtf_ls);
                break;
            case 'm':
                rle_dels = rle_decode(dels);
                dels =mtf_decode(rle_dels);
                delete_list(rle_dels);
            default:
                break;
        }
        print_list(dels, output);
        delete_list(dels);
    }
    fclose(input);
    fclose(output);
    return 0;
}