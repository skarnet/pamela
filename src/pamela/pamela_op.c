/* ISC license. */

#include <string.h>
#include <stdint.h>
#include <sys/uio.h>

#include <skalibs/posixishard.h>
#include <skalibs/uint32.h>
#include <skalibs/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/textmessage.h>
#include <pamela/pamela.h>

static inline int pamela_fail_delay (pamela_t *a, int r, unsigned int usec)
{
  (*a->delayfn)(r, usec, a->aux) ;
  if (!textmessage_timed_send(&a->out, "D", 1, 0, 0)) return PAMELA_PAM_ABORT ;
  return PAMELA_PAM_SUCCESS ;
}

static inline int pamela_converse_and_answer (pamela_t *a, char const *s, size_t len)
{
  pamela_pam_response_t *res ;
  uint32_t n ;
  int e ;
  char ans[2] = "C" ;
  if (len < 4) return PAMELA_PAM_ABORT ;
  uint32_unpack_big(s, &n) ;
  s += 4 ; len -= 4 ;
  if (n > PAMELA_PAM_CONV_MAX_MESSAGES) return PAMELA_PAM_ABORT ;
  if (len < n * 5) return PAMELA_PAM_ABORT ;
  {
    pamela_pam_message_t messages[n] ;
    pamela_pam_message_t const *arr[n] ;
    for (uint32_t i = 0 ; i < n ; i++)
    {
      uint32_t u ;
      uint32_unpack_big(s + 4 * i, &u) ;
      messages[i].msg_style = u ;
      arr[i] = &messages[i] ;
    }
    s += n * 4 ; len -= n * 4 ;
    for (uint32_t i = 0 ; i < n ; i++)
    {
      size_t pos = strnlen(s, len) ;
      if (pos == len) return PAMELA_PAM_ABORT ;
      messages[i].msg = s ;
      s += pos + 1 ; len -= pos + 1 ;
    }
    if (len) return PAMELA_PAM_ABORT ;
    e = (*a->convfn)((int)n, arr, &res, a->aux) ;
  }
  if (e != PAMELA_PAM_SUCCESS)
  {
    ans[1] = (unsigned char)e ;
    if (!textmessage_timed_send(&a->out, ans, 2, 0, 0)) return PAMELA_PAM_ABORT ;
  }
  else
  {
    struct iovec v[n+1] ;
    v[0].iov_base = ans ;
    v[0].iov_len = 2 ;
    for (uint32_t i = 0 ; i < n ; i++)
    {
      v[i+1].iov_base = res[i].resp ;
      v[i+1].iov_len = strlen(res[i].resp) + 1 ;
    }
    if (!textmessage_timed_sendv(&a->out, v, n+1, 0, 0))
    {
      pamela_pam_response_free(res, n) ;
      return PAMELA_PAM_ABORT ;
    }
    pamela_pam_response_free(res, n) ;
  }
  return PAMELA_PAM_SUCCESS ;
}

int pamela_op (pamela_t *a, unsigned char type, int num)
{
  {
    char pack[sizeof(int)] ;
    struct iovec v[3] =
    {
      { .iov_base = "O", .iov_len = 1 },
      { .iov_base = &type, .iov_len = 1 },
      { .iov_base = pack, .iov_len = sizeof(int) }
    } ;
    int_pack_big(pack, num) ;
    if (!textmessage_timed_sendv(&a->out, v, 3, 0, 0)) return PAMELA_PAM_SYSTEM_ERR ;
  }
  for (;;)
  {
    struct iovec v ;
    char const *s ;
    if (textmessage_timed_receive(&a->in, &v, 0, 0) <= 0) return PAMELA_PAM_ABORT ;
    if (v.iov_len < 2) return PAMELA_PAM_ABORT ;
    s = v.iov_base ;
    switch (s[0])
    {
      case 'o' : /* operation returns */
        if (v.iov_len != 2) return PAMELA_PAM_ABORT ;
        return s[1] ;
      case 'c' : /* conversation request */
      {
        int e = pamela_converse_and_answer(a, s + 1, v.iov_len - 1) ;
        if (e != PAMELA_PAM_SUCCESS) return e ;
        break ;
      }
      case 'd' : /* fail_delay request */
      {
        uint32_t u ;
        int r ;
        unsigned int usec ;
        if (v.iov_len != 9) return PAMELA_PAM_ABORT ;
        uint32_unpack_big(s + 1, &u) ; r = u ;
        uint32_unpack_big(s + 5, &u) ; usec = u ;
        r = pamela_fail_delay(a, r, usec) ;
        if (r != PAMELA_PAM_SUCCESS) return r ;
        break ;
      }
      default : return PAMELA_PAM_ABORT ;
    }
  }
}
