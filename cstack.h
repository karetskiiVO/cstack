#ifndef CSTACK
#define CSTACK

#include <stdio.h>

extern const char* logout;

#define Elem_t int

#define CHECK ==0||errorLog(__LINE__,__PRETTY_FUNCTION__,__FILE__,logout)

typedef struct {
    Elem_t* arr     = NULL;
    size_t size     = 0;
    size_t capacity = 0;

    int status = 0;
} Stack;

enum ERRORS_ {
    NOT_ENOUGHT_MEMORY = 0,
    STACK_OVERFLOW     = 1,
    ELEMENT_ISNT_EXIST = 2,
    NULL_PTR_TO_STACK  = 3
};

///////////////////////////

int stackPush (Stack* stk, const Elem_t in);

int stackCtor (Stack* stk, const size_t len);

int stackPop (Stack* stk, Elem_t* out);

int stackNew (Stack* stk, const size_t len);

int stackPrt (const Stack* stk);

int errorLog (const int line, const char* function, const char* file, const char* logfile);

#endif // cstack.h