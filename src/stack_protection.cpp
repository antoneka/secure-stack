#include "stack_protection.h"


void stackDump(Stack *stk, const char *file_name, size_t line_num, const char *func_name)
{
  FILE *output = stk->log_output;

  fprintf(output, "Stack [%p] %s from %s(%zu) %s() called from %s(%zu) %s()\n",
                   stk, stk->var, stk->file, stk->line, stk->func, file_name, line_num, func_name);

  fprintf(output, "{\n"
                  "\tsize = %zu\n"
                  "\tcapacity = %zu\n"
                  "\tdata[%p]\n"
                  "\t{\n", stk->size, stk->capacity, stk->data);

  for (size_t stk_elem = 0; stk_elem < stk->capacity; stk_elem++)
    {
      if (stk_elem < stk->size)
        {
          fprintf(output, "\t\t*[%zu] = " elem_modifier "\n", stk_elem, stk->data[stk_elem]);
        }
      else 
        {
          fprintf(output, "\t\t [%zu] = " elem_modifier "\n", stk_elem, stk->data[stk_elem]);
        } 
    }
  
  fprintf(output, "\t}\n"
                  "}\n\n");
}
