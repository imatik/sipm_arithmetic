#include <stdio.h>
#include "BigInt_class.h"

struct event_BigInt listner;// callback функция, для здесь и сейчас




int main() {
    char* name_f1 = "/home/ilya/CLionProjects/Simple_arithmetic/num1.txt";

    BigInt* num = create_bigint(name_f1);
    BigInt_set_listner(num,&listner);




    return 0;
}
