ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = consoledemo

include $(ROOTDIR)/config.mk

TARGET   = $(INSTALL_DIR)/$(PROJNAME)$(EXE)
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

ifndef clean
include $(SOURCES:.cpp=.d)
endif
CPPFLAGS = $(CFLAGS_SO)

clean:
	rm -rf *.d *.o
ifdef cleanall
	rm -rf $(TARGET)
endif
