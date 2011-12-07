# Included by Makefile. You can customize it.

INTERFACE_DIR =$(ROOTDIR)/interface

INSTALL_DIR   =$(ROOTDIR)/build
PLUGINS_DIR   =$(INSTALL_DIR)/plugins

CC            = g++
CFLAGS       += -g -I$(INTERFACE_DIR)
C_FLAGS      += -g -Wall

CFLAGS_SO     = $(CFLAGS) -fPIC -D_USRDLL
C_FLAGS_SO    = $(C_FLAGS) -shared -fPIC

#SWIG_TYPE: python, perl5, java, ruby (no space after =)
SWIG_TYPE    ?=python

# Environment variables used by source/swig/Makefile.swig
PYTHON_INCLUDE ?=/usr/include/python2.6
PYTHON_LIB     ?=/usr/lib
PERL5_INCLUDE  ?=/usr/include/perl5
PERL5_LIB      ?=perl5.a
JAVA_INCLUDE   ?=/Library/Java/Home/include
RUBY_INCLUDE   ?=/usr/include/ruby
RUBY_LIB       ?=ruby.a

OS           ?=$(shell uname -s)
IS_WIN       :=$(shell echo $(OS)|grep -i Windows)

ifdef IS_WIN
EXE           =.exe
else
L_DL          =-ldl
endif
