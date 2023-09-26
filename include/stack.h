#ifndef STACK_H
#define STACK_H

#include "common.h"
#include <stdio.h>

//-----------------------------------------------------------------------------------------------------------

#define STACK_CTOR(stk, capacity) stackCtor((stk), capacity, #stk, __FILE__, __LINE__, __func__)

//-----------------------------------------------------------------------------------------------------------

#define DEBUG

//-----------------------------------------------------------------------------------------------------------

#ifdef DEBUG
#define ON_DEBUG(code, ...) code ##__VA_ARGS__
#else
#define ON_DEBUG(code) 
#endif

#ifndef DEBUG
#define NO_DEBUG(code, ...) code __VA_ARGS__
#else
#define NO_DEBUG(code) 
#endif

//-----------------------------------------------------------------------------------------------------------

typedef int elem_t;
typedef unsigned long long canary_t;

const size_t STANDART_CAPACITY =         15;
const size_t RESIZE_COEF       =          2;
// const size_t MAX_DIFF_COEF     =          3;

const elem_t POISON_VALUE      = 0xDADD0FAC;

struct Stack
{
  ON_DEBUG(
  canary_t stack_left_can;
      );

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

  ON_DEBUG(
  long long hash;
  canary_t stack_right_can;
      );
};

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackCtor(Stack *stk, size_t initial_cap, const char *var_name, 
                     const char *file_name, size_t line_num, const char *func_name);

ExecStatus stackPush(Stack *stk, elem_t value);

ExecStatus stackPop(Stack *stk, elem_t *return_value);

ExecStatus stackResize(Stack *stk, size_t new_capacity);

ExecStatus stackDtor(Stack *stk);

#endif // STACK_H
