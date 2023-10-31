#include <stdlib.h>
#include <stdio.h>
#include "event_class.h"

typedef struct class_BigInt{
    unsigned int SIZE;
    char* num;
    BigInt_event* listner;

}BigInt;

BigInt* create_bigint(){
    BigInt* new_num = malloc(sizeof(BigInt));
    if(new_num == NULL){
        printf("%s","Не удолось выделить память для числа!\n");
        return NULL;
    }
    printf("%s","Сработал конструктор БигИнта\n");



    return new_num;
}

void destruct_bigint(BigInt* num){
    printf("%s","Сработал деструктор\n");
    free(num->listner);
    free(num->num);
    free(num);
    num=NULL;
}

void BigInt_set_listner(BigInt* num,BigInt_event* listner){
    num->listner = listner;
}





