#include <stdlib.h>
#include <stdio.h>

typedef struct class_BigInt BigInt;

typedef struct event_BigInt{
    void(*on_event)(BigInt* num,...);
}BigInt_event;


