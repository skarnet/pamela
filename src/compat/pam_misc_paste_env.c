/* ISC license. */

#include <pamela/pam.h>
#include <pamela/compat.h>

int pam_misc_paste_env (pam_handle_t *pamh, char const *const *envp)
{
  for (; *envp ; envp++)
  {
    int e = pam_putenv(pamh, *envp) ;
    if (e != PAM_SUCCESS) return e ;
  }
  return PAM_SUCCESS ;
}
