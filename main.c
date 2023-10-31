#include <stdio.h>
#include "class.h"

struct event_BigInt listner;

void eawe(BigInt* num){
    printf("%s","e3awe\n");
}


int main() {
    char* name_f1 = "num1.txt";
    FILE *file1 = fopen(name_f1,"r");

    BigInt* num = create_bigint();

    BigInt_set_listner(num,&listner);

    num->listner->on_event = eawe;
    num->listner->on_event(num);

    return 0;
}
