/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/uint32.h>
#include <pamela/pamela.h>
#include <pamela/pam.h>

static int xauthdata_unpack (pam_handle_t *pamh)
{
  uint32_t namelen, datalen ;
  uint32_unpack_big(pamh->item[PAM_XAUTHDATA].s, &namelen) ;
  uint32_unpack_big(pamh->item[PAM_XAUTHDATA].s + 4, &datalen) ;
  if (namelen + datalen + 10 != pamh->item[PAM_XAUTHDATA].len) return 0 ;
  pamh->xauthdata.namelen = (int)namelen ;
  pamh->xauthdata.datalen = (int)namelen ;
  pamh->xauthdata.name = pamh->item[PAM_XAUTHDATA].s + 8 ;
  pamh->xauthdata.data = pamh->item[PAM_XAUTHDATA].s + 9 + namelen ;
  return 1 ;
}

int pam_get_item (pam_handle_t *pamh, int item_type, void const **item)
{
  if (!pamh) return PAM_SYSTEM_ERR ;
  if (item_type < 1 || item_type >= PAM_ITEM_MAX) return PAM_BAD_ITEM ;
  switch (item_type)
  {
    case PAM_FAIL_DELAY :
      *item = (void const *)pamh->handle.delayfn ;
      return PAM_SUCCESS ;
    case PAM_CONV :
      *item = (void const *)pamh->handle.convfn ;
      return PAM_SUCCESS ;
    default : break ;
  }
  pamh->item[item_type].len = 0 ;
  {
    int e = pamela_get_item(&pamh->handle, (unsigned char)item_type, &pamh->item[item_type]) ;
    if (e) return e ;
  }
  switch (item_type)
  {
    case PAM_XAUTHDATA :
      if (!xauthdata_unpack(pamh)) return PAM_ABORT ;
      *item = (void const *)&pamh->xauthdata ;
      break ;
    default :
      *item = (void const *)pamh->item[item_type].s ;
      break ;
  }
  return PAM_SUCCESS ;
}
