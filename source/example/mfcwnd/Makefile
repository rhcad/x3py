ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =mfcwnd
CPPFLAGS += -D_AFXDLL

include $(ROOTDIR)/config.mk

#INCLUDES += -I$(INTERFACE_DIR)/otherpkg
#LIBS     += -L$(LIBPATHFLAG)yourlibpath  $(LIBFLAG)yourlibname$(LIBEND)

ifdef VCBIN
include $(SRCPUB_DIR)/swig/Makefile.swig
else
all clean swig: # skip MFC project
endif
