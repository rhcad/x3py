# Included by Makefile. You can customize it.
# Readme about variables: https://github.com/rhcad/x3py/wiki/MakeVars

INTERFACE_DIR =$(ROOTDIR)/interface
INSTALL_DIR   =$(ROOTDIR)/build
PLUGINS_DIR   =$(INSTALL_DIR)/plugins
SRCPUB_DIR    =$(ROOTDIR)/source/public

INCLUDES     += -I$(INTERFACE_DIR)/core -I$(SRCPUB_DIR)
ifdef PKGNAME
INCLUDES     += -I$(INTERFACE_DIR)/$(PKGNAME)
endif

#-------------------------------------------------------------------
# Flags for GCC and VC++
# LIBS    += $(LIBPATHFLAG)yourlibpath  $(LIBFLAG)yourlibname$(LIBEND)

ifdef VCBIN
CPP           ="$(VCBIN)cl"
LINK          ="$(VCBIN)link"
AR            ="$(VCBIN)lib"
ARFLAGS       =-out:
OUTFLAG       =-out:
OFLAG         =-Fo
LIBPATHFLAG   =-libpath:
LIBPRE        =lib
LIBEND        =.lib
OBJEXT        =.obj
LIBEXT        =.lib

else
CPP           =g++
LINK          =g++
CPPFLAGS     += -g -Wall -Wno-unused
LDFLAGS      += -g -Wall
OUTFLAG       =-o #space
OFLAG         =-o #
ARFLAGS      += #space
LIBPATHFLAG   =-L
LIBFLAG       =-l
OBJEXT        =.o
LIBEXT        =.a
endif

#-------------------------------------------------------------------

OS           ?=$(shell uname -s)
IS_WIN       :=$(shell echo $(OS)|grep -i Windows)
IS_MACOSX    :=$(shell echo $(OS)|grep -i Darwin)

IS_CONSOLE   :=$(shell echo $(APPTYPE)|grep -i console)
IS_LIB       :=$(shell echo $(CPPFLAGS)|grep -i D_LIB)
IS_AFXDLL    :=$(shell echo $(CPPFLAGS)|grep -i D_AFXDLL)
IS_AFXEXT    :=$(shell echo $(CPPFLAGS)|grep -i D_AFXEXT)

ifndef APPTYPE # dll or lib
ifdef IS_WIN
ifndef IS_AFXEXT
CPPFLAGS     += -D_USRDLL
endif
ifndef VCBIN
LDFLAGS      += -shared
endif
else # unix library
CPPFLAGS     += -fPIC
LDFLAGS      += -shared -fPIC
endif #IS_WIN
endif #APPTYPE

ifdef IS_WIN
APPEXT        =.exe
else
LIBS         += -ldl
endif

#-------------------------------------------------------------------
# VC++ link options

ifdef VCBIN
INCLUDES     += $(VCINC)
CPPFLAGS     += -nologo $(WINSDKINC) $(VCFLAGS)
LDFLAGS      += -nologo $(VCLIBS)
ifdef APPTYPE # application
ifdef IS_CONSOLE
LDFLAGS      += -subsystem:console
else
LDFLAGS      += -subsystem:windows
ifdef IS_AFXDLL # MFC app
LDFLAGS      += -entry:"wWinMainCRTStartup"
endif
endif   # IS_CONSOLE
else    # not app
ifndef IS_LIB # dll
LDFLAGS      += -subsystem:windows -dll
endif
endif #APPTYPE
endif #VCBIN

ifdef IS_CONSOLE
CPPFLAGS     += -DCONSOLE
endif

# for generating dependency file (*.d)
DEPEND_CC     =g++ -MM
ifdef VCBIN
DEPEND_CC    += -D_MSC_VER=1400 -D_M_IX86
endif
DEPEND_CC    += -MF

#-------------------------------------------------------------------
# Environment variables used by source/public/swig/Makefile.swig
# You may change the default values or set environment variables (must set them on Windows).

ifndef IS_WIN
ifdef IS_MACOSX
PYTHON_INCLUDE ?=/usr/include/python2.6
PYTHON_LIBFILE ?=python
JAVA_INCLUDE   ?=/Library/Java/Home/include
else # Linux
PYTHON_INCLUDE ?=/usr/include/python2.7
PYTHON_LIBFILE ?=python2.7
JAVA_INCLUDE   ?=/usr/lib/jvm/java-6-openjdk/include
QT4_INCLUDE    ?=/usr/include/qt4
QT4_LIB        ?=/usr/lib/x86_64-linux-gnu
endif
PERL5_INCLUDE  ?=/usr/lib/perl/5.12.4/CORE
PERL5_LIBFILE  ?=perl
RUBY_INCLUDE   ?=/usr/include/ruby-1.9.1
RUBY_LIBFILE   ?=ruby-1.9.1
endif

