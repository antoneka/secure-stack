#ifndef COMMON_H
#define COMMON_H

enum ExecStatus
{
  EXECUTION_SUCCESS         = 1,
  STACK_ALLOCATION_ERROR    = 2,
  STACK_REALLOCATION_ERROR  = 3,
  LOGFILE_OPENING_ERROR     = 4,
  STACK_ALREADY_CONSTRUCTED = 5,
  STACK_ALREADY_DESTRUCTED  = 6,
};

/*
enum InitStatus
{
  CONSTRUCTED = 1,
  DESTRUCTED  = 2,
};
*/

#endif // COMMON_H