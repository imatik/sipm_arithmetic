#include <stdio.h>
#include "BigInt_class.h"

struct event_BigInt listner;// callback функция, для здесь и сейчас




int main() {
    char* name_f1 = "num1.txt";

    BigInt* num = create_bigint(name_f1);
    BigInt_set_listner(num,&listner);
    int* numer = BigInt_char_to_int(num);
    for (int i=0;i<num->SIZE;i++)
        printf("%u%c",numer[i],' ');
    BigInt_int_to_char(numer,num);
    return 0;
}
