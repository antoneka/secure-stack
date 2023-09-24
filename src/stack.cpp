#include <assert.h>
#include "common.h"
#include "stack.h"

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackCtor(Stack *stk, const char *var_name, const char *file_name, 
                     size_t line_num, const char *func_name)
{
  assert(stk != nullptr);

  if (stk->init_status == CONSTRUCTED)
    {
      return STACK_ALREADY_CONSTRUCTED;
    }
  
  stk->capacity = STANDART_CAPACITY;
  stk->size = 0;

  stk->data = (elem_t*)calloc(stk->capacity, sizeof(elem_t));

  if (stk->data == nullptr)
    {
      return STACK_ALLOCATION_ERROR;
    }

  stk->log_output = fopen("stack_log.txt", "a+");

  if (stk->log_output == nullptr)
    {
      return LOGFILE_OPENING_ERROR;
    }

  stk->var = var_name;
  stk->file = file_name;
  stk->line = line_num;
  stk->func = func_name;

  stk->err_code = 0;
  stk->init_status = CONSTRUCTED;

  return EXECUTION_SUCCESS;
} 

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackPush(Stack *stk, elem_t value)
{
  assert(stk != nullptr);

  if (stk->size == stk->capacity)
    {
      ExecStatus resize_status = stackResize(stk, stk->capacity * RESIZE_COEF);

      if (resize_status != EXECUTION_SUCCESS)
        {
          return resize_status;
        }
    }
  
  stk->data[stk->size++] = value;

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackPop(Stack *stk, elem_t *return_value)
{
  assert(stk != nullptr);

  *return_value = stk->data[--stk->size];

  if (stk->size * MAX_DIFF_COEF < stk->capacity)
    {
      ExecStatus resize_status = stackResize(stk, stk->capacity / RESIZE_COEF);

      if (resize_status != EXECUTION_SUCCESS)
        {
          return resize_status;
        }
    }

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackResize(Stack *stk, size_t new_capacity)
{
  stk->capacity = new_capacity;

  elem_t *data_tmp = (elem_t*)realloc(stk->data, stk->capacity);

  if (data_tmp == nullptr)
    {
      return STACK_REALLOCATION_ERROR;
    }

  stk->data = data_tmp;

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackDtor(Stack *stk)
{
  assert(stk != nullptr);

  if (stk->init_status == DESTRUCTED)
    {
      return STACK_ALREADY_DESTRUCTED;
    }
 
  stk->capacity = 0;
  stk->size = 0;
  stk->err_code = 0;

  stk->var = nullptr;
  stk->file = nullptr;
  stk->line = 0;
  stk->func = nullptr;

  fclose(stk->log_output);
  stk->log_output = nullptr;

  free(stk->data);
  stk->data = nullptr;

  stk->init_status = DESTRUCTED;

  return EXECUTION_SUCCESS;
}

