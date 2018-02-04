/* ISC license. */

#include <pamela/pamela.h>
#include "pamela-internal.h"

int pamela_strerror (pamela_t *a, unsigned char e, stralloc *sa)
{
  char s[2] = "E" ;
  s[1] = e ;
  return pamela_query_string(a, s, 2, sa) ;
}
