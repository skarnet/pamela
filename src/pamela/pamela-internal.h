/* ISC license. */

#ifndef PAMELA_INTERNAL_H
#define PAMELA_INTERNAL_H

#include <sys/uio.h>
#include <skalibs/stralloc.h>
#include <pamela/pamela.h>

extern int pamela_query_string (pamela_t *, char const *, size_t, stralloc *) ;
extern int pamela_set_item_internal (pamela_t *, struct iovec const *, unsigned int) ;

#endif
