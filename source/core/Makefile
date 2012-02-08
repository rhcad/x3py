# Makefile of projects in this package

ROOTDIR =../..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
SWIGSUBDIRS  =$(addsuffix .swig, $(SUBDIRS))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) $(SWIGSUBDIRS) swig
all:      $(SUBDIRS)

$(SUBDIRS):
	@echo --Making project $@...
	@$(MAKE) -C $@

swig:   $(SWIGSUBDIRS)

$(SWIGSUBDIRS):
	@!(test -d $(basename $@)/swig) || $(MAKE) -C $(basename $@)/swig

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
	@!(test -d $(basename $@)/swig) || $(MAKE) -C $(basename $@)/swig clean
