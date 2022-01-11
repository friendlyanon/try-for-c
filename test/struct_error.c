#include <struct_error.h>

struct error const error_ok = {0};

int error_is_ok(struct error error)
{
  return error.value == 0;
}
