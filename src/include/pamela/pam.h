/* ISC license. */

#ifndef PAMELA_PAM_H
#define PAMELA_PAM_H

 /*
    This is pamela's client-side PAM library.
    
 */

#include <skalibs/uint64.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>

#define __LINUX_PAM__ 1
#define __LINUX_PAM_MINOR__ 0


 /* Return codes */

#define _PAM_RETURN_VALUES 32

#define PAM_SUCCESS PAMELA_PAM_SUCCESS
#define PAM_OPEN_ERR PAMELA_PAM_OPEN_ERR
#define PAM_SYMBOL_ERR PAMELA_PAM_SYMBOL_ERR
#define PAM_SERVICE_ERR PAMELA_PAM_SERVICE_ERR
#define PAM_SYSTEM_ERR PAMELA_PAM_SYSTEM_ERR
#define PAM_BUF_ERR PAMELA_PAM_BUF_ERR
#define PAM_PERM_DENIED PAMELA_PAM_PERM_DENIED
#define PAM_AUTH_ERR PAMELA_PAM_AUTH_ERR
#define PAM_CRED_INSUFFICIENT PAMELA_PAM_CRED_INSUFFICIENT
#define PAM_AUTHINFO_UNAVAIL PAMELA_PAM_AUTHINFO_UNAVAIL
#define PAM_USER_UNKNOWN PAMELA_PAM_USER_UNKNOWN
#define PAM_MAXTRIES PAMELA_PAM_MAXTRIES
#define PAM_NEW_AUTHTOK_REQD PAMELA_PAM_NEW_AUTHTOK_REQD
#define PAM_ACCT_EXPIRED PAMELA_PAM_ACCT_EXPIRED
#define PAM_SESSION_ERR PAMELA_PAM_SESSION_ERR
#define PAM_CRED_UNAVAIL PAMELA_PAM_CRED_UNAVAIL
#define PAM_CRED_EXPIRED PAMELA_PAM_CRED_EXPIRED
#define PAM_CRED_ERR PAMELA_PAM_CRED_ERR
#define PAM_NO_MODULE_DATA PAMELA_PAM_NO_MODULE_DATA
#define PAM_CONV_ERR PAMELA_PAM_CONV_ERR
#define PAM_AUTHTOK_ERR PAMELA_PAM_AUTHTOK_ERR
#define PAM_AUTHTOK_RECOVERY_ERR PAMELA_PAM_AUTHTOK_RECOVERY_ERR
#define PAM_AUTHTOK_LOCK_BUSY PAMELA_PAM_AUTHTOK_LOCK_BUSY
#define PAM_AUTHTOK_DISABLE_AGING PAMELA_PAM_AUTHTOK_DISABLE_AGING
#define PAM_TRY_AGAIN PAMELA_PAM_TRY_AGAIN
#define PAM_IGNORE PAMELA_PAM_IGNORE
#define PAM_ABORT PAMELA_PAM_ABORT
#define PAM_AUTHTOK_EXPIRED PAMELA_PAM_AUTHTOK_EXPIRED
#define PAM_MODULE_UNKNOWN PAMELA_PAM_MODULE_UNKNOWN
#define PAM_BAD_ITEM PAMELA_PAM_BAD_ITEM
#define PAM_CONV_AGAIN PAMELA_PAM_CONV_AGAIN
#define PAM_INCOMPLETE PAMELA_PAM_INCOMPLETE


 /* Items */

#define PAM_ITEM_MAX 14  /* 13 items + environment */

