#include "stdio.h"
#include <stdlib.h>

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
                num = realloc(num,sizeof(char)*(i+1));
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