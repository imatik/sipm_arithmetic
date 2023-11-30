#include "stdio.h"
#include <stdlib.h>
char* rEsize(char* int_res,const unsigned int size);

char* Freader(const char *filename,bool* positive,unsigned int* SIZE)
{
    *positive =1;
    FILE *file = fopen(filename, "r");

    char ch = ' ';
    char* num = malloc(sizeof(char));

    unsigned int sizef = 0;
    if(!file){
        printf("%s","Файл не найден!\n");
    }else {
        int i = 0;// iterator
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '-') {
                *positive = 0;
                continue;
            } else {
                num = rEsize(num,sizeof(char)*(i+1));
                num[i] = ch;
                i++;
                sizef++;
            }

        }
    }

    *SIZE = sizef;
    fclose(file);
    return num;
}

char* rEsize(char* int_res,const unsigned int size){
    char* new_res = malloc(sizeof(char) *(size));
    for(int i = 0; i< size-1;i++) {
        new_res[i] = int_res[i];
    }

    free(int_res);
    return new_res;
}