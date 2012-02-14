# Makefile of projects in this package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

SWIGS  =python perl5 java csharp ruby php lua r
.PHONY: $(SUBDIRS) swig $(SWIGS)

all:
# Nothing to do for the default target because no C++ plugin projects in this package.

swig:   $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@ swig

$(SWIGS):
	@export SWIG_TYPE=$@; $(MAKE) swig

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
