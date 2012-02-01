ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libpln2

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).a
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.o)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

%.d: %.cpp
	$(CC) -MM $(CPPFLAGS) $< -MF $@

ifndef clean
include $(SOURCES:.cpp=.d)
endif
CPPFLAGS += -D_LIB

clean:
	rm -rf *.d *.o
ifdef cleanall
	rm -rf $(TARGET)
endif
