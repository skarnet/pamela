/* ISC license. */

#include <string.h>
#include <stdlib.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/strerr.h>
#include <skalibs/stralloc.h>
#include <pamela/pam.h>
#include <pamela/compat.h>

/*
static void freeres (struct pam_response *res, unsigned int n)
{
  while (n--) free(res[n].resp) ;
  free(res) ;
}
*/

static int getsa (int h, char const *msg, stralloc *sa)
{
  /* TODO: complete this */
  return 0 ;
}

int misc_conv (int n, struct pam_message const **msg, struct pam_response **resp, void *aux)
{
  stralloc sa = STRALLOC_ZERO ;
  struct pam_response *res ;
  if (n <= 0) return PAM_CONV_ERR ;
  res = malloc(n * sizeof(struct pam_response)) ;
  if (!res) return PAM_CONV_ERR ;
  for (unsigned int i = 0 ; i < n ; i++)
  {
    switch (msg[i]->msg_style)
    {
      case PAM_PROMPT_ECHO_OFF :
        if (getsa(0, msg[i]->msg, &sa)) goto fail ;
        break ;
      case PAM_PROMPT_ECHO_ON :
        if (getsa(1, msg[i]->msg, &sa)) goto fail ;
        break ;
      case PAM_ERROR_MSG :
        strerr_warnw1x(msg[i]->msg) ;
        break ;
      case PAM_TEXT_INFO :
      {
        size_t len = strlen(msg[i]->msg) ;
        if (allwrite(1, msg[i]->msg, len) < len) goto fail ;
        break ;
      }
      case PAM_BINARY_PROMPT : /* TODO */
        break ;
    }
  }
  return 0 ;

 fail:  /* TODO: check */
  return -1 ;
}
