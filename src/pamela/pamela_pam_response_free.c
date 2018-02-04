/* ISC license. */

#include <stdint.h>
#include <stdlib.h>
#include <pamela/pamela.h>

void pamela_pam_response_free (pamela_pam_response_t *res, uint32_t n)
{
  for (uint32_t i = 0 ; i < n ; i++) free(res[i].resp) ;
  free(res) ;
}
