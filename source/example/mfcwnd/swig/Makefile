ROOTDIR  =../../../..
PKGNAME  =example
PROJNAME =mfcwnd
CPPFLAGS += -D_AFXDLL

include $(ROOTDIR)/config.mk

ifdef VCBIN
include $(SRCPUB_DIR)/swig/Makefile.swig
else
all clean swig: # skip MFC project
endif
