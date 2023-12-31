#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "TXLib.h"

#include "header.h"

Stack_Errors stack_realloc_increase(Stack* stk)
{
    STACK_VERIF(stk);
    printf("stack_realloc_increase happening...\n");

    int old_cap = stk->capacity;
    int new_cap = max_int(old_cap*2, 1);

    size_t left = (new_cap*sizeof(elem_t))%sizeof(canary_t);

    while (left != 0)
    {
        new_cap++;
        left = (new_cap*sizeof(elem_t))%sizeof(canary_t);
    }

    stk->capacity = new_cap;

    stk->data = (elem_t*)stack_get_left_canary(stk);
    assert(stk->data);
    stk->data = (elem_t*)realloc(stk->data, 2*sizeof(canary_t) + new_cap*sizeof(elem_t));
    assert(stk->data);
    stk->data = (elem_t*)((char*)stk->data + sizeof(canary_t));
    assert(stk->data);
    stack_set_data_canaries(stk);

    stack_hash_update(stk);

    stack_realloc_nullify(stk);

    stack_hash_update(stk);

    STACK_VERIF(stk);

    printf("stack_realloc_increase happened from %d to %d!\n", old_cap, new_cap);

    return OK;
}

Stack_Errors stack_realloc_decrease(Stack* stk)
{
    STACK_VERIF(stk);

    int old_cap = stk->capacity;
    int new_cap = max_int(old_cap/2, 1);
    size_t left = (new_cap*sizeof(elem_t))%sizeof(canary_t);

    while (left != 0)
    {
        new_cap++;
        left = (new_cap*sizeof(elem_t))%sizeof(canary_t);
    }

    stk->capacity = new_cap;

    stk->data = (elem_t*)stack_get_left_canary(stk);
    assert(stk->data);
    stk->data = (elem_t*)realloc(stk->data, 2*sizeof(canary_t) + new_cap*sizeof(elem_t));
    assert(stk->data);
    stk->data = (elem_t*)((char*)stk->data + sizeof(canary_t));
    assert(stk->data);

    stack_set_data_canaries(stk);

    stack_hash_update(stk);

    STACK_VERIF(stk);

    printf("stack_realloc_decrease happened from %d to %d!\n", old_cap, new_cap);

    return OK;
}

Stack_Errors stack_realloc_nullify(Stack* stk)
{
    STACK_VERIF(stk);

    int start = stk->cur_size;
    int finish = stk->capacity;
    for (int i = start; i < finish; i++)
        stk->data[i] = EMPTY_ELEM;

    stack_hash_update(stk);

    STACK_VERIF(stk);
    return OK;
}

int max_int(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
