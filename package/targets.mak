BIN_TARGETS :=

LIBEXEC_TARGETS := pamelad

LIB_DEFS := PAMELA=pamela
PAMELA_DESCRIPTION := The pamela client library, a secure PAM implementation.

PAM_LIB := -lpam

$(DESTDIR)$(includedir)/security/pam_appl.h: $(DESTDIR)$(includedir)/$(package)/pam.h
	exec $(INSTALL) -D -l ../$(package)/pam.h $@

install-symlink: $(DESTDIR)$(includedir)/security/pam_appl.h

.PHONY: install-symlink
