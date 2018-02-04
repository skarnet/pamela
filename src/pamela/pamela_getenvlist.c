/* ISC license. */

#include <pamela/pamela.h>
#include "pamela-internal.h"

int pamela_getenvlist (pamela_t *a, stralloc *sa)
{
  return pamela_query_string(a, "V", 1, sa) ;
}
