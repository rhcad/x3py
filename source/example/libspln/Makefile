ROOTDIR  = ../../..
PKGNAME  = example
PROJNAME = libspln

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o) $(PLUGINS_DIR)/libpln1.a $(PLUGINS_DIR)/libpln2.a
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL) -L $(PLUGINS_DIR) -lpln1 -lpln2

module.o: module.cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -c $<
$(PROJNAME).o: $(PROJNAME).cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -c $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
