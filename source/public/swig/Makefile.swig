# Included by Makefile of swig project.
# x3py framework: https://github.com/rhcad/x3py

# SWIG_TYPE == ?
USE_PYTHON   :=$(shell echo $(SWIG_TYPE)|grep -i python)
USE_PERL     :=$(shell echo $(SWIG_TYPE)|grep -i perl)
USE_JAVA     :=$(shell echo $(SWIG_TYPE)|grep -i java)
USE_CSHARP   :=$(shell echo $(SWIG_TYPE)|grep -i csharp)
USE_RUBY     :=$(shell echo $(SWIG_TYPE)|grep -i ruby)

# The extension of the target file to compile.
ifdef IS_WIN
ifdef USE_PYTHON
SWIG_EXT      =.pyd
else
SWIG_EXT      =.dll
endif
else
SWIG_EXT      =.so
endif

# The prefix of the target file to compile.
ifdef USE_PYTHON
SWIG_PRE      =_
else
ifdef USE_CSHARP
SWIG_PRE      =_
endif
endif

ifdef USE_PYTHON
SWIG_INCLUDE ?=$(PYTHON_INCLUDE)
SWIG_LIBPATH :=$(PYTHON_LIB)
SWIG_LIBFILE :=$(PYTHON_LIBFILE)
SWIG_TESTEXT  =.py
WRAPTARGET    =$(PROJNAME).py
CPPFLAGS     += -DUSE_PYTHON
endif

ifdef USE_PERL
SWIG_INCLUDE ?=$(PERL5_INCLUDE)
SWIG_LIBPATH :=$(PERL5_LIB)
SWIG_LIBFILE :=$(PERL5_LIBFILE)
SWIG_TESTEXT  =.pl
WRAPTARGET    =$(PROJNAME).pm
CPPFLAGS     += -DUSE_PERL
endif

ifdef USE_JAVA
SWIG_INCLUDE ?=$(JAVA_INCLUDE)
SWIG_TESTEXT  =.java
WRAPTARGET    =$(PROJNAME).jar
CPPFLAGS     += -DUSE_JAVA
endif

ifdef USE_CSHARP
SWIG_TESTEXT  =.cs
WRAPTARGET    =$(PROJNAME)$(SWIG_EXT)
CPPFLAGS     += -DUSE_CSHARP
endif

ifdef USE_RUBY
SWIG_INCLUDE ?=$(RUBY_INCLUDE)
SWIG_LIBPATH :=$(RUBY_LIB)
SWIG_LIBFILE :=$(RUBY_LIBFILE)
SWIG_TESTEXT  =.rb
WRAPTARGET    =$(PROJNAME).rb
CPPFLAGS     += -DUSE_RUBY
endif

ifdef SWIG_INCLUDE
INCLUDES     += -I"$(SWIG_INCLUDE)"
endif
ifdef SWIG_LIBPATH
LIBS         += $(LIBPATHFLAG)"$(SWIG_LIBPATH)"
endif
ifdef SWIG_LIBFILE
LIBS         += $(LIBFLAG)$(SWIG_LIBFILE)$(LIBEND)
endif

ifdef USE_JAVA
SWIGTMP       =._$(SWIG_TYPE)
else
ifdef USE_CSHARP
SWIGTMP       =._$(SWIG_TYPE)
endif
endif

SWIG_TESTDIR ?=$(INSTALL_DIR)/$(SWIG_TYPE)
ifdef USE_PYTHON
SWIG_OUTDIR  ?=$(SWIG_TESTDIR)/$(PKGNAME)
else
SWIG_OUTDIR  ?=$(SWIG_TESTDIR)
endif

SWIG_CC       ="$(SWIG_BIN)swig" -c++ -$(SWIG_TYPE)
ifdef USE_CSHARP
SWIG_CC      += -namespace $(PKGNAME).$(PROJNAME) -dllimport _$(PROJNAME)
endif
ifdef SWIGTMP
SWIG_CC      += -outdir $(SWIGTMP)
else
SWIG_CC      += -outdir $(SWIG_OUTDIR)
endif

