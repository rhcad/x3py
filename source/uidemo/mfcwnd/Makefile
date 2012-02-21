ROOTDIR  =../../..
PKGNAME  =uidemo
PROJNAME =mfcwnd
CPPFLAGS += -D_AFXDLL -D_AFXEXT

include $(ROOTDIR)/config.mk

#INCLUDES += -I$(INTERFACE_DIR)/otherpkg
#LIBS     += -L$(LIBPATHFLAG)yourlibpath  $(LIBFLAG)yourlibname$(LIBEND)

ifdef VCBIN
include $(SRCPUB_DIR)/swig/Makefile.plswig
else
all clean swig: # skip MFC project
endif
