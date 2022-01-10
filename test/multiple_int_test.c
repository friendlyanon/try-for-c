#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <try.h>

int library_function_that_succeeds(void)
{
  return 0;
}

int library_function_with_out_param_that_succeeds(int* out)
{
  *out = 1;
  return 0;
}

int library_function_with_multiple_allocations(void)
TRY_BODY({
  int* allocation1 = malloc(sizeof(int));
  TRY(allocation1 == NULL ? 1 : 0);

  int* allocation2 = malloc(sizeof(int));
  TRY_GOTO(allocation2 == NULL ? 1 : 0, cleanup);

  *allocation1 = 1;
  *allocation2 = 1;

  assert(*allocation1 == *allocation2);

  free(allocation2);

cleanup:
  free(allocation1);
})

int main(void)
{
  TRY(library_function_that_succeeds());

  int value = 0;
  TRY(library_function_with_out_param_that_succeeds(&value));

  assert(value == 1);

  TRY(library_function_with_multiple_allocations());

  return 0;
}
