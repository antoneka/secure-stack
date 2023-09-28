#include "stack_debug.h"
#include "stack_hash.h"
#include <stdint.h>

void stackDump(Stack *stk, const char *file_name, size_t line_num, const char *func_name)
{
  if (stk == nullptr)
    {
      return;
    }

  FILE *log_file = stk->log_output == nullptr ? stderr : stk->log_output;

  fprintf(log_file, "Stack [%p] %s from %s(%zu) %s() called from %s(%zu) %s()\n",
                     stk, stk->var, stk->file, stk->line, stk->func, file_name, line_num, func_name);

  fprintf(log_file, "{\n"
                    "\tsize = %zu\n"
                    "\tcapacity = %zu\n"
                    "\tdata[%p]\n"
                    "\t{\n", stk->size, stk->capacity, stk->data);

  for (size_t stk_elem = 0; stk_elem < stk->capacity; stk_elem++)
    {
      if (stk_elem < stk->size)
        {
          fprintf(log_file, "\t\t*[%zu] = " ELEM_MODIFIER "\n", stk_elem, stk->data[stk_elem]);
        }
      else 
        {
          fprintf(log_file, "\t\t [%zu] = " ELEM_MODIFIER "\n", stk_elem, stk->data[stk_elem]);
        } 
    }
  
  fprintf(log_file, "\t}\n"
                    "}\n\n");

  fprintf(log_file, "============================================================================\n\n");
}

//-----------------------------------------------------------------------------------------------------------

int stackCheck(Stack *stk)
{
  if (stk == nullptr)
    {
      return STACK_PTR_IS_NULL;
    }

  if (stk->log_output == nullptr)
    {
      stk->err_code |= LOGFILE_OPENING_ERROR;
    }

  if (stk->data == nullptr)
    {
      stk->err_code |= STACK_ALLOCATION_ERROR;
    }

  if (stk->capacity == SIZE_MAX)
    {
      stk->err_code |= STACK_CAPACITY_ERROR;
    }

  if (stk->size == SIZE_MAX || stk->size > stk->capacity)
    {
      stk->err_code |= STACK_SIZE_ERROR;
    }

  ON_DEBUG
    (
      if (stk->stack_left_can != CANARY_VALUE)
        {
          stk->err_code |= LEFT_CANARY_STACK_CORRUPTED;
        }

      if (stk->stack_right_can != CANARY_VALUE)
        {
          stk->err_code |= RIGHT_CANARY_STACK_CORRUPTED;
        }

      if (stk->data != nullptr && *((canary_t*)stk->data - 1) != CANARY_VALUE)
        {
          stk->err_code |= LEFT_CANARY_DATA_CORRUPTED;
        }

      if (stk->data != nullptr && *(canary_t*)(stk->data + stk->capacity) != CANARY_VALUE)
        {
          stk->err_code |= RIGHT_CANARY_DATA_CORRUPTED;
        }

      unsigned int correct_hash = hashCalc(stk);

      if (correct_hash != stk->hash)
        {
          stk->err_code |= HASH_CORRUPTED;
        }
    )

  return stk->err_code;
}

//-----------------------------------------------------------------------------------------------------------

void printErrors(Stack *stk, const char *file_name, size_t line_num, const char *func_name)
{
  if (stk == nullptr)
    {
      fprintf(stderr, "Stack pointer passed to the function %s():%zu from %s is NULL\n",
                       func_name, line_num, file_name);

      return;
    }

  int errors = stk->err_code;
  FILE *log_file = stk->log_output == nullptr ? stderr : stk->log_output;

  if (errors & LOGFILE_OPENING_ERROR)
    {
      fprintf(log_file, "Failed to open a log file\n");

      return;
    }

  if (errors & STACK_ALLOCATION_ERROR)
    {
      fprintf(log_file, "Failed to allocate memory for the data array\n");
    }

  if (errors & STACK_REALLOCATION_ERROR)
    {
      fprintf(log_file, "Failed to resize the data array\n");
    }

  if (errors & STACK_CAPACITY_ERROR)
    {
      fprintf(log_file, "Invalid capacity value\n");
    }

  if (errors & STACK_SIZE_ERROR)
    {
      fprintf(log_file, "Invalid size value\n");
    }

  if (errors & LEFT_CANARY_STACK_CORRUPTED)
    {
      fprintf(log_file, "Left canary of the stack is corrupted\n");
    }

  if (errors & RIGHT_CANARY_STACK_CORRUPTED)
    {
      fprintf(log_file, "Right canary of the stack is corrupted\n");
    }

  if (errors & LEFT_CANARY_DATA_CORRUPTED)
    {
      fprintf(log_file, "Left canary of the data array is corrupted\n");
    }

  if (errors & RIGHT_CANARY_DATA_CORRUPTED)
    {
      fprintf(log_file, "Right canary of the data array is corrupted\n");
    }

  if (errors & HASH_CORRUPTED)
    {
      fprintf(log_file, "The hash was corrupted\n");
    }
}

