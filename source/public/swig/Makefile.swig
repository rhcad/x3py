# Included by Makefile of swig project.

USE_PYTHON   :=$(shell echo $(SWIG_TYPE)|grep -i python)
USE_PERL     :=$(shell echo $(SWIG_TYPE)|grep -i perl)
USE_JAVA     :=$(shell echo $(SWIG_TYPE)|grep -i java)
USE_RUBY     :=$(shell echo $(SWIG_TYPE)|grep -i ruby)

ifdef USE_PYTHON
SWIG_INCLUDE ?=$(PYTHON_INCLUDE)
SWIG_LIBPATH :=$(PYTHON_LIB)
SWIG_LIBFILE :=$(PYTHON_LIBFILE)
endif

ifdef USE_PERL
SWIG_INCLUDE ?=$(PERL5_INCLUDE)
SWIG_LIBPATH :=$(PERL5_LIB)
SWIG_LIBFILE :=$(PERL5_LIBFILE)
endif

ifdef USE_JAVA
SWIG_INCLUDE ?=$(JAVA_INCLUDE)
endif

ifdef USE_RUBY
SWIG_INCLUDE ?=$(RUBY_INCLUDE)
SWIG_LIBPATH :=$(RUBY_LIB)
SWIG_LIBFILE :=$(RUBY_LIBFILE)
endif

SWIGSO_FLAGS  =$(C_FLAGS_SO)
ifdef USE_JAVA
SWIGOUTDIR    =$(INSTALL_DIR)/$(SWIG_TYPE)_$(PROJNAME)
else
SWIGOUTDIR    =$(INSTALL_DIR)/$(SWIG_TYPE)
ifdef SWIG_LIBPATH
SWIGSO_FLAGS +=-L$(SWIG_LIBPATH)
endif
ifdef SWIG_LIBFILE
SWIGSO_FLAGS +=-l$(SWIG_LIBFILE)
else
SWIGSO_FLAGS +=-l$(SWIG_TYPE)
endif
endif

SWIGCC        =$(SWIG_BIN)swig -c++ -$(SWIG_TYPE) -I$(INTERFACE_DIR)/core -outdir $(SWIGOUTDIR)
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
	$(CC) $(SWIGSO_FLAGS) -o $@ $(WRAPFILE).o $(L_DL)
ifdef USE_PYTHON
	-@cp test$(PROJNAME).py $(SWIGOUTDIR)
endif
ifdef USE_JAVA
	javac $(SWIGOUTDIR)/*.java
endif

$(WRAPFILE).cxx: $(PROJNAME).i
	-@mkdir $(SWIGOUTDIR)
	$(SWIGCC) -o $(WRAPFILE).cxx $<

$(WRAPFILE).o: $(WRAPFILE).cxx
	$(CC) $(SWIG_CFLAGS) -c $<

clean:
	rm -rf *.o
	rm -rf *_wrap.cxx
	rm -rf *_wrap.h
	rm -rf $(TARGET)
	rm -rf $(SWIGOUTDIR)/$(PROJNAME).py*
	rm -rf $(SWIGOUTDIR)/test$(PROJNAME).py
	rm -rf $(SWIGOUTDIR)/$(PROJNAME).pm
	rm -rf $(SWIGOUTDIR)/*.java
	rm -rf $(SWIGOUTDIR)/*.class
