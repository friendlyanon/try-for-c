#include <assert.h>
#include <try.h>

TRY_ERROR_TYPE library_function_that_fails_with_3(void)
{
  TRY_ERROR_TYPE result = {3};
  return result;
}

TRY_ERROR_TYPE try_main(void)
{
  TRY(library_function_that_fails_with_3());
  assert(!"TryForC: test fail");
  return TRY_OK_VALUE;
}

int main(void)
{
  TRY_ERROR_TYPE result = try_main();
  return error_is_ok(result) ? 1 : 0;
}
