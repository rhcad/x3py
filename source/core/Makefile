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
	@ ! test -e $@/Makefile || $(MAKE) -C $@

swig:   $(SWIGSUBDIRS)

$(SWIGSUBDIRS):
	@!(test -d $(basename $@)/swig) || $(MAKE) -C $(basename $@)/swig swig
	@!(test -e $(basename $@)/$(basename $@).i) || $(MAKE) -C $(basename $@) swig

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@!(test -e $(basename $@)/Makefile) || $(MAKE) -C $(basename $@) clean
	@!(test -d $(basename $@)/swig) || $(MAKE) -C $(basename $@)/swig clean
