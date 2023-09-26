#ifndef STACK_PROTECTION_H
#define STACK_PROTECTION_H

#include "stack.h"

//-----------------------------------------------------------------------------------------------------------

#define elem_modifier "%d"

#define STACK_DUMP(stk) stackDump(stk, __FILE__, __LINE__, __func__)
#define PRINT_ERRORS(stk) printErrors(stk, __FILE__, __LINE__, __func__)

#define STACK_ASSERT(stk)                             \
  do                                                  \
    {                                                 \
      int check_status = stackCheck(stk);             \
                                                      \
      if (check_status != 0)                          \
        {                                             \
          STACK_DUMP(stk);                            \
          PRINT_ERRORS(stk);                          \
                                                      \
          if (check_status != STACK_PTR_IS_NULL)      \
            {                                         \
              stackDtor(stk);                         \
            }                                         \
                                                      \
          exit(EXIT_FAILURE);                         \
        }                                             \
                                                      \
    } while(0)                                        

//-----------------------------------------------------------------------------------------------------------

const canary_t CANARY_VALUE = 0xBADC0FFEE;

void stackDump(Stack *stk, const char *file_name, size_t line_num, const char *func_name);

int stackCheck(Stack *stk);

void printErrors(Stack *stk, const char *file_name, size_t line_num, const char *func_name);

#endif // STACK_PROTECTION_H
