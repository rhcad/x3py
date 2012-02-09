ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libspln

include $(ROOTDIR)/config.mk

LIBS    += $(LIBPATHFLAG)$(PLUGINS_DIR) \
           $(LIBFLAG)$(LIBPRE)pln1$(LIBEND) \
           $(LIBFLAG)$(LIBPRE)pln2$(LIBEND)

include $(SRCPUB_DIR)/mk/Makefile.pln