#------------------------------------------------
TARGET              =$(SWIG_PRE)$(PROJNAME)$(SWIG_EXT)
WRAPFILE            =$(PROJNAME)_$(SWIG_TYPE)_wrap
OBJS               +=$(WRAPFILE)$(OBJEXT)
TESTFILE           :=test$(PROJNAME)$(SWIG_TESTEXT)
REMOTE_TARGET       =$(SWIG_OUTDIR)/$(TARGET)
REMOTE_WRAPTARGET   =$(SWIG_OUTDIR)/$(WRAPTARGET)
REMOTE_TESTFILE    :=$(SWIG_TESTDIR)/$(TESTFILE)
HASTESTFILE         =(test -e $(TESTFILE))

.PHONY: swig clean $(TESTFILE)

all:
swig: $(REMOTE_TARGET) $(REMOTE_WRAPTARGET) $(REMOTE_TESTFILE)

$(REMOTE_TARGET): $(OBJS)
	-@test -d $(SWIG_TESTDIR) || mkdir $(SWIG_TESTDIR)
	-@test -d $(SWIG_OUTDIR) || mkdir $(SWIG_OUTDIR)
	$(LINK) $(LDFLAGS) $(OUTFLAG)$@ $(OBJS) $(LIBS)

%$(OBJEXT): %.cxx
	$(CPP) $(subst -Wall ,,$(subst -W4 ,,$(CPPFLAGS))) $(INCLUDES) -c $<

#------------------------------------------------

$(WRAPFILE).cxx: $(PROJNAME).i
	@echo --Making $(SWIG_TYPE) project $(PROJNAME)...
	-@test -d $(SWIG_TESTDIR) || mkdir $(SWIG_TESTDIR)
	-@test -d $(SWIG_OUTDIR) || mkdir $(SWIG_OUTDIR)
ifdef SWIGTMP
	-@test -d $(SWIGTMP) || mkdir $(SWIGTMP); rm -rf $(SWIGTMP)/*.*
endif
	$(SWIG_CC) -o $(WRAPFILE).cxx $(INCLUDES) $<
ifdef USE_PYTHON
	@test -e $(SWIG_OUTDIR)/__init__.py || echo "#empty" > $(SWIG_OUTDIR)/__init__.py
endif

#------------------------------------------------

$(REMOTE_WRAPTARGET): $(WRAPFILE).cxx
ifdef SWIGTMP
	@test -d $(SWIGTMP) || (rm -rf $(WRAPFILE).cxx; $(MAKE) $(WRAPFILE).cxx)
endif
ifdef USE_JAVA
	@cd $(SWIGTMP); "$(JAVA_BIN)javac" *.java; \
	    "$(JAVA_BIN)jar" cfM $(WRAPTARGET) *.class; \
	    cp -v $(WRAPTARGET) ../$(SWIG_OUTDIR)
endif
ifdef USE_CSHARP
	@cd $(SWIGTMP); "$(CSC_BIN)csc" -nologo -t:library -out:$(WRAPTARGET) *.cs; \
	    cp -v $(WRAPTARGET) ../$(SWIG_OUTDIR)
endif

#------------------------------------------------

$(TESTFILE):
ifdef SWIG_TESTEXT
	-@!$(HASTESTFILE) || cp -v $(TESTFILE) $(SWIG_TESTDIR)
endif

$(REMOTE_TESTFILE): $(REMOTE_WRAPTARGET) $(TESTFILE)
ifdef SWIG_TESTEXT
ifdef USE_JAVA
	@!$(HASTESTFILE) || (cd $(SWIG_TESTDIR); \
	    "$(JAVA_BIN)javac" -cp $(WRAPTARGET) $(TESTFILE))
endif
ifdef USE_CSHARP
	@!$(HASTESTFILE) || (cd $(SWIG_TESTDIR); \
	    "$(CSC_BIN)csc" -nologo -t:exe -r:$(WRAPTARGET) $(TESTFILE))
endif
endif #SWIG_TESTEXT

#------------------------------------------------

clean:
ifndef SWIG_TYPE
	rm -rf *.d *$(OBJEXT)  *_wrap.*  ._*
ifdef touch
	touch -c *
endif
else
	rm -rf *.d $(WRAPFILE)*  ._$(SWIG_TYPE)*
ifdef cleanall
	rm -rf $(REMOTE_TARGET) $(REMOTE_WRAPTARGET) $(REMOTE_TESTFILE)
endif
endif
