#include <stdio.h>
#include "common.h"
#include "stack.h"
#include "stack_protection.h"

int main()
{
  Stack stk = {};

  int creation_staus = STACK_CTOR(&stk);

  stackPush(&stk, 2);

  stackPush(&stk, 5);

  stackPush(&stk, 7);

  STACK_DUMP(&stk);

  elem_t element;

  stackPop(&stk, &element);
  printf("poped elem = " elem_modifier "\n", element);

  STACK_DUMP(&stk);

  int destruction_status = stackDtor(&stk);

  return 0;
}
