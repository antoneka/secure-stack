#include <assert.h>
#include "common.h"
#include "stack_protection.h"
#include "stack.h"

static void appendCanaries(Stack *stk);

static void fillWithPoison(Stack *stk, size_t src, size_t dst);

static void shiftArray(Stack *stk, size_t shift, ShiftDir direction);

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackCtor(Stack *stk, size_t initial_cap, const char *var_name, 
                     const char *file_name, size_t line_num, const char *func_name)
{
  if (stk == nullptr)
    {
      fprintf(stderr, "Stack pointer passed to the constructor is NULL\n");

      return STACK_PTR_IS_NULL;
    }

  if (stk->init_status == CONSTRUCTED)
    {
      return STACK_ALREADY_CONSTRUCTED;
    }
  
  stk->capacity = initial_cap;
  stk->size = 0;

  stk->err_code = 0;

  stk->var = var_name;
  stk->file = file_name;
  stk->line = line_num;
  stk->func = func_name;

  stk->log_output = fopen("stack_log.txt", "a+");

  if (stk->log_output == nullptr)
    {
      stk->err_code = LOGFILE_OPENING_ERROR;

      return LOGFILE_OPENING_ERROR;
    }

  ON_DEBUG
    (
      stk->stack_left_can = CANARY_VALUE;
      stk->stack_right_can = CANARY_VALUE;

      stk->data = (elem_t*)calloc(2 * sizeof(canary_t) + stk->capacity * sizeof(elem_t), sizeof(char));

      if (stk->data == nullptr)
        {
          stk->err_code |= STACK_ALLOCATION_ERROR;

          return STACK_ALLOCATION_ERROR;
        }

      appendCanaries(stk);

      shiftArray(stk, 1, RIGHT_SHIFT);

      fillWithPoison(stk, 0, stk->capacity);
    );

  NO_DEBUG
    (
      stk->data = (elem_t*)calloc(stk->capacity, sizeof(elem_t));

      if (stk->data == nullptr)
        {
          stk->err_code |= STACK_ALLOCATION_ERROR;

          return STACK_ALLOCATION_ERROR;
        }
    );

  stk->init_status = CONSTRUCTED;

  return EXECUTION_SUCCESS;
} 

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackPush(Stack *stk, elem_t value)
{
  STACK_ASSERT(stk);

  if (stk->size == stk->capacity)
    {
      ExecStatus resize_status = stackResize(stk, stk->capacity * RESIZE_COEF);

      if (resize_status != EXECUTION_SUCCESS)
        {
          stk->err_code |= resize_status;

          return resize_status;
        }
    }
  
  stk->data[stk->size++] = value;

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackPop(Stack *stk, elem_t *return_value)
{
  STACK_ASSERT(stk);

  *return_value = stk->data[--stk->size];

  stk->data[stk->size] = POISON_VALUE;

  if (stk->size * RESIZE_COEF < stk->capacity)
    {
      ExecStatus resize_status = stackResize(stk, stk->capacity / RESIZE_COEF);

      if (resize_status != EXECUTION_SUCCESS)
        {
          stk->err_code |= resize_status;

          return resize_status;
        }
    }

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

static void appendCanaries(Stack *stk)
{
  canary_t *canary_left = (canary_t*)stk->data;
  canary_t *canary_right = (canary_t*)((elem_t*)(canary_left + 1) + stk->capacity);

  *canary_left = CANARY_VALUE;
  *canary_right = CANARY_VALUE;
}

//-----------------------------------------------------------------------------------------------------------

static void fillWithPoison(Stack *stk, size_t src, size_t dst)
{
  for (size_t elem_cnt = src; elem_cnt < dst; elem_cnt++) 
    {
      stk->data[elem_cnt] = POISON_VALUE;
    }
}

//-----------------------------------------------------------------------------------------------------------

static void shiftArray(Stack *stk, size_t shift, ShiftDir direction)
{
  canary_t* data_canary_cast = (canary_t*)stk->data;

  if (direction == LEFT_SHIFT)
    {
      data_canary_cast -= shift;
    }
  else if (direction == RIGHT_SHIFT)
    {
      data_canary_cast += shift;
    }

  stk->data = (elem_t*)data_canary_cast;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackResize(Stack *stk, size_t new_capacity)
{
  STACK_ASSERT(stk);

  stk->capacity = new_capacity;

  ON_DEBUG
    (
      shiftArray(stk, 1, LEFT_SHIFT);

      elem_t *data_tmp = (elem_t*)realloc(stk->data, stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t));

      if (data_tmp == nullptr)
        {
          stk->err_code |= STACK_REALLOCATION_ERROR;

          return STACK_REALLOCATION_ERROR;
        }

      stk->data = data_tmp;

      appendCanaries(stk);

      shiftArray(stk, 1, RIGHT_SHIFT);

      fillWithPoison(stk, stk->size, stk->capacity);
    );

  NO_DEBUG
    (
      elem_t *data_tmp = (elem_t*)realloc(stk->data, stk->capacity * sizeof(elem_t));

      if (data_tmp == nullptr)
        {
          stk->err_code |= STACK_REALLOCATION_ERROR;

          return STACK_REALLOCATION_ERROR;
        }

      stk->data = data_tmp;

      fillWithPosion(stk, stk->size, stk->capacity);
    );

  return EXECUTION_SUCCESS;
}

//-----------------------------------------------------------------------------------------------------------

ExecStatus stackDtor(Stack *stk)
{
  STACK_ASSERT(stk);

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

  ON_DEBUG
    (
      stk->stack_left_can = POISON_VALUE;
      stk->stack_right_can = POISON_VALUE;
    );

  if (stk->log_output != nullptr)
    {
      fclose(stk->log_output);
      stk->log_output = nullptr;
    }

  shiftArray(stk, 1, LEFT_SHIFT);

  free(stk->data);
  stk->data = nullptr;

  stk->init_status = DESTRUCTED;

  return EXECUTION_SUCCESS;
}

