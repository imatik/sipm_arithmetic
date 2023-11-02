#include <stdlib.h>
#include <stdio.h>
#include "event_class.h"
#include "fileworker.h"
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)

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
    //printf("%s","Сработал конструктор БигИнта\n");

    new_num->SIZE = get_sizeF(filename);
    new_num->num = Freader(filename);

    return new_num;
}

void BigInt_destruct(BigInt* num){
    //printf("%s","Сработал деструктор\n");
    free(num->listner);
    free(num->num);
    free(num);
    num=NULL;
}

void BigInt_set_listner(BigInt* num,BigInt_event* listner){
    num->listner = listner;
}

int* BigInt_char_to_int(BigInt* new_num)
{
    int* numer = malloc(sizeof(int)*new_num->SIZE);
    for (int i=0;i<new_num->SIZE;i++)
        numer[new_num->SIZE-i-1]=new_num->num[i]-'0';
    return numer;
}

void BigInt_int_to_char(int* int_num,BigInt* pnum){

    pnum->num = malloc(sizeof(char)*pnum->SIZE);

    for(int i =0;i<pnum->SIZE;i++){
        pnum->num[pnum->SIZE - i - 1] = int_num[i]+'0';

    }

    for(int i =0;i<pnum->SIZE;i++){
        printf("%c",pnum->num[i]);
    }
}

BigInt* BigInt_plus(BigInt* num1,BigInt* num2){
    int* int_num1 = BigInt_char_to_int(num1);
    int* int_num2 = BigInt_char_to_int(num2);

    unsigned int min_size = MIN(num1->SIZE,num2->SIZE);
    unsigned int max_size = MAX(num1->SIZE,num2->SIZE);

    int* int_res = malloc(sizeof (int)*(max_size + 1));
    BigInt* res = malloc(sizeof (BigInt));


    for(int i =0; i<max_size+1;i++){
        int_res[i] = 0;
    }

    for(int i =0; i < max_size;i++){
        if(i<min_size) {
            if ((int_res[i] + int_num1[i] + int_num2[i]) / 10 > 0) {
                int_res[i] = (int_res[i] + int_num1[i] + int_num2[i]) % 10;
                int_res[i + 1]++;
            } else {

                int_res[i] = (int_res[i] + int_num1[i] + int_num2[i]);
            }
        }else {
            if (num1->SIZE > num2->SIZE) {
                if ((int_res[i] + int_num1[i]) / 10 > 0) {
                    int_res[i] = (int_res[i] + int_num1[i]) % 10;
                    int_res[i + 1]++;
                } else {

                    int_res[i] = (int_res[i] + int_num1[i]);
                }

            } else {
                if ((int_res[i] + int_num2[i]) / 10 > 0) {
                    int_res[i] = (int_res[i] + int_num2[i]) % 10;
                    int_res[i + 1]++;
                } else {

                    int_res[i] = (int_res[i] + int_num2[i]);
                }
            }
        }
    }

    if(int_res[max_size+1]==0){
        res->SIZE = max_size;
        int_res = realloc(int_res,max_size);
    }else
        res->SIZE= max_size + 1;

    BigInt_int_to_char(int_res,res);

    return res;
}





