/* ISC license. */

#ifndef PAMELA_H
#define PAMELA_H

 /*
    Declarations for the client library.
    This is the internal layer, that does not
    depend on the PAM API.
 */

#include <sys/types.h>
#include <stdint.h>
#include <sys/uio.h>
#include <skalibs/stralloc.h>
#include <skalibs/textmessage.h>
#include <pamela/common.h>


 /* Misc defs */

#define PAMELA_BUFSIZE 4096


 /* pam_fail_delay */

typedef void pamela_pam_delay_func (int, unsigned int, void *) ;
typedef pamela_pam_delay_func *pamela_pam_delay_func_ref ;


 /* Conversations */

typedef struct pamela_pam_message_s pamela_pam_message_t, *pamela_pam_message_t_ref ;
struct pamela_pam_message_s
{
  int msg_style ;
  char const *msg ;
} ;

typedef struct pamela_pam_response_s pamela_pam_response_t, *pamela_pam_response_t_ref ;
struct pamela_pam_response_s
{
  char *resp ;
  int *resp_retcode ;
} ;

extern void pamela_pam_response_free (pamela_pam_response_t *, uint32_t) ;

typedef int pamela_pam_conv_func (int, pamela_pam_message_t const **, pamela_pam_response_t **, void *) ;
typedef pamela_pam_conv_func *pamela_pam_conv_func_ref ;


 /* Client handle */

typedef struct pamela_s pamela_t, *pamela_t_ref ;
struct pamela_s
{
  textmessage_receiver in ;
  textmessage_sender out ;
  pid_t pid ;
  pamela_pam_delay_func_ref delayfn ;
  pamela_pam_conv_func_ref convfn ;
  void *aux ;
  char inbuf[PAMELA_BUFSIZE] ;
} ;
#define PAMELA_ZERO { TEXTMESSAGE_RECEIVER_ZERO, TEXTMESSAGE_SENDER_ZERO, 0, 0, 0, 0, "" }

extern pamela_t const pamela_zero ;


 /* User-facing functions */

extern int pamela_startf (pamela_t *, char const *, char const *, pamela_pam_conv_func_ref, void *) ;
extern void pamela_end (pamela_t *) ;
extern int pamela_strerror (pamela_t *, unsigned char, stralloc *) ;
extern int pamela_getenvlist (pamela_t *, stralloc *) ;
extern int pamela_get_item (pamela_t *, unsigned char, stralloc *) ;
extern int pamela_set_item (pamela_t *, unsigned char, char const *) ;
extern int pamela_set_itemv (pamela_t *, unsigned char, struct iovec const *, unsigned int) ;
extern int pamela_op (pamela_t *, unsigned char, int) ;

#endif
