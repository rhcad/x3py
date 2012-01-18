ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = pltempl

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

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
