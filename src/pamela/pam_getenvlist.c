/* ISC license. */

#include <string.h>
#include <stdlib.h>
#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

char **pam_getenvlist (pam_handle_t *pamh)
{
  stralloc *sa ;
  char **arr ;
  char *p ;
  size_t n ;
  size_t i = 0 ;
  if (!pamh) return 0 ;
  sa = &pamh->item[PAMELA_ENV] ;
  if (!pamh->flagenvcached)
  {
    sa->len = 0 ;
    if (!pamela_getenvlist(&pamh->handle, sa)) return 0 ;
    pamh->flagenvcached = 1 ;
  }
  n = byte_count(sa->s, sa->len, 0) ;
  arr = malloc((n+1) * sizeof(char *)) ;
  if (!arr) return 0 ;
  p = sa->s ;
  for (; i < n ; i++)
  {
    arr[i] = strdup(p) ;
    if (!arr[i]) goto err ;
    p += strlen(p) + 1 ;
  }
  arr[n] = 0 ;
  return arr ;

 err:
  while (i--) free(arr[i]) ;
  free(arr) ;
  return 0 ;
}
