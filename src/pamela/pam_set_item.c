/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <sys/uio.h>
#include <skalibs/uint32.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

static int xauthdata_pack_and_set (pamela_t *a, struct pam_xauth_data const *d)
{
  if (d->namelen < 0 || d->datalen < 0) return PAM_SYSTEM_ERR ;
  {
    char buf[8] ;
    struct iovec v[3] =
    {
      { .iov_base = buf, .iov_len = 8 },
      { .iov_base = d->name, .iov_len = d->namelen + 1 },
      { .iov_base = d->data, .iov_len = d->datalen + 1 }
    } ;
    uint32_pack_big(buf, (uint32_t)d->namelen) ;
    uint32_pack_big(buf + 4, (uint32_t)d->datalen) ;
    return pamela_set_itemv(a, PAM_XAUTHDATA, v, 3) ;
  }
}

int pam_set_item (pam_handle_t *pamh, int item_type, void const *item)
{
  if (!pamh) return PAM_SYSTEM_ERR ;
  if (item_type < 1 || item_type >= PAM_ITEM_MAX) return PAM_BAD_ITEM ;
  switch (item_type)
  {
    case PAM_FAIL_DELAY :
    {
      int e ;
      pamh->handle.delayfn = (pamela_pam_delay_func_ref)item ;
      e = pamela_op(&pamh->handle, PAMELA_OP_SETFAILDELAY, 0) ;
      if (e != PAM_SUCCESS) return e ;
      break ;
    }
    case PAM_CONV :
      pamh->handle.convfn = (pamela_pam_conv_func_ref)item ;
      break ;
    case PAM_XAUTHDATA :
      return xauthdata_pack_and_set(&pamh->handle, (struct pam_xauth_data const *)item) ;
    default :
      return pamela_set_item(&pamh->handle, (uint32_t)item_type, (char const *)item) ;
  }
  return PAM_SUCCESS ;
}
