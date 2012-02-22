# Makefile of packages

ROOTDIR =..
include $(ROOTDIR)/config.mk

SUBDIRS =$(filter-out public, $(subst /,,$(dir $(wildcard */))))
SWIGSUBDIRS  =$(addsuffix .swig, $(SUBDIRS))
CLEANSUBDIRS =$(addsuffix .clean, $(SUBDIRS))

.PHONY:   $(SUBDIRS) $(SWIGSUBDIRS) swig
all:      $(SUBDIRS)

$(SUBDIRS):
	@ ! test -e $@/Makefile || $(MAKE) -C $@

swig:   $(SWIGSUBDIRS)

$(SWIGSUBDIRS):
	@$(MAKE) -C $(basename $@) swig

clean:	$(CLEANSUBDIRS)
ifdef touch
	touch -c *
endif

$(CLEANSUBDIRS):
	@!(test -e $(basename $@)/Makefile) || $(MAKE) -C $(basename $@) clean
ifdef touch
	touch -c $(basename $@)/*
endif
