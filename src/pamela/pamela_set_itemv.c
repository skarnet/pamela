/* ISC license. */

#include <sys/uio.h>
#include <pamela/pamela.h>
#include "pamela-internal.h"

int pamela_set_itemv (pamela_t *a, unsigned char type, struct iovec const *v, unsigned int n)
{
  struct iovec vv[n+2] ;
  vv[0].iov_base = "S" ; vv[0].iov_len = 1 ;
  vv[1].iov_base = &type ; vv[1].iov_len = 1 ;
  for (unsigned int i = 0 ; i < n ; i++) vv[i+2] = v[i] ;
  return pamela_set_item_internal(a, vv, n+2) ;
}
