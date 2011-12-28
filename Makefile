# The simplest way to compile x3c on Linux, Mac OS X or Unix is:
# 1. `cd' to the directory containing the file of 'Makefile'.
# 2. Type `make' to compile the package.
#    The program binaries files are outputed to './build/bin'.
# 
# 3. You can remove the program object files from the source code
#    directory by typing `make clean'.
#

ROOTDIR = .
include $(ROOTDIR)/config.mk

.PHONY:	source swig clean python perl5 java ruby php r

#==============================================================================
# The default build target.
#==============================================================================
all:	source

source:
	@test -d build || mkdir build
	@test -d $(PLUGINS_DIR) || mkdir $(PLUGINS_DIR)
	@$(MAKE) -C source

swig:
	@test -d build || mkdir build
	@$(MAKE) -C source swig

python perl5 java ruby php r:
	@test -d build || mkdir build
	export SWIG_TYPE=$@; $(MAKE) -C source swig

#==============================================================================
# Clean up the targets built by 'make all'.
#==============================================================================
clean:
	@$(MAKE) -C source clean
