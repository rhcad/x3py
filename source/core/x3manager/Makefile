ROOTDIR  = ../../..
include $(ROOTDIR)/config.mk

PROJNAME = x3manager
TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

module.o: module.cpp plugins.h
	$(CC) $(CFLAGS_SO) -c $<
plugins.o: plugins.cpp plugins.h
	$(CC) $(CFLAGS_SO) -c $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
