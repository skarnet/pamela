/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/textmessage.h>
#include <pamela/pamela.h>

void pamela_end (pamela_t *a)
{
  int wstat ;
  fd_close(textmessage_sender_fd(&a->out)) ;
  textmessage_sender_free(&a->out) ;
  fd_close(textmessage_receiver_fd(&a->in)) ;
  textmessage_receiver_free(&a->in) ;
  waitpid_nointr(a->pid, &wstat, 0) ;
  *a = pamela_zero ;
}
