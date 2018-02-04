/* ISC license. */

#include <stdlib.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

static int pamela_dummy_conv (int num_msg, pamela_pam_message_t const **msg, pamela_pam_response_t **resp, void *aux)
{
  (void)num_msg ;
  (void)msg ;
  (void)resp ;
  (void)aux ;
  return PAMELA_PAM_CONV_ERR ;
}

int pam_start (char const *service_name, char const *user, struct pam_conv const *pam_conversation, pam_handle_t **pamh)
{
  int e ;
  pam_handle_t *a = malloc(sizeof(pam_handle_t)) ;
  if (!a) return PAM_BUF_ERR ;
  a->handle = pamela_zero ;
  a->flagerrcached = a->flagenvcached = 0 ;
  for (unsigned int i = 0 ; i < _PAM_RETURN_VALUES ; i++) a->err[i] = stralloc_zero ;
  for (unsigned int i = 0 ; i < PAM_ITEM_MAX ; i++) a->item[i] = stralloc_zero ;
  e = pamela_startf(&a->handle, service_name, user, pam_conversation && pam_conversation->conv ? (pamela_pam_conv_func_t_ref)pam_conversation->conv : &pamela_dummy_conv, pam_conversation ? pam_conversation->appdata_ptr : 0) ;
  if (e)
  {
    free(a) ;
    return e ;
  }
  *pamh = a ;
  return PAM_SUCCESS ;
}
