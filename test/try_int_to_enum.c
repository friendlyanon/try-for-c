#include <try.h>

TRY_ERROR_TYPE try_int_to_enum(int error)
{
  return error == 0 ? TRY_OK_VALUE : ERROR_FAIL;
}
