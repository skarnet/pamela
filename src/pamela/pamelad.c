/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/uio.h>

#include <skalibs/uint32.h>
#include <skalibs/types.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/strerr2.h>
#include <skalibs/sig.h>
#include <skalibs/djbunix.h>
#include <skalibs/textmessage.h>
#include <skalibs/posixishard.h>
#include <pamela/common.h>
#include <security/pam_appl.h>

#define USAGE "pamelad service_name user"

static int cont = 1 ;
static pam_handle_t *pamh ;


 /* Utility */

static void get (struct iovec *v)
{
  ssize_t r = textmessage_timed_receive(textmessage_receiver_0, v, 0, 0) ;
  if (r < 0) _exit(1) ;
  if (!r) _exit(0) ;
}

static void put (char const *s, size_t len)
{
  if (!textmessage_timed_send(textmessage_sender_1, s, len, 0, 0))
    _exit(1) ;
}

static void putv (struct iovec const *v, unsigned int n)
{
  if (!textmessage_timed_sendv(textmessage_sender_1, v, n, 0, 0))
    _exit(1) ;
}

static inline void env_free (char **envp)
{
  char **p = envp ;
  while (*p) free(*p++) ;
  free(envp) ;
}


 /* If the app customizes fail_delay */

static void custom_delay (int retval, unsigned int usec, void *aux)
{
  struct iovec v ;
  char pack[9] = "d" ;
  uint32_pack_big(pack+1, (uint32_t)retval) ;
  uint32_pack_big(pack+5, (uint32_t)usec) ;
  put(pack, 9) ;
  get(&v) ;
  if (v.iov_len != 1 || ((char const *)v.iov_base)[0] != 'D') _exit(1) ;
  (void)aux ;
}


 /* Conversation */

static void freeres (struct pam_response *res, unsigned int i)
{
  while (i--) free(res[i].resp) ;
  free(res) ;
}

static int converse (int n, struct pam_message const **msg, struct pam_response **resp, void *aux)
{
  if (n < 0 || n > PAMELA_PAM_CONV_MAX_MESSAGES) return PAM_SYSTEM_ERR ;
  {
    char pack[n * 4] ;
    struct iovec v[n+2] ;
    v[0].iov_base = "c" ;
    v[0].iov_len = 1 ;
    v[1].iov_base = pack ;
    v[1].iov_len = n << 2 ;
    for (uint32_t i = 0 ; i < n ; i++) uint32_pack_big(pack + 4 * i, (uint32_t)msg[i]->msg_style) ;
    for (uint32_t i = 0 ; i < n ; i++)
    {
      v[i+2].iov_base = (char *)msg[i]->msg ;
      v[i+2].iov_len = strlen(msg[i]->msg) + 1 ;
    }
    putv(v, n+2) ;
  }
  {
    struct pam_response *res ;
    struct iovec v ;
    char const *s ;
    size_t len ;
    get(&v) ;
    if (v.iov_len < 2) return PAM_ABORT ;
    s = v.iov_base ;
    len = v.iov_len - 2 ;
    if (s[0] != 'C') return PAM_ABORT ;
    if (s[1]) return s[1] ;
    s += 2 ;
    res = malloc(n * sizeof(struct pam_response)) ;
    if (!res) return PAM_BUF_ERR ;
    for (uint32_t i = 0 ; i < n ; i++)
    {
      size_t pos = strnlen(s, len) ;
      if (pos == len) return PAM_ABORT ;
      res[i].resp_retcode = 0 ;
      res[i].resp = strdup(s) ;
      if (!res[i].resp)
      {
        freeres(res, i) ;
        return PAM_BUF_ERR ;
      }
      s += pos + 1 ; len -= pos + 1 ;
    }
    if (len)
    {
      freeres(res, n) ;
      return PAM_ABORT ;
    }
    *resp = res ;
  }
  (void)aux ;
  return PAM_SUCCESS ;
}


 /* Protocol and actions */

static void do_strerror (int num)
{
  char const *x = pam_strerror(pamh, num) ;
  if (!x)
  {
    char c = errno ;
    if (!c) c = EIO ;
    put(&c, 1) ;
  }
  else
  {
    struct iovec v[2] =
    {
      { .iov_base = "", .iov_len = 1 },
      { .iov_base = (char *)x, .iov_len = strlen(x) + 1 }
    } ;
    putv(v, 2) ;
  }
}

static void do_getenvlist (void)
{
  char **envp = pam_getenvlist(pamh) ;
  if (!envp)
  {
    char c = errno ;
    if (!c) c = EIO ;
    put(&c, 1) ;
  }
  else
  {
    size_t n = env_len((char const *const *)envp) ;
    struct iovec v[n+1] ;
    v[0].iov_base = "" ;
    v[0].iov_len = 1 ;
    for (size_t i = 0 ; i < n ; i++)
    {
      v[i+1].iov_base = envp[i] ;
      v[i+1].iov_len = strlen(envp[i]) + 1 ;
    }
    putv(v, n+1) ;
    env_free(envp) ;
  }
}

