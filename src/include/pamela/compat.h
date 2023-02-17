/* ISC license. */

#ifndef PAMELA_COMPAT_H
#define PAMELA_COMPAT_H

#include <pamela/pam.h>

extern int misc_conv (int n, struct pam_message const **, struct pam_response **, void *) ;
extern char **pam_misc_drop_env (char **) ;
extern int pam_misc_paste_env (pam_handle_t *, char const *const *) ;

#endif
