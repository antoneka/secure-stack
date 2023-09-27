#include <stdio.h>
#include "stack.h"
#include "stack_debug.h"

int main()
{
  Stack stk = {};

  int creation_status = STACK_CTOR(&stk, 2);

  stackPush(&stk, 2);

  stackPush(&stk, 5);

//  STACK_DUMP(&stk);

  stackPush(&stk, 7);

 // STACK_DUMP(&stk);

  elem_t element;

  stackPop(&stk, &element);

//  fprintf(stk.log_output, "poped elem = " elem_modifier "\n\n", element);
  
  stackPop(&stk, &element);

//  STACK_DUMP(&stk);
  stackPop(&stk, &element);

//  STACK_DUMP(&stk);
  stackPop(&stk, &element);

  stackPop(&stk, &element);


  int destruction_status = stackDtor(&stk);

  return 0;
}
