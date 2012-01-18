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

SWIGOUTDIR    =$(INSTALL_DIR)/$(SWIG_TYPE)
SWIGSO_FLAGS  =$(C_FLAGS_SO)
ifdef SWIG_LIBPATH
SWIGSO_FLAGS +=-L$(SWIG_LIBPATH)
endif
ifdef SWIG_LIBFILE
SWIGSO_FLAGS +=-l$(SWIG_LIBFILE)
endif

SWIGCC        =$(SWIG_BIN)swig -c++ -$(SWIG_TYPE) -I$(INTERFACE_DIR)/core
ifdef USE_JAVA
SWIGCC       += -outdir java
else
SWIGCC       += -outdir $(SWIGOUTDIR)
endif

SWIG_CFLAGS   =$(CFLAGS_SO) -I$(SWIG_INCLUDE)
ifdef PKGNAME
SWIGCC       += -I$(INTERFACE_DIR)/$(PKGNAME)
SWIG_CFLAGS  += -I$(INTERFACE_DIR)/$(PKGNAME)
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

TARGET   =$(SWIGOUTDIR)/$(SWIG_PRE)$(PROJNAME)$(SWIG_EXT)
WRAPFILE =$(PROJNAME)_$(SWIG_TYPE)_wrap

$(TARGET): $(WRAPFILE).cxx $(WRAPFILE).o
	-@test -d $(SWIGOUTDIR) || mkdir $(SWIGOUTDIR)
	$(CC) $(SWIGSO_FLAGS) -o $@ $(WRAPFILE).o $(L_DL)
ifdef SWIG_TESTEXT
	-@cp test$(PROJNAME)$(SWIG_TESTEXT) $(SWIGOUTDIR)
endif

$(WRAPFILE).cxx: $(PROJNAME).i
	-@test -d $(SWIGOUTDIR) || mkdir $(SWIGOUTDIR)
ifdef USE_JAVA
	-@test -d java || mkdir java
endif
	$(SWIGCC) -o $(WRAPFILE).cxx $<
ifdef USE_JAVA
	javac java/*.java
	cd java; jar cvfM ../$(SWIGOUTDIR)/$(PROJNAME).jar *.class
	rm -rf java/*.class
endif

$(WRAPFILE).o: $(WRAPFILE).cxx
	$(CC) $(SWIG_CFLAGS) -c $<

clean:
	rm -rf *.o  *_wrap.cxx *_wrap.h  java
ifdef cleanall
	rm -rf $(TARGET)
	rm -rf $(SWIGOUTDIR)python/$(PROJNAME).py* $(SWIGOUTDIR)python/$(SWIG_PRE)$(PROJNAME)$(SWIG_EXT)
	rm -rf $(SWIGOUTDIR)java/$(PROJNAME).jar $(SWIGOUTDIR)java/$(PROJNAME)$(SWIG_EXT)
endif
