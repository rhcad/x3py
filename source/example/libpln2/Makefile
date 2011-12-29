ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libpln2

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).a
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCES:.cpp=.o)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

include $(SOURCES:.cpp=.d)
CPPFLAGS = $(CFLAGS_SO) -D_LIB -Wno-unused

clean:
	rm -rf *.d *.o
	rm -rf $(TARGET)
