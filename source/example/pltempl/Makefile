ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =pltempl

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

all:       $(TARGET)
$(TARGET): $(OBJS)
	$(LINK) $(LDFLAGS) $(OUTFLAG)$@ $(OBJS) $(LIBS)

%.d: %.cpp
	$(DEPEND_CC) $@ $(INCLUDES) $<
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
