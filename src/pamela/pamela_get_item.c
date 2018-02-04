/* ISC license. */

#include <pamela/pamela.h>
#include "pamela-internal.h"

int pamela_get_item (pamela_t *a, unsigned char what, stralloc *sa)
{
  char s[2] = "G" ;
  s[1] = what ;
  return pamela_query_string(a, s, 2, sa) ;
}
