ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libspln

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o) $(PLUGINS_DIR)/libpln1.a $(PLUGINS_DIR)/libpln2.a
	$(CC) $(LNKFLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(LIBS) -L $(PLUGINS_DIR) -lpln1 -lpln2

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
