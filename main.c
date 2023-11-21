#include <stdio.h>
#include "BigInt_class.h"

struct event_BigInt listner;// callback функция, для здесь и сейчас




int main() {
    char* name_f1 = "num1.txt";
    char* name_f2 = "num2.txt";
    char* res = "result.txt";

    BigInt* num1 = create_bigint(name_f1);
    BigInt_set_listner(num1,&listner);



    BigInt* num2 = create_bigint(name_f2);
    BigInt_set_listner(num2,&listner);

    //printf("%b", BigInt_max(num1,num2));

/*    BigInt* result = BigInt_plus(num1,num2);
    BigInt_display(result);*/

/*
    BigInt* result2 = BigInt_subtr(num1,num2);
    BigInt_display(result2);
*/

//    BigInt* result3 = BigInt_subtr(num1,num2);
    BigInt* result3 = BigInt_multiplication(num1,num2);
    BigInt_display(result3);
    return 0;
}
