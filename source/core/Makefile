# Makefile of projects in a package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) swig cleanswig
all:      $(SUBDIRS)

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

swig:
	@$(MAKE) -C x3manager/swig

clean:	$(CLEANSUBDIRS) cleanswig

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean

cleanswig:
	@$(MAKE) -C x3manager/swig clean
