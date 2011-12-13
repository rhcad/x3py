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
IS_MACOSX    :=$(shell echo $(OS)|grep -i Darwin)

# Environment variables used by source/public/swig/Makefile.swig
# You may change the default values or set environment variables (must do this on Windows).

#SWIG_TYPE: python, perl5, java, ruby, php, r (no space after =)
SWIG_TYPE      ?=python

ifdef IS_MACOSX
PYTHON_INCLUDE ?=/usr/include/python2.6
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

ifdef IS_WIN
EXE           =.exe
else
L_DL          =-ldl
endif
