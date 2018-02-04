#
# This file has been generated by tools/gen-deps.sh
#

src/include/pamela/pam.h: src/include/pamela/pamela.h
src/include/pamela/pamela.h: src/include/pamela/common.h
src/pamela/pamela-internal.h: src/include/pamela/pamela.h
src/pamela/pam_acct_mgmt.o src/pamela/pam_acct_mgmt.lo: src/pamela/pam_acct_mgmt.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_authenticate.o src/pamela/pam_authenticate.lo: src/pamela/pam_authenticate.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_chauthtok.o src/pamela/pam_chauthtok.lo: src/pamela/pam_chauthtok.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_close_session.o src/pamela/pam_close_session.lo: src/pamela/pam_close_session.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_end.o src/pamela/pam_end.lo: src/pamela/pam_end.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_fail_delay.o src/pamela/pam_fail_delay.lo: src/pamela/pam_fail_delay.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_get_item.o src/pamela/pam_get_item.lo: src/pamela/pam_get_item.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_getenv.o src/pamela/pam_getenv.lo: src/pamela/pam_getenv.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_getenvlist.o src/pamela/pam_getenvlist.lo: src/pamela/pam_getenvlist.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_open_session.o src/pamela/pam_open_session.lo: src/pamela/pam_open_session.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_putenv.o src/pamela/pam_putenv.lo: src/pamela/pam_putenv.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_set_item.o src/pamela/pam_set_item.lo: src/pamela/pam_set_item.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_setcred.o src/pamela/pam_setcred.lo: src/pamela/pam_setcred.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_start.o src/pamela/pam_start.lo: src/pamela/pam_start.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pam_strerror.o src/pamela/pam_strerror.lo: src/pamela/pam_strerror.c src/include/pamela/pam.h src/include/pamela/pamela.h
src/pamela/pamela_end.o src/pamela/pamela_end.lo: src/pamela/pamela_end.c src/include/pamela/pamela.h
src/pamela/pamela_get_item.o src/pamela/pamela_get_item.lo: src/pamela/pamela_get_item.c src/pamela/pamela-internal.h src/include/pamela/pamela.h
src/pamela/pamela_getenvlist.o src/pamela/pamela_getenvlist.lo: src/pamela/pamela_getenvlist.c src/pamela/pamela-internal.h src/include/pamela/pamela.h
src/pamela/pamela_op.o src/pamela/pamela_op.lo: src/pamela/pamela_op.c src/include/pamela/pamela.h
src/pamela/pamela_pam_response_free.o src/pamela/pamela_pam_response_free.lo: src/pamela/pamela_pam_response_free.c src/include/pamela/pamela.h
src/pamela/pamela_query_string.o src/pamela/pamela_query_string.lo: src/pamela/pamela_query_string.c src/include/pamela/pamela.h
src/pamela/pamela_set_item.o src/pamela/pamela_set_item.lo: src/pamela/pamela_set_item.c src/pamela/pamela-internal.h src/include/pamela/pamela.h
src/pamela/pamela_set_item_internal.o src/pamela/pamela_set_item_internal.lo: src/pamela/pamela_set_item_internal.c src/include/pamela/pamela.h
src/pamela/pamela_set_itemv.o src/pamela/pamela_set_itemv.lo: src/pamela/pamela_set_itemv.c src/pamela/pamela-internal.h src/include/pamela/pamela.h
src/pamela/pamela_startf.o src/pamela/pamela_startf.lo: src/pamela/pamela_startf.c src/include/pamela/config.h src/include/pamela/pamela.h
src/pamela/pamela_strerror.o src/pamela/pamela_strerror.lo: src/pamela/pamela_strerror.c src/pamela/pamela-internal.h src/include/pamela/pamela.h
src/pamela/pamela_zero.o src/pamela/pamela_zero.lo: src/pamela/pamela_zero.c src/include/pamela/pamela.h
src/pamela/pamelad.o src/pamela/pamelad.lo: src/pamela/pamelad.c src/include/pamela/common.h

ifeq ($(strip $(STATIC_LIBS_ARE_PIC)),)
libpamela.a.xyzzy: src/pamela/pam_acct_mgmt.o src/pamela/pam_authenticate.o src/pamela/pam_chauthtok.o src/pamela/pam_close_session.o src/pamela/pam_end.o src/pamela/pam_fail_delay.o src/pamela/pam_get_item.o src/pamela/pam_getenv.o src/pamela/pam_getenvlist.o src/pamela/pam_open_session.o src/pamela/pam_putenv.o src/pamela/pam_set_item.o src/pamela/pam_setcred.o src/pamela/pam_start.o src/pamela/pam_strerror.o src/pamela/pamela_end.o src/pamela/pamela_get_item.o src/pamela/pamela_getenvlist.o src/pamela/pamela_op.o src/pamela/pamela_pam_response_free.o src/pamela/pamela_query_string.o src/pamela/pamela_set_item.o src/pamela/pamela_set_item_internal.o src/pamela/pamela_set_itemv.o src/pamela/pamela_startf.o src/pamela/pamela_strerror.o src/pamela/pamela_zero.o
else
libpamela.a.xyzzy: src/pamela/pam_acct_mgmt.lo src/pamela/pam_authenticate.lo src/pamela/pam_chauthtok.lo src/pamela/pam_close_session.lo src/pamela/pam_end.lo src/pamela/pam_fail_delay.lo src/pamela/pam_get_item.lo src/pamela/pam_getenv.lo src/pamela/pam_getenvlist.lo src/pamela/pam_open_session.lo src/pamela/pam_putenv.lo src/pamela/pam_set_item.lo src/pamela/pam_setcred.lo src/pamela/pam_start.lo src/pamela/pam_strerror.lo src/pamela/pamela_end.lo src/pamela/pamela_get_item.lo src/pamela/pamela_getenvlist.lo src/pamela/pamela_op.lo src/pamela/pamela_pam_response_free.lo src/pamela/pamela_query_string.lo src/pamela/pamela_set_item.lo src/pamela/pamela_set_item_internal.lo src/pamela/pamela_set_itemv.lo src/pamela/pamela_startf.lo src/pamela/pamela_strerror.lo src/pamela/pamela_zero.lo
endif
libpamela.so.xyzzy: EXTRA_LIBS :=
libpamela.so.xyzzy: src/pamela/pam_acct_mgmt.lo src/pamela/pam_authenticate.lo src/pamela/pam_chauthtok.lo src/pamela/pam_close_session.lo src/pamela/pam_end.lo src/pamela/pam_fail_delay.lo src/pamela/pam_get_item.lo src/pamela/pam_getenv.lo src/pamela/pam_getenvlist.lo src/pamela/pam_open_session.lo src/pamela/pam_putenv.lo src/pamela/pam_set_item.lo src/pamela/pam_setcred.lo src/pamela/pam_start.lo src/pamela/pam_strerror.lo src/pamela/pamela_end.lo src/pamela/pamela_get_item.lo src/pamela/pamela_getenvlist.lo src/pamela/pamela_op.lo src/pamela/pamela_pam_response_free.lo src/pamela/pamela_query_string.lo src/pamela/pamela_set_item.lo src/pamela/pamela_set_item_internal.lo src/pamela/pamela_set_itemv.lo src/pamela/pamela_startf.lo src/pamela/pamela_strerror.lo src/pamela/pamela_zero.lo
pamelad: EXTRA_LIBS := ${PAM_LIB}
pamelad: src/pamela/pamelad.o -lskarnet
