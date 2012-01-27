ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =pltempl

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(LNKFLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(LIBS)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

ifndef clean
include $(SOURCES:.cpp=.d)
endif
CPPFLAGS =$(CFLAGS_SO)

clean:
	rm -rf *.d *.o
ifdef cleanall
	rm -rf $(TARGET)
endif
