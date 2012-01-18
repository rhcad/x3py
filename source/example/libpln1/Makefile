ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libpln1

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).a
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCES:.cpp=.o)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

ifndef clean
include $(SOURCES:.cpp=.d)
endif
CPPFLAGS = $(CFLAGS_SO) -D_LIB -Wno-unused

clean:
	rm -rf *.d *.o
ifdef cleanall
	rm -rf $(TARGET)
endif
