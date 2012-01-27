# Makefile of packages

ROOTDIR =..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) swig
all:      $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

swig:
	@$(MAKE) -C core swig
	@$(MAKE) -C example swig
	@$(MAKE) -C public/swigtest

clean:	$(CLEANSUBDIRS)
	@$(MAKE) -C public/swigtest clean

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
