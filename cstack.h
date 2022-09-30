#ifndef CSTACK
#define CSTACK

#include <stdio.h>
#include <math.h>
#include <stdint.h>

extern const char* logout;

//add extern

typedef double Elem_t;
#define Elem_out "%lf"
#define POISON (Elem_t)INFINITY

typedef struct {
    uint64_t marker1;
    size_t size;
    int errors; 
    size_t capacity;
    uint64_t marker2;
    Elem_t* arr;
    uint64_t hash; 
} Stack;

enum ERRORS_ {
    NOT_ENOUGHT_MEMORY = 0,
    STACK_OVERFLOW     = 1,
    ELEMENT_ISNT_EXIST = 2,
    NULL_PTR_TO_STACK  = 3,
    LOSED_DATA         = 4,
    STRANGE_DATA       = 5
};

int stackCtor_ (Stack* stk, const size_t len);

int stackNew_ (Stack* stk, const size_t len);

int stackPush_ (Stack* stk, Elem_t newElem);

int stackPop_ (Stack* stk, Elem_t* pastElem);

int stackPrint_ (const Stack* stk, const char* name);



#endif