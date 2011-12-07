ROOTDIR  = ../../..
include $(ROOTDIR)/config.mk

PROJNAME = consoledemo
TARGET   = $(INSTALL_DIR)/$(PROJNAME)$(EXE)
SOURCES  = $(wildcard *.cpp)

$(TARGET): $(SOURCES:.cpp=.o)
	$(CC) $(C_FLAGS) -o $@ $(SOURCES:.cpp=.o) $(L_DL)

main.o: main.cpp
	$(CC) $(CFLAGS) -D_CONSOLE -c $<

clean:
	rm -rf *.o
	rm -rf $(TARGET)
