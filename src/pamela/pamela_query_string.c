/* ISC license. */

#include <errno.h>
#include <sys/uio.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/textmessage.h>
#include <pamela/pamela.h>

int pamela_query_string (pamela_t *a, char const *s, size_t len, stralloc *sa)
{
  struct iovec v ;
  if (!textmessage_timed_send(&a->out, s, len, 0, 0)) return 0 ;
  if (textmessage_timed_receive(&a->in, &v, 0, 0) <= 0) return 0 ;
  if (!v.iov_len) return (errno = EPROTO, 0) ;
  s = v.iov_base ;
  if (s[0]) return (errno = s[0], 0) ;
  if (!stralloc_catb(sa, s + 1, v.iov_len - 1)) return 0 ;
  return 1 ;
}
