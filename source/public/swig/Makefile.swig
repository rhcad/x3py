# Included by Makefile of swig project.

USE_PYTHON   :=$(shell echo $(SWIG_TYPE)|grep -i python)
USE_PERL     :=$(shell echo $(SWIG_TYPE)|grep -i perl)
USE_JAVA     :=$(shell echo $(SWIG_TYPE)|grep -i java)
USE_RUBY     :=$(shell echo $(SWIG_TYPE)|grep -i ruby)

ifdef USE_PYTHON
SWIG_INCLUDE ?=$(PYTHON_INCLUDE)
SWIG_LIBPATH :=$(PYTHON_LIB)
SWIG_LIBFILE :=$(PYTHON_LIBFILE)
SWIG_TESTEXT :=.py
endif

ifdef USE_PERL
SWIG_INCLUDE ?=$(PERL5_INCLUDE)
SWIG_LIBPATH :=$(PERL5_LIB)
SWIG_LIBFILE :=$(PERL5_LIBFILE)
SWIG_TESTEXT :=.pm
endif

ifdef USE_JAVA
SWIG_INCLUDE ?=$(JAVA_INCLUDE)
SWIG_TESTEXT :=.java
endif

ifdef USE_RUBY
SWIG_INCLUDE ?=$(RUBY_INCLUDE)
SWIG_LIBPATH :=$(RUBY_LIB)
SWIG_LIBFILE :=$(RUBY_LIBFILE)
endif

SWIG_OUTDIR   =$(INSTALL_DIR)/$(SWIG_TYPE)

ifdef SWIG_LIBPATH
LIBS         += $(LIBPATHFLAG)"$(SWIG_LIBPATH)"
endif
ifdef SWIG_LIBFILE
LIBS         += $(LIBFLAG)$(SWIG_LIBFILE)$(LIBEND)
endif
INCLUDES     += -I"$(SWIG_INCLUDE)"

SWIG_CC       ="$(SWIG_BIN)swig" -c++ -$(SWIG_TYPE)
ifdef USE_JAVA
SWIG_CC      += -outdir java
else
SWIG_CC      += -outdir $(SWIG_OUTDIR)
endif

ifdef USE_PYTHON
SWIG_PRE      =_
endif

ifdef IS_WIN
ifdef USE_PYTHON
SWIG_EXT      =.pyd
else
SWIG_EXT      =.dll
endif
else
SWIG_EXT      =.so
endif

#------------------------------------------

TARGET   =$(SWIG_OUTDIR)/$(SWIG_PRE)$(PROJNAME)$(SWIG_EXT)
WRAPFILE =$(PROJNAME)_$(SWIG_TYPE)_wrap
TESTFILE :=test$(PROJNAME)$(SWIG_TESTEXT)
OBJS     =$(WRAPFILE)$(OBJEXT)

$(TARGET): $(WRAPFILE).cxx $(OBJS)
	-@test -d $(SWIG_OUTDIR) || mkdir $(SWIG_OUTDIR)
	$(LINK) $(LDFLAGS) $(OUTFLAG)$@ $(OBJS) $(LIBS)

$(WRAPFILE).cxx: $(PROJNAME).i
	@echo --Making $(SWIG_TYPE) project $(PROJNAME)...
	-@test -d $(SWIG_OUTDIR) || mkdir $(SWIG_OUTDIR)
ifdef USE_JAVA
	-@test -d java || mkdir java
endif
	$(SWIG_CC) -o $(WRAPFILE).cxx $(INCLUDES) $<
ifdef SWIG_TESTEXT
	-@!(test -e $(TESTFILE)) || cp $(TESTFILE) $(SWIG_OUTDIR)
endif
ifdef USE_JAVA
	"$(JAVA_BIN)javac" java/*.java
	cd java; "$(JAVA_BIN)jar" cvfM ../$(SWIG_OUTDIR)/$(PROJNAME).jar *.class
	@rm -rf java/*.class
	@!(test -e $(TESTFILE)) || "$(JAVA_BIN)javac" -cp $(SWIG_OUTDIR)/$(PROJNAME).jar $(SWIG_OUTDIR)/$(TESTFILE)
endif

$(WRAPFILE)$(OBJEXT): $(WRAPFILE).cxx
	$(CPP) $(subst -Wall ,,$(subst -W4 ,,$(CPPFLAGS))) $(INCLUDES) -c $<

clean:
	rm -rf *$(OBJEXT)  *_wrap.cxx *_wrap.h  java
ifdef cleanall
	rm -rf $(TARGET)
	rm -rf $(SWIG_OUTDIR)python/$(PROJNAME).py* $(SWIG_OUTDIR)python/$(SWIG_PRE)$(PROJNAME)$(SWIG_EXT)
	rm -rf $(SWIG_OUTDIR)java/$(PROJNAME).jar $(SWIG_OUTDIR)java/$(PROJNAME)$(SWIG_EXT)
endif
