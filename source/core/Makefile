# Makefile

ROOTDIR = ../..
include $(ROOTDIR)/config.mk

.PHONY:   x3manager swig cleanswig
all:      x3manager
SUBDIRS = x3manager
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

swig:
	@echo --Making all swig projects in subdirectory $@...
	@$(MAKE) -C x3manager/swig

clean:	$(CLEANSUBDIRS) cleanswig

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
cleanswig:
	@$(MAKE) -C x3manager/swig clean
