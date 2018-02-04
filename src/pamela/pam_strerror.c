/* ISC license. */

#include <pamela/pamela.h>
#include <pamela/pam.h>

char const *pam_strerror (pam_handle_t *pamh, int errnum)
{
  if (errnum < 0 || errnum >= _PAM_RETURN_VALUES) return 0 ;
  if (!(pamh->flagerrcached & (1ULL << errnum)))
  {
    pamh->err[errnum].len = 0 ;
    if (!pamela_strerror(&pamh->handle, (unsigned char)errnum, &pamh->err[errnum])) return 0 ;
    if (!stralloc_0(&pamh->err[errnum])) return 0 ;
    pamh->flagerrcached |= (1ULL << errnum) ;
  }
  return (char const *)pamh->err[errnum].s ;
}
