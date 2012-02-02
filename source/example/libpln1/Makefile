ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libpln1
CPPFLAGS += -D_LIB

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME)$(LIBEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS)$@ $(OBJS)

%.d: %.cpp
	g++ -MM $(INCLUDES) $< -MF $@
%$(OBJEXT): %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $<

ifndef clean
include $(SOURCES:.cpp=.d)
endif

clean:
	rm -rf *.d *.o *.obj
ifdef cleanall
	rm -rf $(TARGET)
endif
