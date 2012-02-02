ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =consoledemo
APPTYPE  =console

include $(ROOTDIR)/config.mk

TARGET   =$(INSTALL_DIR)/$(PROJNAME)$(APPEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

CPPFLAGS += -DCONSOLE

$(TARGET): $(OBJS)
	$(LINK) $(LDFLAGS) $(OUTFLAG)$@ $(OBJS) $(LIBS)

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
