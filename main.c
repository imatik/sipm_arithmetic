#include <stdio.h>
#include <sys/time.h>
#include <locale.h>
#include "BigInt_class.h"

struct event_BigInt listner;// callback функция, для здесь и сейчас




int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    struct timeval start,end_read, end;
    long cpu_time_used;

    char* name_f1 = "num1.txt";
    char* name_f2 = "num2.txt";
    char* res = "result.txt";

    gettimeofday(&start, NULL);

    BigInt* num1 = create_bigint(name_f1);
    BigInt_set_listner(num1,&listner);

    gettimeofday(&end_read, NULL);

    printf("%b", is_prime(num1));

    gettimeofday(&end, NULL);

    cpu_time_used = (end_read.tv_sec - start.tv_sec) * 1000000 + (end_read.tv_usec - start.tv_usec);
    printf("Время подкрузки файла : %d секунд\n",cpu_time_used);
    cpu_time_used = (end.tv_sec - end_read.tv_sec) * 1000000 + (end.tv_usec - end_read.tv_usec);
    printf("Время проверки : %d секунд\n",cpu_time_used);
    cpu_time_used = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    printf("Всё время работы : %d секунд\n",cpu_time_used);

/*    BigInt* num2 = create_bigint(name_f2);
    BigInt_set_listner(num2,&listner);

    BigInt *mod = malloc(sizeof (BigInt));
    mod->SIZE = 0;
    mod->num = 0;
    mod->positive = true;

    BigInt* result4 = BigInt_div(num1,num2,mod);
    BigInt_display(result4);
    BigInt_display(mod);

    BigInt* result = BigInt_plus(num1,num2);
    BigInt_display(result);

    BigInt* result2 = BigInt_subtr(num1,num2);
    BigInt_display(result2);

    BigInt* result3 = BigInt_multiplication(num1,num2);
    BigInt_display(result3);*/




    return 0;
}
