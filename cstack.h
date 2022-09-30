#ifndef CSTACK
#define CSTACK

#include <stdio.h>
#include <math.h>
#include <stdint.h>

extern const char* logout;

enum ERRORS_ {
    NOT_ENOUGHT_MEMORY = 0,
    STACK_OVERFLOW     = 1,
    ELEMENT_ISNT_EXIST = 2,
    NULL_PTR_TO_STACK  = 3,
    LOSED_DATA         = 4,
    STRANGE_DATA       = 5
};

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

int stackCtor_ (Stack* stk, const size_t len);

int stackNew_ (Stack* stk, const size_t len);

int stackPush_ (Stack* stk, Elem_t newElem);

int stackPop_ (Stack* stk, Elem_t* pastElem);

int stackPrint_ (const Stack* stk, const char* name);

int stackDump_ (const Stack* stk, const char* stkname, const char* file, const char* funct, const int line);




#define Log_init(filename) const char* logout = (filename)

#define stackDump(stk) stackDump_(&(stk), #stk, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#define errdump(stream, err, typeoferr) fprintf(stream, #typeoferr);                \
fprintf(stream, "\t\t%s\n", ((err >> typeoferr) & 1)?("ATTENTION!!!!"):("[  OK  ]"))

#define stackCtor(stk, len) stackCtor_(&(stk), (len)) && stackDump(stk)
#define stackNew(stk, len)  stackNew_ (&(stk), (len)) && stackDump(stk)
#define stackPush(stk, val) stackPush_(&(stk), (val)) && stackDump(stk)
#define stackPop(stk, val)  stackPop_ (&(stk), &(val))&& stackDump(stk)
#define stackPrint(stk) stackPrint_(&(stk), #stk) || stackDump(stk)

#endif