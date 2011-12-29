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

include $(SOURCES:.cpp=.d)
CPPFLAGS = $(CFLAGS_SO)

clean:
	rm -rf *.d *.o
	rm -rf $(TARGET)
