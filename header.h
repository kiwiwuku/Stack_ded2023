#ifndef HEADER_H
#define HEADER_H

#define STACK_CTOR(stk) stack_ctor(stk, #stk, __LINE__, __FILE__, __func__);
#define STACK_DUMP(stk) stack_dump(stk, #stk, __LINE__, __FILE__, __func__);
#define STACK_VERIF(stk) stack_verif(stk, #stk, __LINE__, __FILE__, __func__);
#define CHECK_ERR(stk, err) if (stk->status & err) printf(#err "\n");

#define EMPTY_ELEM 0
#define CANARY_VALUE 999999
#define ELEM_F "%d"
#define CANARY_F "%lld"
typedef int elem_t;
typedef long long int canary_t;

enum Stack_Errors{
    OK                  = 0,
    STACK_NULLPTR       = 1 << 1,
    DATA_NULLPTR        = 1 << 2,
    NEGATIVE_CAP        = 1 << 3,
    NEGATIVE_SIZE       = 1 << 4,
    SIZE_GREATER_CAP    = 1 << 5,
    NULL_FILE           = 1 << 6,
    NULL_LINE           = 1 << 7,
    NULL_FUNC           = 1 << 8,
    NULL_NAME           = 1 << 9,
    IMPOSSIBLE_ACTION   = 1 << 10,
    LEFT_DATA_CANARY    = 1 << 11,
    RIGHT_DATA_CANARY   = 1 << 12,
    LEFT_STRUCT_CANARY  = 1 << 13,
    RIGHT_STRUCT_CANARY = 1 << 14,
    WRONG_HASH          = 1 << 15
};

struct Stack{
    canary_t left_canary;
    const char* name;
    elem_t* data;
    int cur_size;
    int capacity;
    int line;
    const char* file;
    const char* func;
    int status;
    long long unsigned int hashsum;
    canary_t right_canary;
};

Stack_Errors stack_ctor(Stack* stk, const char* name, int line, const char* file, const char* func);
Stack_Errors stack_dtor(Stack* stk);
Stack_Errors stack_realloc_increase(Stack* stk);
Stack_Errors stack_realloc_decrease(Stack* stk);
Stack_Errors stack_realloc_nullify(Stack* stk);
Stack_Errors push(Stack* stk, elem_t value);
elem_t pop(Stack* stk);
Stack_Errors stack_verif(Stack* stk, const char* name, int line, const char* file, const char* func);

long long unsigned int get_hash(char* str, long long unsigned int len);
long long unsigned int stack_get_hash(Stack* stk);
Stack_Errors stack_hash_update(Stack* stk);

canary_t* stack_get_left_canary(Stack* stk);
canary_t* stack_get_right_canary(Stack* stk);

Stack_Errors stack_set_data_canaries(Stack* stk);
void stack_check_status(Stack* stk, const char* name, int line, const char* file, const char* func);
Stack_Errors stack_dump(Stack* stk, const char* name, int line, const char* file, const char* func);
Stack_Errors stack_print(Stack* stk);
int max_int(int a, int b);

#endif // HEADER_H
