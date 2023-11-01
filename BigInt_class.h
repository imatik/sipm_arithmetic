#include <stdlib.h>
#include <stdio.h>
#include "event_class.h"
#include "fileworker.h"

typedef struct class_BigInt{
    unsigned int SIZE;
    char* num;
    BigInt_event* listner;

}BigInt;

BigInt* create_bigint(const char *filename){
    BigInt* new_num = malloc(sizeof(BigInt));
    if(new_num == NULL){
        printf("%s","Не удолось выделить память для числа!\n");
        return NULL;
    }
    printf("%s","Сработал конструктор БигИнта\n");

    new_num->num = Freader(filename);

    return new_num;
}

void BigInt_destruct(BigInt* num){
    printf("%s","Сработал деструктор\n");
    free(num->listner);
    free(num->num);
    free(num);
    num=NULL;
}

void BigInt_set_listner(BigInt* num,BigInt_event* listner){
    num->listner = listner;
}







