/* ISC license. */

#include <sys/uio.h>
#include <skalibs/textmessage.h>
#include <pamela/pamela.h>

int pamela_set_item_internal (pamela_t *a, struct iovec const *v, unsigned int n)
{
  struct iovec r ;
  if (!textmessage_timed_sendv(&a->out, v, n, 0, 0)) return PAMELA_PAM_SYSTEM_ERR ;
  if (textmessage_timed_receive(&a->in, &r, 0, 0) <= 0) return PAMELA_PAM_ABORT ;
  if (r.iov_len != 1) return PAMELA_PAM_ABORT ;
  return ((unsigned char const *)r.iov_base)[0] ;
}
