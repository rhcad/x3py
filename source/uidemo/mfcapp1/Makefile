ROOTDIR  =../../..
PKGNAME  =uidemo
PROJNAME =mfcapp1
APPTYPE  =mfc
CPPFLAGS += -D_AFXDLL

include $(ROOTDIR)/config.mk

#INCLUDES += -I$(INTERFACE_DIR)/otherpkg
#LIBS     += -L$(LIBPATHFLAG)yourlibpath  $(LIBFLAG)yourlibname$(LIBEND)

ifdef VCBIN
include $(SRCPUB_DIR)/mk/Makefile.app
else
all clean swig: # skip MFC project
endif
