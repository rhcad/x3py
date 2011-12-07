ROOTDIR  = ../../..
include $(ROOTDIR)/config.mk

PROJNAME = plsimple
TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

module.o: module.cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -c $<
$(PROJNAME).o: $(PROJNAME).cpp $(PROJNAME).h
	$(CC) $(CFLAGS_SO) -c $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
