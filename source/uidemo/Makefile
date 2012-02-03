# Makefile of projects in a package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public pltempl, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS)
all:      $(SUBDIRS)

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
