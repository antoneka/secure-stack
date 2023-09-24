#ifndef STACK_H
#define STACK_H

#include "common.h"
#include <stdio.h>

//-----------------------------------------------------------------------------------------------------------

#define STACK_CTOR(stk) stackCtor((stk), #stk, __FILE__, __LINE__, __func__)

//-----------------------------------------------------------------------------------------------------------

typedef int elem_t;

const size_t STANDART_CAPACITY = 15;
const size_t RESIZE_COEF       =  2;
const size_t MAX_DIFF_COEF     =  3;

const int CONSTRUCTED          =  1;
const int DESTRUCTED           =  2;

struct Stack
{
  int init_status;
  
  size_t capacity; 
  size_t size;
  elem_t *data;

  const char *var;
  const char *file; 
  size_t line; 
  const char *func;

  FILE *log_output;

  int err_code;

  long long hash;
};

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackCtor(Stack *stk, const char *var_name, const char *file_name, 
                     size_t line_num, const char *func_name);

ExecStatus stackPush(Stack *stk, elem_t value);

ExecStatus stackPop(Stack *stk, elem_t *return_value);

ExecStatus stackResize(Stack *stk, size_t new_capacity);

ExecStatus stackDtor(Stack *stk);

#endif // STACK_H
