#ifndef CSTACK
#define CSTACK

#define SAVEFLAG 0
#define HASHFLAG 0

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

/**
 * @brief Elem_t   - type of stack elements
 * @brief Elem_out - flag to scanf
 * @brief POISON   - empty element
 */
typedef double Elem_t;
#define Elem_out "%lf"
#define POISON (Elem_t)INFINITY

/**
 * @brief new type of data, whitch include stack
 */
typedef struct {
#if SAVEFLAG
    uint64_t marker1;
#endif
    size_t size;
    int errors; 
    size_t capacity;
#if SAVEFLAG
    uint64_t marker2;
#endif
    Elem_t* arr;
#if HASHFLAG
    uint64_t hash; 
#endif
} Stack;

/**
 * @brief locate memory for stak
 * 
 * @param [in] stk - pointer to stack
 * @param [in] len - how many elements need to locate
 * 
 * @return int - error code
 */
int stackCtor_ (Stack* stk, const size_t len);

/**
 * @brief make empty stack
 * 
 * @param [in] stk - pointer to stack
 * @param [in] len - how many elements need to locate
 * 
 * @return int - error code
 */
int stackNew_ (Stack* stk, const size_t len);

/**
 * @brief add element in stack
 * 
 * @param [in] stk     - pointer to stack
 * @param [in] newElem - element, that needs to add
 * 
 * @return int - error code
 */
int stackPush_ (Stack* stk, Elem_t newElem);

/**
 * @brief add element in stack
 * 
 * @param [in] stk       - pointer to stack
 * @param [out] pastElem - last element in stack
 * 
 * @param int - error code
 */
int stackPop_ (Stack* stk, Elem_t* pastElem);

/**
 * @brief print stack 
 * 
 * @param [in] stk  - pointer to stack
 * @param [in] name - name of stack
 * 
 * @return int - error code
 */
int stackPrint_ (const Stack* stk, const char* name);

/**
 * @brief make dump
 * 
 * @param [in] stk     - pointer to stack
 * @param [in] stkname - name of stack
 * @param [in] file    - file called dump
 * @param [in] funct   - function celled dump
 * @param [in] line    - line called dump
 * 
 * @return int - error code
 */
int stackDump_ (const Stack* stk, const char* stkname, const char* file, const char* funct, const int line);

#define Log_init(filename) const char* logout = (filename)

#define stackDump(stk) stackDump_(&(stk), #stk, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#define errdump(stream, err, typeoferr) fprintf(stream, #typeoferr);                \
fprintf(stream, "\t\t%s\n", ((err >> typeoferr) & 1)?("ATTENTION!!!!"):("[  OK  ]"))

/**
 * @brief use this to call function in svefull mode
 */
#define stackCtor(stk, len) stackCtor_(&(stk), (len)) && stackDump(stk)
#define stackNew(stk, len)  stackNew_ (&(stk), (len)) && stackDump(stk)
#define stackPush(stk, val) stackPush_(&(stk), (val)) && stackDump(stk)
#define stackPop(stk, val)  stackPop_ (&(stk), &(val))&& stackDump(stk)
#define stackPrint(stk) stackPrint_(&(stk), #stk) || stackDump(stk)

#endif