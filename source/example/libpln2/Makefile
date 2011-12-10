ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libpln2

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).a
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCES:.cpp=.o)

module.o: module.cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -D _LIB -c $<
$(PROJNAME).o: $(PROJNAME).cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -D _LIB -c $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
