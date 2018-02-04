/* ISC license. */

#include <string.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

static char const *getvar (char const *s, size_t len, char const *var)
{
  size_t varlen = strlen(var) ;
  size_t i = 0 ;
  while (i < len)
  {
    if (!strncmp(var, s + i, varlen) && s[i + varlen] == '=') break ;
    i += strlen(s + i) + 1 ;
  }
  return i < len ? s + i + varlen + 1 : 0 ;
}

char const *pam_getenv (pam_handle_t *pamh, char const *name)
{
  stralloc *sa ;
  if (!pamh) return 0 ;
  sa = &pamh->item[PAMELA_ENV] ;
  if (!pamh->flagenvcached)
  {
    sa->len = 0 ;
    if (!pamela_getenvlist(&pamh->handle, sa)) return 0 ;
    pamh->flagenvcached = 1 ;
  }
  return getvar(sa->s, sa->len, name) ;
}
