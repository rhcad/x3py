# The simplest way to compile x3c on Linux, Mac OS X or Unix is:
# 1. `cd' to the directory containing the file of 'Makefile'.
# 2. Type `make' to compile C++ plugins.
#    The program binaries files are outputed to './build/plugins'.
# 
# 3. Type `make all python' to compile C++ plugins and swig projects.
#    The swig projects binaries files are outputed to './build/python'.
# 
# 4. You can remove the program object files from the source code
#    directory by typing `make clean'.
#

ROOTDIR =.
include $(ROOTDIR)/config.mk

.PHONY:	source clean cleanall python perl5 java ruby php r

#==============================================================================
# The default build target.
#==============================================================================
all:	source

source:
	@test -d $(INSTALL_DIR) || mkdir $(INSTALL_DIR)
	@test -d $(PLUGINS_DIR) || mkdir $(PLUGINS_DIR)
	@$(MAKE) -C source

python perl5 java ruby php r:
	@test -d $(INSTALL_DIR) || mkdir $(INSTALL_DIR)
	@export SWIG_TYPE=$@; $(MAKE) -C source swig

#==============================================================================
# Clean up the targets built by 'make all'.
#==============================================================================
clean:
	@export clean=1; $(MAKE) -C source clean
cleanall:
	@export cleanall=1; $(MAKE) clean
