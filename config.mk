# Included by Makefile. You can customize it.

INTERFACE_DIR =$(ROOTDIR)/interface
INSTALL_DIR   =$(ROOTDIR)/build
PLUGINS_DIR   =$(INSTALL_DIR)/plugins

CC            = g++
CFLAGS       += -g -I$(INTERFACE_DIR)/core
C_FLAGS      += -g -Wall
ifdef PKGNAME
CFLAGS       += -I$(INTERFACE_DIR)/$(PKGNAME)
endif

CFLAGS_SO     = $(CFLAGS) -fPIC -D_USRDLL
C_FLAGS_SO    = $(C_FLAGS) -shared -fPIC

OS           ?=$(shell uname -s)
IS_WIN       :=$(shell echo $(OS)|grep -i Windows)

# Environment variables used by source/public/swig/Makefile.swig
# You may change the default values or set environment variables.

#SWIG_TYPE: python, perl5, java, ruby, csharp, php, r (no space after =)
SWIG_TYPE      ?=python

PYTHON_INCLUDE ?=/usr/include/python2.7
PYTHON_LIBFILE ?=python2.7
PERL5_INCLUDE  ?=/usr/include/perl5
PERL5_LIBFILE  ?=perl5
JAVA_INCLUDE   ?=/Library/Java/Home/include
RUBY_INCLUDE   ?=/usr/include/ruby
RUBY_LIBFILE   ?=ruby

ifdef IS_WIN
EXE           =.exe
else
L_DL          =-ldl
endif
