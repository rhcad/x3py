ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libpln2

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).a
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCES:.cpp=.o)

%.d: %.cpp
	$(CC) -MM $(CFLAGS_SO) $< -MF $@
	@echo -e "\t$(CC) $(CFLAGS_SO) -c $<" >> $@

include $(SOURCES:.cpp=.d)

clean:
	rm -rf *.d *.o
	rm -rf $(TARGET)
