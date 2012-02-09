# Makefile of projects in this package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY: $(SUBDIRS) swig python perl5 java ruby php r

all:
# Nothing to do for the default target because no C++ plugin projects in this package.

swig:   $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

python perl5 java ruby php r:
	@export SWIG_TYPE=$@; $(MAKE) swig

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
