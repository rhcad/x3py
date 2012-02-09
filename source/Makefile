# Makefile of packages

ROOTDIR =..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
SWIGSUBDIRS  =$(addsuffix .swig, $(SUBDIRS))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) $(SWIGSUBDIRS) swig
all:      $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

swig:   $(SWIGSUBDIRS)

$(SWIGSUBDIRS):
	@$(MAKE) -C $(basename $@) swig

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@$(MAKE) -C $(basename $@) clean
