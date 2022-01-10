#include <assert.h>
#include <try.h>

int pretend_external_function_always_fails(void)
{
  return 1;
}

TRY_ERROR_TYPE try_main(void)
TRY_BODY({
  TRY_GOTO(pretend_external_function_always_fails(), fail);
  assert(!"TryForC: test fail");
  return try_result;

fail:
  while (0);
})

int main(void)
{
  TRY_ERROR_TYPE result = try_main();
  return result == TRY_OK_VALUE ? 1 : 0;
}
