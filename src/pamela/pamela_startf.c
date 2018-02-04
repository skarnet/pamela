/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/environ.h>
#include <skalibs/djbunix.h>
#include <skalibs/textmessage.h>
#include <pamela/config.h>
#include <pamela/pamela.h>

int pamela_startf (pamela_t *a, char const *service_name, char const *user, pamela_pam_conv_func_t_ref convfn, void *aux)
{
  char const *argv[4] = { PAMELA_LIBEXECPREFIX "pamelad", service_name, user, 0 } ;
  int fd[2] ;
  pid_t pid = child_spawn2(argv[0], argv, (char const *const *)environ, fd) ;
  int e = PAMELA_PAM_ABORT ;
  struct iovec v ;
  if (!pid) return 0 ;
  textmessage_receiver_init(&a->in, fd[0], a->inbuf, PAMELA_BUFSIZE, TEXTMESSAGE_MAXLEN) ;
  if (textmessage_timed_receive(&a->in, &v, 0, 0) <= 0) goto err ;
  if (v.iov_len != 1) goto ferr ;
  e = ((unsigned char const *)v.iov_base)[0] ; if (e) goto ferr ;
  a->pid = pid ;
  a->delayfn = 0 ;
  a->convfn = convfn ;
  a->aux = aux ;
  textmessage_sender_init(&a->out, fd[1]) ;
  return e ;

 ferr:
  textmessage_receiver_free(&a->in) ;
 err:
  fd_close(fd[1]) ;
  fd_close(fd[0]) ;
  {
    int wstat ;
    waitpid_nointr(pid, &wstat, 0) ;
  }
  return e ;
}
