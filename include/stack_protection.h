#ifndef STACK_PROTECTION_H
#define STACK_PROTECTION_H

#include "stack.h"

//-----------------------------------------------------------------------------------------------------------

#define elem_modifier "%d"

#define STACK_DUMP(stk) stackDump(stk, __FILE__, __LINE__, __func__)

//-----------------------------------------------------------------------------------------------------------

const canary_t CANARY_VALUE = 0xBADC0FFEE;

void stackDump(Stack *stk, const char *file_name, size_t line_num, const char *func_name);

#endif // STACK_PROTECTION_H
