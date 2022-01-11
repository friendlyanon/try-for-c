#pragma once

struct error {
  int value;
};

extern struct error const error_ok;

int error_is_ok(struct error error);