static void do_getitem (int num)
{
  void const *item ;
  int e = pam_get_item(pamh, num, &item) ;
  if (e != PAM_SUCCESS)
  {
    char c = e ;
    put(&c, 1) ;
    return ;
  }
  switch (num)
  {
    case PAMELA_PAM_FAIL_DELAY :
    case PAMELA_PAM_CONV :
    {
      char c = PAMELA_PAM_BAD_ITEM ;
      put(&c, 1) ;
      break ;
    }
    case PAMELA_PAM_XAUTHDATA :
    {
      struct pam_xauth_data const *p = item ;
      char pack[8] ;
      struct iovec v[4] =
      {
        { .iov_base = "", .iov_len = 1 },
        { .iov_base = pack, .iov_len = 8 },
        { .iov_base = p->name, .iov_len = p->namelen + 1 },
        { .iov_base = p->data, .iov_len = p->datalen + 1 }
      } ;
      uint32_pack_big(pack, (uint32_t)p->namelen) ;
      uint32_pack_big(pack + 4, (uint32_t)p->datalen) ;
      putv(v, 4) ;
      break ;
    }
    default :
    {
      struct iovec v[2] =
      {
        { .iov_base = "", .iov_len = 1 },
        { .iov_base = (char *)item, .iov_len = strlen((char const *)item) + 1 }
      } ;
      putv(v, 2) ;
      break ;
    }
  }
}

static void do_setitem (int num, char const *s, size_t len)
{
  char c ;
  switch (num)
  {
    case PAMELA_PAM_FAIL_DELAY :
    case PAMELA_PAM_CONV :
    baditem:
      c = PAMELA_PAM_BAD_ITEM ;
      break ;
    case PAMELA_ENV :
      if (s[len-1]) goto baditem ;
      c = pam_putenv(pamh, s) ;
      break ;
    case PAMELA_PAM_XAUTHDATA :
    {
      struct pam_xauth_data xd ;
      uint32_t u ;
      if (len < 10) goto baditem ;
      uint32_unpack_big(s, &u) ;
      xd.namelen = u ;
      uint32_unpack_big(s + 4, &u) ;
      xd.datalen = u ;
      if (len != 10 + xd.namelen + xd.datalen) goto baditem ;
      xd.name = (char *)s + 8 ;
      xd.data = (char *)s + 9 + xd.namelen ;
      c = pam_set_item(pamh, PAM_XAUTHDATA, &xd) ;
      break ;
    }
    default :
      if (s[len-1]) goto baditem ;
      c = pam_set_item(pamh, num, s) ;
      break ;
  }
  put(&c, 1) ;
}

static void do_op (char type, int num)
{
  char s[2] = "o" ;
  switch (type)
  {
    case PAMELA_OP_ACCT_MGMT :
      s[1] = pam_acct_mgmt(pamh, num) ;
      break ;
    case PAMELA_OP_AUTHENTICATE :
      s[1] = pam_authenticate(pamh, num) ;
      break ;
    case PAMELA_OP_CHAUTHTOK :
      s[1] = pam_chauthtok(pamh, num) ;
      break ;
    case PAMELA_OP_CLOSE_SESSION :
      s[1] = pam_close_session(pamh, num) ;
      break ;
    case PAMELA_OP_FAIL_DELAY :
      s[1] = pam_fail_delay(pamh, (unsigned int)num) ;
      break ;
    case PAMELA_OP_OPEN_SESSION :
      s[1] = pam_open_session(pamh, num) ;
      break ;
    case PAMELA_OP_SETCRED :
      s[1] = pam_setcred(pamh, num) ;
      break ;
    case PAMELA_OP_SETFAILDELAY :
      s[1] = pam_set_item(pamh, PAM_FAIL_DELAY, &custom_delay) ;
      break ;
    case PAMELA_OP_END :
      s[1] = pam_end(pamh, num) ;
      break ;
    default :
      s[1] = PAM_ABORT ;
      break ;
  }
  put(s, 2) ;
  if (type == PAMELA_OP_END) cont = 0 ;
}


 /* Main */

int main (int argc, char const *const *argv)
{
  PROG = "pamelad" ;
  if (argc < 3) strerr_dieusage(100, USAGE) ;
  if (ndelay_on(0) < 0) strerr_diefu2sys(111, "ndelay_on ", "0") ;
  if (ndelay_on(1) < 0) strerr_diefu2sys(111, "ndelay_on ", "1") ;
  if (!sig_altignore(SIGPIPE)) strerr_diefu1sys(111, "ignore SIGPIPE") ;

  if (!getgid())
  {
    char const *x = getenv("PAMELA_GID") ;
    if (x)
    {
      gid_t g ;
      if (!gid0_scan(x, &g))
        strerr_warnw1x("invalid PAMELA_GID, keeping gid 0") ;
      else setgid(g) ;
    }
  }
  if (!getuid())
  {
    char const *x = getenv("PAMELA_UID") ;
    if (x)
    {
      uid_t u ;
      if (!uid0_scan(x, &u))
        strerr_warnw1x("invalid PAMELA_UID, keeping uid 0") ;
      else setuid(u) ;
    }
  }

  {
    struct pam_conv conv = { .conv = &converse, .appdata_ptr = 0 } ;
    char c = pam_start(argv[1], argv[2], &conv, &pamh) ;
    put(&c, 1) ;
    if (c != PAM_SUCCESS) return 2 ;
  }

  while (cont)
  {
    struct iovec v ;
    char const *s ;
    size_t len ;
    get(&v) ;
    len = v.iov_len ;
    if (!len) return 1 ;
    s = v.iov_base ;
    switch (s[0])
    {
      case 'E' :
        if (len != 2) return 1 ;
        do_strerror(s[1]) ;
        break ;
      case 'V' :
        if (len != 1) return 1 ;
        do_getenvlist() ;
        break ;
      case 'G' :
        if (len != 2) return 1 ;
        do_getitem(s[1]) ;
        break ;
      case 'S' :
        if (len < 3) return 1 ;
        do_setitem(s[1], s + 2, len - 2) ;
        break ;
      case 'O' :
      {
        unsigned int arg ;
        if (len != 2 + sizeof(int)) return 1 ;
        uint_unpack(s + 2, &arg) ;
        do_op(s[1], (int)arg) ;
        break ;
      }
      default : return 1 ;
    }
  }
  return 0 ;
}
