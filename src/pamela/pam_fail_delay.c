/* ISC license. */

#include <stdint.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

int pam_fail_delay (pam_handle_t *pamh, unsigned int usec)
{
  if (!pamh) return PAM_SYSTEM_ERR ;
  return pamela_op(&pamh->handle, PAMELA_OP_FAIL_DELAY, (int)usec) ;
}
