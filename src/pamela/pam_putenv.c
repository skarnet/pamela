/* ISC license. */

#include <pamela/pamela.h>
#include <pamela/pam.h>

int pam_putenv (pam_handle_t *pamh, char const *name_value)
{
  int e ;
  if (!pamh) return PAM_SYSTEM_ERR ;
  e = pamela_set_item(&pamh->handle, PAMELA_ENV, name_value) ;
  if (e) return e ;
  pamh->flagenvcached = 0 ;
  return PAM_SUCCESS ;
}
