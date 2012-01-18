# Makefile of packages

ROOTDIR = ..
include $(ROOTDIR)/config.mk

.PHONY:   core example swig
all:      core example
SUBDIRS = core example
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

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
