#include <stdio.h>
#include "stack.h"
#include "stack_debug.h"
#include <string.h>

int main()
{
  Stack stk = {};


  int creation_status = STACK_CTOR(&stk, 3);

  STACK_DUMP(&stk, nullptr);

//  memset(&stk, 0xcc, sizeof(stk));

  stackPush(&stk, 2);

  STACK_DUMP(&stk, nullptr);

  stackPush(&stk, 5);

  STACK_DUMP(&stk, nullptr);

  stackPush(&stk, 7);

  STACK_DUMP(&stk, nullptr);

  elem_t element = {};

  stackPop(&stk, &element);

  STACK_DUMP(&stk, nullptr);

//  fprintf(stk.log_output, "poped elem = " elem_modifier "\n\n", element);
  
  stackPop(&stk, &element);

  STACK_DUMP(&stk, nullptr);

//  stk.hash = 96;

//  STACK_DUMP(&stk);
  stackPop(&stk, &element);

  STACK_DUMP(&stk, nullptr);

//  STACK_DUMP(&stk);
  stackPop(&stk, &element);

  STACK_DUMP(&stk, nullptr);



  int destruction_status = stackDtor(&stk);

  return 0;
}