#define PAM_SERVICE PAMELA_PAM_SERVICE
#define PAM_USER PAMELA_PAM_USER
#define PAM_TTY PAMELA_PAM_TTY
#define PAM_RHOST PAMELA_PAM_RHOST
#define PAM_CONV PAMELA_PAM_CONV
#define PAM_AUTHTOK PAMELA_PAM_AUTHTOK
#define PAM_OLDAUTHTOK PAMELA_PAM_OLDAUTHTOK
#define PAM_RUSER PAMELA_PAM_RUSER
#define PAM_USER_PROMPT PAMELA_PAM_USER_PROMPT
#define PAM_FAIL_DELAY PAMELA_PAM_FAIL_DELAY
#define PAM_XDISPLAY PAMELA_PAM_XDISPLAY
#define PAM_XAUTHDATA PAMELA_PAM_XAUTHDATA
#define PAM_AUTHTOK_TYPE PAMELA_PAM_AUTHTOK_TYPE


 /* Flags */

#define PAM_SILENT PAMELA_PAM_SILENT
#define PAM_DISALLOW_NULL_AUTHTOK PAMELA_PAM_DISALLOW_NULL_AUTHTOK
#define PAM_ESTABLISH_CRED PAMELA_PAM_ESTABLISH_CRED
#define PAM_DELETE_CRED PAMELA_PAM_DELETE_CRED
#define PAM_REINITIALIZE_CRED PAMELA_PAM_REINITIALIZE_CRED
#define PAM_REFRESH_CRED PAMELA_PAM_REFRESH_CRED
#define PAM_CHANGE_EXPIRED_AUTHTOK PAMELA_PAM_CHANGE_EXPIRED_AUTHTOK


 /* Conversation types */

#define PAM_PROMPT_ECHO_OFF PAMELA_PAM_PROMPT_ECHO_OFF
#define PAM_PROMPT_ECHO_ON PAMELA_PAM_PROMPT_ECHO_ON
#define PAM_ERROR_MSG PAMELA_PAM_ERROR_MSG
#define PAM_TEXT_INFO PAMELA_PAM_TEXT_INFO
#define PAM_RADIO_TYPE PAMELA_PAM_RADIO_TYPE
#define PAM_BINARY_PROMPT PAMELA_PAM_BINARY_PROMPT


 /* Misc Linux-PAM stuff */

#define PAM_MAX_NUM_MSG 32
#define PAM_MAX_MSG_SIZE 512
#define PAM_MAX_RESP_SIZE 512

#define PAM_DATA_SILENT PAMELA_PAM_DATA_SILENT


 /* Data structures and functions */

struct pam_message
{
  int msg_style ;
  char const *msg ;
} ;

struct pam_response
{
  char *resp ;
  int resp_retcode ;
} ;

struct pam_conv
{
  int (*conv) (int, struct pam_message const **, struct pam_response **, void *) ;
  void *appdata_ptr ;
} ;

struct pam_xauth_data
{
  int namelen ;
  char *name ;
  int datalen ;
  char *data ;
} ;

typedef struct pam_handle_s pam_handle_t ;
struct pam_handle_s
{
  pamela_t handle ;
  struct pam_xauth_data xauthdata ;
  stralloc err[_PAM_RETURN_VALUES] ;
  stralloc item[PAM_ITEM_MAX] ;
  uint64_t flagerrcached : _PAM_RETURN_VALUES ;
  uint64_t flagenvcached : 1 ;
} ;

extern int pam_start (char const *, char const *, struct pam_conv const *, pam_handle_t **) ;
extern int pam_end (pam_handle_t *, int) ;
extern int pam_set_item (pam_handle_t *, int, void const *) ;
extern int pam_get_item (pam_handle_t *, int, void const **) ;
extern char const *pam_strerror (pam_handle_t *, int) ;
extern int pam_fail_delay (pam_handle_t *, unsigned int) ;
extern int pam_authenticate (pam_handle_t *, int) ;
extern int pam_setcred (pam_handle_t *, int) ;
extern int pam_acct_mgmt (pam_handle_t *, int) ;
extern int pam_chauthtok (pam_handle_t *, int) ;
extern int pam_open_session (pam_handle_t *, int) ;
extern int pam_close_session (pam_handle_t *, int) ;
extern int pam_putenv (pam_handle_t *, char const *) ;
extern char const *pam_getenv (pam_handle_t *, char const *) ;
extern char **pam_getenvlist (pam_handle_t *) ;

#endif
