#include <stdio.h>
#include "common.h"
#include "stack.h"
#include "stack_protection.h"

int main()
{
  Stack stk = {};

  int creation_status = STACK_CTOR(nullptr, 2);

  /*
  stackPush(&stk, 2);

  stackPush(&stk, 5);

  STACK_DUMP(&stk);

  stackPush(&stk, 7);

  STACK_DUMP(&stk);

  elem_t element;

  stackPop(&stk, &element);

  fprintf(stk.log_output, "poped elem = " elem_modifier "\n\n", element);
  

  STACK_DUMP(&stk);
  */

  int destruction_status = stackDtor(&stk);

  return 0;
}
