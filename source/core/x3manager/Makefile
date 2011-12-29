ROOTDIR  = ../../..
PROJNAME = x3manager

include $(ROOTDIR)/config.mk

TARGET   = $(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS_SO) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -MF $@

include $(SOURCES:.cpp=.d)
CPPFLAGS = $(CFLAGS_SO)

clean:
	rm -rf *.d *.o
	rm -rf $(TARGET)
