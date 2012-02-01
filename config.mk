# Included by Makefile. You can customize it.
# Readme for variables: https://github.com/rhcad/x3py/wiki/MakeVars

INTERFACE_DIR =$(ROOTDIR)/interface
INSTALL_DIR   =$(ROOTDIR)/build
PLUGINS_DIR   =$(INSTALL_DIR)/plugins

CC            =g++
LINK          =g++
CPPFLAGS     += -g -Wall -Wno-unused -I$(INTERFACE_DIR)/core
LDFLAGS      += -g -Wall
ifdef PKGNAME
CPPFLAGS     += -I$(INTERFACE_DIR)/$(PKGNAME)
endif

OS           ?=$(shell uname -s)
IS_WIN       :=$(shell echo $(OS)|grep -i Windows)
IS_MACOSX    :=$(shell echo $(OS)|grep -i Darwin)

ifndef EXETYPE
ifdef IS_WIN
CPPFLAGS     += -D_USRDLL
LDFLAGS      += -shared
else
CPPFLAGS     += -fPIC
LDFLAGS      += -shared -fPIC
endif
endif

ifdef IS_WIN
APPEXT        =.exe
else
LIBS         += -ldl
endif

# Environment variables used by source/public/swig/Makefile.swig
# You may change the default values or set environment variables (must set them on Windows).

ifdef IS_MACOSX
PYTHON_INCLUDE ?=/usr/include/python2.6
PYTHON_LIBFILE ?=python
JAVA_INCLUDE   ?=/Library/Java/Home/include
else # Linux
PYTHON_INCLUDE ?=/usr/include/python2.7
PYTHON_LIBFILE ?=python2.7
JAVA_INCLUDE   ?=/usr/lib/jvm/java-6-openjdk/include
endif
PERL5_INCLUDE  ?=/usr/lib/perl/5.12.4/CORE
PERL5_LIBFILE  ?=perl
RUBY_INCLUDE   ?=/usr/include/ruby-1.9.1
RUBY_LIBFILE   ?=ruby-1.9.1
