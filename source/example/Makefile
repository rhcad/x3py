# Makefile of projects in a package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public pltempl, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) swig cleanswig
all:      $(SUBDIRS)

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

swig:
	@$(MAKE) -C plsimple/swig
	@$(MAKE) -C observerex/swig

clean:	$(CLEANSUBDIRS) cleanswig

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean

cleanswig:
	@$(MAKE) -C plsimple/swig clean
	@$(MAKE) -C observerex/swig clean
