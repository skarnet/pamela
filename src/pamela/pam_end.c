/* ISC license. */

#include <stdlib.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

int pam_end (pam_handle_t *pamh, int pam_status)
{
  if (!pamh) return PAM_SYSTEM_ERR ;
  pamela_op(&pamh->handle, PAMELA_OP_END, pam_status) ;
  pamela_end(&pamh->handle) ;
  for (unsigned int i = 0 ; i < _PAM_RETURN_VALUES ; i++) stralloc_free(&pamh->err[i]) ;
  for (unsigned int i = 0 ; i < PAM_ITEM_MAX ; i++) stralloc_free(&pamh->item[i]) ;
  free(pamh) ;
  return PAM_SUCCESS ;
}
