#include "cstack.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define CHECK(derror,dusl,derrortype) (derror)|=((!(dusl))<<(derrortype))

static uint64_t gnu_hash (const void* begin, const size_t len_in_bytes);

int stackNew_ (Stack* stk, const size_t len) {
    srand(time(NULL));

    stk->arr = NULL;

    stk->marker1 = rand();
    stk->marker2 = stk->marker1;

    stk->capacity = 0;
    stk->size = 0;

    stk->errors = 0;

    stk->hash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));
    return stackCtor_(stk, len);
}

///stack push and stack pop

int stackPush_ (Stack* stk, Elem_t newElem) {
    if (stk == NULL) {
        return 1 << NULL_PTR_TO_STACK;
    }

    //////secure
    uint64_t bufhash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));
    CHECK(stk->errors, stk->hash == bufhash, LOSED_DATA);

    CHECK(stk->errors, stk->marker1 == stk->marker2, LOSED_DATA);
    //////unsecure

    if (stk->size < stk->capacity) {
        CHECK(stk->errors,  stk->arr[stk->size] != POISON, LOSED_DATA);

        stk->arr[stk->size++] = newElem;
    } else {
        CHECK(stk->errors,  stk->size > stk->capacity, LOSED_DATA);

        if (stk->capacity == 0) {
            stackCtor_ (stk, 1);
        } else {
            stackCtor_ (stk, 2 * stk->capacity);
        }
        CHECK(stk->errors,  stk->arr[stk->size] != POISON, LOSED_DATA);

        stk->arr[stk->size++] = newElem;
    }

    stk->hash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));

    return stk->errors;
}

int stackPop_ (Stack* stk, Elem_t* pastElem) {
    if (stk == NULL) {
        return 1 << NULL_PTR_TO_STACK;
    }

    //////secure
    uint64_t bufhash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));
    CHECK(stk->errors, stk->hash == bufhash, LOSED_DATA);

    CHECK(stk->errors, stk->marker1 == stk->marker2, LOSED_DATA);
    //////unsecure

    CHECK(stk->errors, !stk->size, STACK_OVERFLOW);
    CHECK(stk->errors, pastElem != NULL, STACK_OVERFLOW);
    
    *pastElem = NAN;

    if (stk->capacity == 0 || stk->size == 0) {
        
    } else if (stk->capacity == 1) {
        *pastElem = stk->arr[--stk->size];
        stk->arr[stk->size] = POISON;

        free(stk->arr);
        stk->capacity = 0;

    } else if (stk->capacity == 2) {
        *pastElem = stk->arr[--stk->size];
        stk->arr[stk->size] = POISON;

        stackCtor_(stk, 1);
    } else if (stk->capacity == 3) {
        *pastElem = stk->arr[--stk->size];
        stk->arr[stk->size] = POISON;
    } else  {
        *pastElem = stk->arr[--stk->size];
        stk->arr[stk->size] = POISON;

        if (stk->size * 4 <= stk->capacity) {
            stk->capacity /= 2;
            stackCtor_(stk, stk->capacity);
        }
    } 

    stk->hash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));

    return stk->errors;
}

int stackCtor_ (Stack* stk, const size_t len) {    
    if (stk == NULL) {
        return 1 << NULL_PTR_TO_STACK;
    }

    //////secure
    uint64_t bufhash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));
    CHECK(stk->errors, stk->hash == bufhash, LOSED_DATA);

    CHECK(stk->errors, stk->marker1 == stk->marker2, LOSED_DATA);
    //////unsecure

    if (stk->arr == NULL) {
        stk->arr = (Elem_t*)malloc(len * sizeof(Elem_t));
        
        CHECK(stk->errors, stk->arr, NULL_PTR_TO_STACK);

        for (size_t i = 0; i < len; i++) {
            stk->arr[i] = POISON;
        }
    } else {
        size_t capacitybuf = stk->capacity;

        stk->arr = (Elem_t*)realloc(stk->arr, len * sizeof(Elem_t));
        CHECK(stk->errors, stk->arr, NULL_PTR_TO_STACK);
        CHECK(stk->errors, stk->size > stk->capacity, STACK_OVERFLOW);

        for(size_t i = capacitybuf; i < len; i++) {
            stk->arr[i] = POISON;
        }
    }

    stk->capacity = len;

    stk->hash = gnu_hash(stk->arr, stk->size * sizeof(Elem_t));


    return stk->errors;
}

int stackPrint_ (const Stack* stk, const char* name) {
    printf("Stack %s[%p]\terrors:%d\n\tsize: %ld\tcapicity: %ld hash: %lu\n", \
                    name, stk, stk->errors, stk->size, stk->capacity, stk->hash);
    printf("\t\tArray[%p]\n", stk->arr);

    for (size_t i = 0; i < stk->capacity; i++) {
        printf("\t\t");

        if (i < stk->size) {
            printf("*");
        } else {
            printf(" ");
        }

        printf("[%ld]\t", i);
        printf(Elem_out, stk->arr[i]);

        if (stk->arr[i] == POISON) {
            printf(" (POISON)");
        }
        printf("\n");
    }

    return stk->errors;
}

static uint64_t gnu_hash (const void* begin, const size_t len_in_bytes) {
    uint64_t hash = 5381;

    for (size_t i = 0; i < len_in_bytes; i++) {
        hash = ((hash << 5) + hash + *((char*)begin + i)) % UINTMAX_MAX;
    }

    return len_in_bytes;
}
