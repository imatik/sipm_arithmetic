#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "event_class.h"
#include "fileworker.h"
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)


BigInt* BigInt_subtr(BigInt* num1,BigInt* num2);
BigInt* BigInt_plus(BigInt* num1,BigInt* num2);
BigInt* BigInt_multiplication(BigInt* num1,BigInt* num2);
BigInt* BigInt_div(BigInt* num1,BigInt* num2,BigInt* mod);
BigInt* BigInt_pow(const BigInt* num, const unsigned int power);
bool BigInt_equal(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_max(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_min(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_copy(const BigInt* num1);
bool BigInt_greater_equal(const BigInt* num1,const BigInt* num2);
BigInt* BigInt_copy_int(int i_num);
void BigInt_display(const BigInt* num);
int* resize(int* int_res,unsigned int size);
BigInt* cut(BigInt* main_num,unsigned int inx_l,unsigned int inx_r);

typedef struct class_BigInt{
    unsigned int SIZE;
    char* num;
    BigInt_event* listner;
    bool positive ;
}BigInt;

BigInt* create_bigint(const char *filename){

    BigInt* new_num = malloc(sizeof(BigInt));
    if(new_num == NULL){
        printf("%s","Не удалось выделить память для числа!\n");
        return NULL;
    }

    new_num->num = Freader(filename,&new_num->positive,&new_num->SIZE);

    return new_num;
}

void BigInt_destruct(BigInt* num){
    free(num->listner);
    free(num->num);
    free(num);
}

void BigInt_set_listner(BigInt* num,BigInt_event* listner){
    num->listner = listner;
}

int* BigInt_char_to_int(BigInt* new_num)
{
    int* numer = malloc(sizeof(int)*new_num->SIZE);
    for (int i=0;i<new_num->SIZE;i++){
        numer[new_num->SIZE-i-1]=new_num->num[i]-'0';
    }

    return numer;
}

void BigInt_int_to_char(int* int_num,BigInt* pnum){

    pnum->num = malloc(sizeof(char)*pnum->SIZE);

    for(int i =0;i<pnum->SIZE;i++){

        pnum->num[pnum->SIZE - i - 1] = int_num[i]+'0';

    }

}


//Сложение
BigInt* BigInt_plus(BigInt* num1,BigInt* num2){
    bool res_positive;


    if(num1->positive== true && num2->positive==false){
        num2->positive=true;
        BigInt* res = BigInt_subtr(num1,num2);
        num2->positive = false;
        return res;
    }else if(num1->positive== false && num2->positive==true){
        num1->positive=true;
        BigInt* res = BigInt_subtr(num2,num1);
        num1->positive=false;
        return res;
    }else if(num1->positive == num2->positive && num1->positive == 0)
        res_positive = 0;
    else if(num1->positive == num2->positive && num1->positive == 1)
        res_positive = 1;


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
        int_res = resize(int_res,max_size);
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
        BigInt* res = BigInt_plus(num1,num2);
        num2->positive = true;
        return res;
    }

    if(num1->positive==true && num2->positive == false){
        num2->positive = true;// для того что б попасть в if в сложении
        BigInt* res = BigInt_plus(num1,num2);
        num2->positive = false;
        return res;
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
            i_MAX_NUM = resize(i_MAX_NUM,num2->SIZE-1);
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

            i_MAX_NUM = resize(i_MAX_NUM,num1->SIZE-1);
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
            if(i == num1->SIZE)
                break;
            res->SIZE = num1->SIZE - i;
        }

        i_MAX_NUM = resize(i_MAX_NUM, res->SIZE);

        BigInt_int_to_char(i_MAX_NUM,res);

        if((num1->positive==1) && num1->num == BigInt_max(num1,num2)->num){
            res->positive = true;
        }else{
            res->positive = false;
        }


        return res;
    }

}


BigInt* BigInt_multiplication(BigInt* num1,BigInt* num2){
    int* i_MAX_NUM = (num1->SIZE > num2->SIZE) ? BigInt_char_to_int(num1):BigInt_char_to_int(num2);
    int* i_MIN_NUM = (num2->SIZE < num1->SIZE) ? BigInt_char_to_int(num2):BigInt_char_to_int(num1);

    unsigned int min_size = MIN(num1->SIZE,num2->SIZE);
    unsigned int max_size = MAX(num1->SIZE,num2->SIZE);

    int* int_res = malloc(sizeof(int)*(max_size+min_size));
    BigInt* res = malloc(sizeof(BigInt));

    for(int i =0; i<max_size+min_size;i++){
        int_res[i] = 0;
    }

    for(int i = 0;i<min_size;i++)
        for(int j = 0;j<max_size;j++){
            if(i_MIN_NUM[i]*i_MAX_NUM[j] > 9 && j + i + 1<max_size+min_size) {
                int_res[j + i + 1] += i_MIN_NUM[i] * i_MAX_NUM[j] / 10;
                int_res[j + i] += i_MIN_NUM[i] * i_MAX_NUM[j] % 10;
            }else
                int_res[j + i] += i_MIN_NUM[i] * i_MAX_NUM[j];

        }



    for (int i = 0;i<num1->SIZE+num2->SIZE;i++)
        if(int_res[i] > 9) {
            int_res[i + 1]+=int_res[i]/10;
            int_res[i]%=10;
        }
    if (num1->positive==num2->positive)
        res->positive=true;
    else
        res->positive=false;

    res->SIZE = min_size+max_size;

    for(int i =1;int_res[min_size+max_size-i]==0;i++) {
        if(i == min_size+max_size)
            break;
        res->SIZE= min_size+max_size - i;
    }

    int_res = resize(int_res,res->SIZE);
    BigInt_int_to_char(int_res,res);
    return res;
}


BigInt *BigInt_div(BigInt* num1,    //Делимое
                   BigInt* num2,    //Делитель
                   BigInt* mod      //Остаток
                   ){

    bool temp1_positive = num1->positive;
    bool temp2_positive = num2->positive;

    num1->positive = true;
    num2->positive = true;

    if(num2->SIZE==1 &&num2->num[0]=='0'){
        BigInt *res = malloc(sizeof (BigInt));
        res->num = malloc(sizeof (char)*8);
        res->num = "infinity";
        res->SIZE = 8;
        res->positive = true;
        return res;
    }


    if(num1->SIZE<num2->SIZE){
        BigInt *res = malloc(sizeof (BigInt));
        res->num = malloc(sizeof(char));
        res->num[0] = '0';
        res->SIZE = 1;
        res->positive = num1->positive == num2->positive?true:false;

        mod->SIZE = num1->SIZE;
        mod->positive = num1->positive;
        mod->num = num1->num;
        return res;
    }

    BigInt* res = malloc(sizeof (BigInt));
    res->SIZE = num1->SIZE-num2->SIZE + 1;
    res->num = malloc(sizeof (char)* num1->SIZE-num2->SIZE + 1);

    if(temp1_positive == temp2_positive)
        res->positive = true;
    else
        res->positive = false;

    for(int i = 0;i<num1->SIZE-num2->SIZE + 1;i++)
        res->num[i] = '0';

    int j = 0;
    int inx = 0;
    int i = 0;
    BigInt* temp_res;
    BigInt* buff;

    while(j<num1->SIZE){
        if(j==0) {
            temp_res = cut(num1, j, j + num2->SIZE - 1);
            j+=num2->SIZE - 1;
        }

        buff = BigInt_copy(num2);
        buff->positive = true;
        while(BigInt_greater_equal(temp_res,buff)){
            buff = BigInt_plus(buff,num2);
            i++;
        }
        if(i>0) {
            buff = BigInt_subtr(buff, num2);
            temp_res = BigInt_subtr(temp_res, buff);
        }

        if(j+1<num1->SIZE){
            if(temp_res->num[0]=='0'){
                temp_res->num[0] = num1->num[j + 1];
            }else {
                temp_res->num = rEsize(temp_res->num, temp_res->SIZE + 1);
                temp_res->num[temp_res->SIZE] = num1->num[j + 1];
                temp_res->SIZE++;
            }
            j++;
        }else {
            mod->SIZE = temp_res->SIZE;
            mod->positive = temp_res->positive;
            mod->num = temp_res->num;
            j++;
        }
        res->num[inx] = i + '0';
        inx++;
        i=0;



    }

    int k =0;
    int size =res->SIZE;
    while(res->num[k] =='0' && k<size){
        for(int i = k;i<size-1;i++)
            res->num[i] = res->num[i+1];
        size--;
        res->SIZE--;
        res->num = rEsize(res->num,size);
    }



    num1->positive = temp1_positive;
    num2->positive = temp2_positive;

    return res;
}


BigInt* BigInt_pow(const BigInt* num,const unsigned int power){
    BigInt* res = BigInt_copy(num);
    BigInt *pres1 = res;
    BigInt *pres2;

    if(power == 0){
        res->SIZE = 1;
        res->num = rEsize(res->num,1);
        res->num[0] = '1';
        return res;
    }

    for(unsigned int i = 0;i<power-1;i++){
        pres2 = res;
        res = BigInt_multiplication(res,num);
        free(pres2);
    }



    return res;
}


bool is_prime(BigInt* num){
    if(BigInt_greater_equal(BigInt_copy_int(1),num)) false;
    if(BigInt_greater_equal(BigInt_copy_int(3),num)) true;

    BigInt* mod1 = BigInt_copy_int(0);
    BigInt* mod2 = BigInt_copy_int(0);

    BigInt_div(num,BigInt_copy_int(2),mod1);
    BigInt_div(num,BigInt_copy_int(3),mod2);

    if( (BigInt_equal(mod1,BigInt_copy_int(0))) || (BigInt_equal(mod2, BigInt_copy_int(0))) ) return false;

    BigInt* i = BigInt_copy_int(5);


    while(BigInt_greater_equal(num, BigInt_multiplication(i,i))){

        BigInt_div(num,BigInt_copy(i),mod1);
        BigInt_div(num, BigInt_plus(BigInt_copy(i), BigInt_copy_int(2)),mod2);

        if( (BigInt_equal(mod1, BigInt_copy_int(0))) || (BigInt_equal(mod2, BigInt_copy_int(0))) ) return false;

        i = BigInt_plus(i, BigInt_copy_int(6));
    }
    return true;
}


bool BigInt_equal(const BigInt* num1,const BigInt* num2){
    if(num1->SIZE != num2->SIZE)
        return false;

    for(unsigned int i = 0;i<num1->SIZE;i++){
        if(num1->num[i] != num2->num[i])
            return false;
    }
    return true;

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
    return num1;//когда размеры равны
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
    return num1;//когда размеры равны
}


void BigInt_display(const BigInt* num){

    if(num->positive == false)
        printf("-");
    for (int i = 0;i<num->SIZE;i++)
        printf("%c",num->num[i]);
    printf("\nSIZE : %d\n",num->SIZE);
}

int* resize(int* int_res,unsigned int size){
    int* new_res = malloc(sizeof(int) *(size));
    for(int i = 0; i< size;i++)
        new_res[i] = int_res[i];

    return new_res;
}

BigInt* cut(BigInt* main_num,unsigned int inx_l,unsigned int inx_r){
    unsigned int size = inx_r - inx_l;
    BigInt* new_num = malloc(sizeof(BigInt));
    new_num->num = malloc(sizeof(char)*(size+1));
    new_num->SIZE = size + 1;
    new_num->positive = true;

    for(int i = 0;i<size+1;i++)
        new_num->num[i] = '0';

    int j =0;
    for(int i = inx_l;i<=inx_r;i++){
        new_num->num[j] = '0';
        new_num->num[j]=main_num->num[i];
        j++;
    }


    return new_num;
}

bool BigInt_greater_equal(const BigInt* num1,const BigInt* num2){
    if(num1->positive==false && num2->positive==true)
        return false;
    if(num1->positive==true && num2->positive==false)
        return true;

    if(num1->SIZE==num2->SIZE){
        for(int i =0;i<num1->SIZE;i++) {
            if (num1->num[i] - '0' > num2->num[i] - '0') {
                return num1->positive == false?false:true;
            }
            if (num1->num[i] - '0' < num2->num[i] - '0') {
                return num1->positive == false?true:false;
            }
        }
        return true;
    }

    return num1->SIZE>num2->SIZE? (num1->positive == false?false:true) : (num1->positive == false?true:false);
}

BigInt* BigInt_copy(const BigInt* num1){
    BigInt* copy = malloc(sizeof (BigInt));
    copy->num = malloc(sizeof(char)*num1->SIZE);
    copy->SIZE = num1->SIZE;
    copy->positive = num1->positive;
        for(int i = 0;i<num1->SIZE;i++){
            copy->num[i] = num1->num[i];
        }
    return copy;
}

BigInt* BigInt_copy_int(int i_num){
    BigInt* copy = malloc(sizeof (BigInt));
    copy->SIZE =1;
    copy->num = malloc(sizeof (char));
    copy->num[0] = i_num + '0';
    copy->positive = true;

    return copy;
}