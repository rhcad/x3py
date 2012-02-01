ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =pltempl

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.o)

$(TARGET): $(OBJS)
	$(LINK) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.d: %.cpp
	$(CC) -MM $(CPPFLAGS) $< -MF $@

ifndef clean
include $(SOURCES:.cpp=.d)
endif

clean:
	rm -rf *.d *.o
ifdef cleanall
	rm -rf $(TARGET)
endif
