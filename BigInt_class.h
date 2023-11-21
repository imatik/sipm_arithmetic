#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "event_class.h"
#include "fileworker.h"
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)


BigInt* BigInt_subtr(BigInt* num1,BigInt* num2);
BigInt* BigInt_plus(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_max(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_min(const BigInt* num1,const BigInt* num2);


typedef struct class_BigInt{
    unsigned int SIZE;
    char* num;
    BigInt_event* listner;
    bool positive ;
}BigInt;

BigInt* create_bigint(const char *filename){

    BigInt* new_num = malloc(sizeof(BigInt));
    if(new_num == NULL){
        printf("%s","Не удолось выделить память для числа!\n");
        return NULL;
    }
    //printf("%s","Сработал конструктор БигИнта\n");


    new_num->num = Freader(filename,&new_num->positive,&new_num->SIZE);


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
    for (int i=0;i<new_num->SIZE;i++){
        numer[new_num->SIZE-i-1]=new_num->num[i]-'0';
        printf("%i ",numer[new_num->SIZE-i-1]);
    }
    printf("\n");
    return numer;
}

void BigInt_int_to_char(int* int_num,BigInt* pnum){

    pnum->num = malloc(sizeof(char)*pnum->SIZE);

    for(int i =0;i<pnum->SIZE;i++){
        pnum->num[pnum->SIZE - i - 1] = int_num[i]+'0';
    }

}


//Сложение
BigInt* BigInt_plus(const BigInt* num1,const BigInt* num2){
    bool res_positive;

    if(num1->positive!=num2->positive){
        BigInt* res = BigInt_subtr(num1,num2);
        return res;
    }else if(num1->positive == num2->positive && num1->positive == 0)
        res_positive = 0;


    int* i_MAX_NUM = (num1->SIZE > num2->SIZE) ? BigInt_char_to_int(num1):BigInt_char_to_int(num2);
    int* i_MIN_NUM = (num2->SIZE < num1->SIZE) ? BigInt_char_to_int(num2):BigInt_char_to_int(num1);

    unsigned int min_size = MIN(num1->SIZE,num2->SIZE);
    unsigned int max_size = MAX(num1->SIZE,num2->SIZE);

    int* int_res = malloc(sizeof (int)*(max_size + 1));
    BigInt* res = malloc(sizeof (BigInt));

    for(int i =0; i<max_size+1;i++){
        int_res[i] = 0;
    }

    for(int i =0; i < max_size;i++){
        if(i<min_size) {
            if ((int_res[i] + i_MAX_NUM[i] + i_MIN_NUM[i]) / 10 > 0) {
                int_res[i] = (int_res[i] + i_MAX_NUM[i] + i_MIN_NUM[i]) % 10;
                int_res[i + 1]++;
            } else {

                int_res[i] = (int_res[i] + i_MAX_NUM[i] + i_MIN_NUM[i]);
            }
        }else {

            if ((int_res[i] + i_MAX_NUM[i]) / 10 > 0) {
                int_res[i] = (int_res[i] + i_MAX_NUM[i]) % 10;
                int_res[i + 1]++;
            } else {

                int_res[i] = (int_res[i] + i_MAX_NUM[i]);
            }

        }
    }

    if(int_res[max_size]==0){
        res->SIZE = max_size;
        int_res = realloc(int_res,max_size);
    }else
        res->SIZE= max_size + 1;

    res->positive = res_positive;

    BigInt_int_to_char(int_res,res);

    return res;
}


//Вычитание
BigInt* BigInt_subtr(BigInt* num1,BigInt* num2){

    if(num1->positive==false && num2->positive == true){
        num2->positive = false;// для того что б попасть в if в сложении (80 строчка)
        return BigInt_plus(num1,num2);
    }

    if(num1->positive==true && num2->positive == false){
        num2->positive = true;// для того что б попасть в if в сложении
        return BigInt_plus(num1,num2);
    }

    BigInt* res = malloc(sizeof (BigInt));

    if(num1->SIZE < num2->SIZE){

        int* i_MAX_NUM = BigInt_char_to_int(num2);
        int* i_MIN_NUM = BigInt_char_to_int(num1);

        for(int i = 0;i<num1->SIZE;i++){
            if(i_MAX_NUM[i] - i_MIN_NUM[i] < 0){
                int j = 1;
                while(i_MAX_NUM[i+j] == 0 && i+j<num2->SIZE){
                    j++;
                }
                i_MAX_NUM[i+j]--;
                while(j!=1){
                    j--;
                    i_MAX_NUM[i+j] = 9;
                }
                i_MAX_NUM[i] += 10;
                i_MAX_NUM[i] -= i_MIN_NUM[i];
            }else
                i_MAX_NUM[i] -= i_MIN_NUM[i];
        }

        if(i_MAX_NUM[num2->SIZE - 1]==0){
            res->SIZE = num2->SIZE-1;
            i_MAX_NUM = realloc(i_MAX_NUM,num2->SIZE-1);
        }else
            res->SIZE = num2->SIZE;

        BigInt_int_to_char(i_MAX_NUM,res);

        if(num1->positive==1){
            res->positive = false;
        }else{
            res->positive = true;
        }

        return res;
    }

    if(num2->SIZE < num1->SIZE){

        int* i_MAX_NUM = BigInt_char_to_int(num1);
        int* i_MIN_NUM = BigInt_char_to_int(num2);

        for(int i = 0;i<num2->SIZE;i++){
            if(i_MAX_NUM[i] - i_MIN_NUM[i] < 0){
                int j = 1;
                while(i_MAX_NUM[i+j] == 0 && i+j<num1->SIZE){
                    j++;
                }
                i_MAX_NUM[i+j]--;
                while(j!=1){
                    j--;
                    i_MAX_NUM[i+j] = 9;
                }
                i_MAX_NUM[i] += 10;
                i_MAX_NUM[i] -= i_MIN_NUM[i];
            }else
                i_MAX_NUM[i] -= i_MIN_NUM[i];
        }

        if(i_MAX_NUM[num1->SIZE - 1]==0){
            res->SIZE = num1->SIZE-1;
            i_MAX_NUM = realloc(i_MAX_NUM,num1->SIZE-1);
        }else
            res->SIZE = num1->SIZE;

        BigInt_int_to_char(i_MAX_NUM,res);

        if(num2->positive==1){
            res->positive = true;
        }else{
            res->positive = false;
        }

        return res;
    }

    if(num1->SIZE == num2->SIZE){

        int* i_MAX_NUM = BigInt_char_to_int(BigInt_max(num1,num2));
        int* i_MIN_NUM = BigInt_char_to_int(BigInt_min(num1,num2));

        for(int i = 0;i<num2->SIZE;i++){
            if(i_MAX_NUM[i] - i_MIN_NUM[i] < 0){
                int j = 1;
                while(i_MAX_NUM[i+j] == 0 && i+j<num1->SIZE){
                    j++;
                }
                i_MAX_NUM[i+j]--;
                while(j!=1){
                    j--;
                    i_MAX_NUM[i+j] = 9;
                }
                i_MAX_NUM[i] += 10;
                i_MAX_NUM[i] -= i_MIN_NUM[i];
            }else
                i_MAX_NUM[i] -= i_MIN_NUM[i];
        }



        res->SIZE = BigInt_max(num1,num2)->SIZE;


        for(int i =1;i_MAX_NUM[num1->SIZE - i] ==0;i++) {
            res->SIZE = num1->SIZE - i;
        }

        i_MAX_NUM = realloc(i_MAX_NUM, res->SIZE);

        BigInt_int_to_char(i_MAX_NUM,res);

        if((num1->positive==1 || num1->positive==0) && num1->num == BigInt_max(num1,num2)->num){
            res->positive = true;
        }else{
            res->positive = false;
        }


        return res;
    }




}

BigInt* BigInt_max(const BigInt* num1,const BigInt* num2){
    int numer1;
    int numer2;
    if(num1->SIZE>num2->SIZE){
        return num1;
    }else if(num2->SIZE>num1->SIZE){
        return num2;
    }

    for (int i=0;i<num1->SIZE;i++){
        numer1=num1->num[i]-'0';
        numer2=num2->num[i]-'0';
        if(numer1 > numer2){
            return num1;
        }else if(numer2 > numer1){
            return num2;
        }
    }
}

BigInt* BigInt_min(const BigInt* num1,const BigInt* num2){
    int numer1;
    int numer2;
    if(num1->SIZE<num2->SIZE){
        return num1;
    }else if(num2->SIZE<num1->SIZE){
        return num2;
    }

    for (int i=0;i<num1->SIZE;i++){
        numer1=num1->num[i]-'0';
        numer2=num2->num[i]-'0';
        if(numer1 < numer2){
            return num1;
        }else if(numer2 < numer1){
            return num2;
        }
    }
}


void BigInt_display(const BigInt* num){

    for (int i = 0;i<num->SIZE;i++)
        printf("%c ",num->num[i]);
    printf("\nSIZE : %d\nPositive : %d\n",num->SIZE,num->positive);
}