ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libspln

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o) $(PLUGINS_DIR)/libpln1.a $(PLUGINS_DIR)/libpln2.a
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL) -L $(PLUGINS_DIR) -lpln1 -lpln2

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

include $(SOURCES:.cpp=.d)
CPPFLAGS = $(CFLAGS_SO)

clean:
	rm -rf *.d *.o
	rm -rf $(TARGET)
