#include "stdio.h"
#include <stdlib.h>

unsigned int get_sizeF(const char *filename){
    FILE *file = fopen(filename, "r");
    char ch = ' ';
    unsigned int sizef = 0;
    if(!file){
        printf("%s","Файл не найден!\n");
    }else
        while((ch = fgetc(file))!=EOF) {
            sizef++;
        }



    fclose(file);

    return sizef;
}

char* Freader(const char *filename)
{
    FILE *file = fopen(filename, "r");

    char ch = ' ';

    char* num = malloc(sizeof(char)* get_sizeF(filename));

    //printf("%u",get_sizeF(filename));

    int i = 0;// iterator
    while((ch = fgetc(file))!=EOF) {
        num[i] = ch;
        printf("%c",num[i]);
        i++;
    }


    fclose(file);
    return num;
}