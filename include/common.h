#ifndef COMMON_H
#define COMMON_H

enum StackError
{
};

enum ExecStatus
{
  EXECUTION_SUCCESS            = 1 << 0,
  STACK_ALLOCATION_ERROR       = 1 << 1,
  STACK_CAPACITY_ERROR         = 1 << 2,
  STACK_SIZE_ERROR             = 1 << 3,
  LEFT_CANARY_STACK_CORRUPTED  = 1 << 4,
  RIGHT_CANARY_STACK_CORRUPTED = 1 << 5,
  LEFT_CANARY_DATA_CORRUPTED   = 1 << 6,
  RIGHT_CANARY_DATA_CORRUPTED  = 1 << 7,
  STACK_REALLOCATION_ERROR     = 1 << 8,
  LOGFILE_OPENING_ERROR        = 1 << 9,
  STACK_ALREADY_CONSTRUCTED    = 1 << 10,
  STACK_ALREADY_DESTRUCTED     = 1 << 11,
  STACK_PTR_IS_NULL            = 1 << 12,
};

enum StackStatus
{
  CONSTRUCTED = 1,
  DESTRUCTED  = 2,
};

enum ShiftDir
{
  LEFT_SHIFT  = 1,
  RIGHT_SHIFT = 2,
};

#endif // COMMON_H
