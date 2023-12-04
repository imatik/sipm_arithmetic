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

    BigInt *mod = malloc(sizeof (BigInt));
    mod->SIZE = 0;
    mod->num = 0;
    mod->positive = true;


    BigInt* a = BigInt_rand(20);
    BigInt_display(a);
    printf("%b\n",is_prime(a));



/*    BigInt* result4 = BigInt_div(num1,num2,mod);
    BigInt_display(result4);
    BigInt_display(mod);*/

/*    BigInt* result = BigInt_plus(num1,num2);
    BigInt_display(result);

    BigInt* result2 = BigInt_subtr(num1,num2);
    BigInt_display(result2);

    BigInt* result3 = BigInt_multiplication(num1,num2);
    BigInt_display(result3);*/

    return 0;
}
