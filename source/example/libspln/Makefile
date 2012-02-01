ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libspln

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.o)

LIBS    += -L $(PLUGINS_DIR) -lpln1 -lpln2

$(TARGET): $(OBJS) $(PLUGINS_DIR)/libpln1.a $(PLUGINS_DIR)/libpln2.a
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
