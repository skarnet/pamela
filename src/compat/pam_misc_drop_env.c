/* ISC license. */

#include <stdlib.h>
#include <pamela/compat.h>

static inline void env_free (char **envp)
{
  char **p = envp ;
  while (*p) free(*p++) ;
  free(envp) ;
}

char **pam_misc_drop_env (char **envp)
{
  env_free(envp) ;
  return 0 ;
}
