/* ISC license. */

#include <stdint.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

int pam_setcred (pam_handle_t *pamh, int flags)
{
  if (!pamh) return PAM_SYSTEM_ERR ;
  return pamela_op(&pamh->handle, PAMELA_OP_SETCRED, flags) ;
}
