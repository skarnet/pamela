/* ISC license. */

#include <string.h>
#include <pamela/pamela.h>
#include "pamela-internal.h"

int pamela_set_item (pamela_t *a, unsigned char type, char const *s)
{
  struct iovec const v[3] =
  {
    { .iov_base = "S", .iov_len = 1 },
    { .iov_base = &type, .iov_len = 1 },
    { .iov_base = (char *)s, .iov_len = strlen(s) + 1 }
  } ;
  return pamela_set_item_internal(a, v, 3) ;
}
