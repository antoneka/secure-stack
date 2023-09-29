#include "stack_hash.h"
#include "stack.h"

// rot15_hash
unsigned int hashFunc(const char * arr, const size_t nbytes)
{
  unsigned int hash = 0;

  for(size_t byte_cnt = 0; byte_cnt < nbytes; byte_cnt++)
    {
      hash += (unsigned char)arr[byte_cnt];
      hash -= (hash << 13) | (hash >> 19);
    }

  return hash;
}

// stack.cpp
unsigned int hashCalc(Stack *stk)
{
  unsigned int old_hash = stk->hash;
  unsigned int new_hash = 0;

  stk->hash = 0;

  new_hash = hashFunc((char*)stk, sizeof(*stk));

  new_hash += hashFunc((char*)((canary_t*)stk->data - 1), 
                       stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t));

  stk->hash = old_hash;

  return new_hash;
}
