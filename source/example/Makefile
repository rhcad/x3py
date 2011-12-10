# Makefile of projects in a package

ROOTDIR = ../..
include $(ROOTDIR)/config.mk

.PHONY:   consoledemo  libpln1  libpln2  libspln  observerex  plsimple  swig cleanswig
all:      consoledemo  libpln1  libpln2  libspln  observerex  plsimple
SUBDIRS = consoledemo  libpln1  libpln2  libspln  observerex  plsimple
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

swig:
	@echo --Making all swig projects in subdirectory $@...
	@$(MAKE) -C plsimple/swig
	@$(MAKE) -C observerex/swig

clean:	$(CLEANSUBDIRS) cleanswig

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
cleanswig:
	@$(MAKE) -C plsimple/swig clean
	@$(MAKE) -C observerex/swig clean
