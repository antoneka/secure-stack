#ifndef STACK_HASH_H
#define STACK_HASH_H

#include <stdio.h>
#include "stack.h"

unsigned int hashFunc(const char * arr, const size_t nbytes);

unsigned int hashCalc(Stack *stk);

#endif
