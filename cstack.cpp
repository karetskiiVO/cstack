#include "cstack.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int stackCtor (Stack* stk, const size_t len) {
    int outputStatus = 0;

    if (stk->arr == NULL) {
        stk->arr = (Elem_t*)calloc(len, sizeof(Elem_t));

        if (stk->arr == NULL) {
            outputStatus |= (1 << NOT_ENOUGHT_MEMORY);

            stk->status |= outputStatus;
            return outputStatus;
        }
    }

    if (stk->capacity >= len) {
        stk->status |= outputStatus;
        return outputStatus;
    }

    stk->arr = (Elem_t*)realloc(stk->arr, len * sizeof(Elem_t));
    stk->capacity = len;

    if (stk->arr == NULL) {
        outputStatus |= (1 << NOT_ENOUGHT_MEMORY);
    }

    stk->status |= outputStatus;
    return outputStatus;
}

int stackPush (Stack* stk, const Elem_t in) {
    int outputStatus = 0;

    if (stk == NULL) {
        outputStatus |= NULL_PTR_TO_STACK;
        assert(!outputStatus && "pointers mustn't bu NULL");
        return outputStatus;
    }

    /*if (stk->size + 1 > stk->capacity) {
        outputStatus |= (1 << STACK_OVERFLOW);
        stk->status |= outputStatus;

        return outputStatus;
    }*/

    if (stk->size == stk->capacity) {
        stackCtor(stk, 2 * stk->capacity + 1);
        stk->capacity = 2 * stk->capacity + 1;
    }

    stk->arr[stk->size++] = in;

    return outputStatus;
}

int stackPop (Stack* stk, Elem_t* out) {
    int outputStatus = 0;

    if (stk == NULL) {
        outputStatus |= NULL_PTR_TO_STACK;
        assert(!outputStatus && "pointers mustn't bu NULL");
        return outputStatus;
    }

    if (stk->size == 0) {
        outputStatus |= (1 << ELEMENT_ISNT_EXIST);
        stk->status |= outputStatus;
        return outputStatus;
    }

    *out = stk->arr[--stk->size];

    if (stk->size + 1 > stk->capacity) {
        outputStatus |= (1 << STACK_OVERFLOW);
        stk->status |= outputStatus;

        return outputStatus;
    }

    if (stk->size <= ((stk->capacity - 1) / 2 - 1) / 2) {
        outputStatus |= stackCtor(stk, (stk->capacity - 1) / 2);
    }

    return outputStatus;
}

int stackNew (Stack* stk, const size_t len) {
    stk->capacity = 0;
    stk->size     = 0;
    stk->status   = 0;

    stk->arr = NULL;

    if (len == 0) {
        return 0;
    }

    return stackCtor(stk, len);
}

int stackPrt (const Stack* stk) {
    int outputStatus = 0;

    if (stk == NULL) {
        outputStatus |= NULL_PTR_TO_STACK;
        assert(!outputStatus && "pointers mustn't bu NULL");
    }

    printf("Stack[%p]\n\tsize:%ld\tcapacity:%ld\tstatus:%d\n", stk, stk->size, stk->capacity, stk->status);
    for (size_t i = 0; i < stk->capacity; i++) {
        if (i < stk->size) {
            printf("\t\t*[%ld]\t= %d\n", i, stk->arr[i]);
        } else {
            printf("\t\t [%ld]\t= %d\n", i, stk->arr[i]);
        }
    }

    return outputStatus;
}



int errorLog (const int line, const char* function, const char* file, const char* logfile) {
    if (logfile == 0) {
        printf("Error in %d  in %s in %s\n", line, function, file);
        return 0;
    }
    FILE* fout = fopen(logfile, "a");

    fprintf(fout, "Error in %d in %s in %s\n", line, function, file);
    fclose(fout);

    return 0;
}




