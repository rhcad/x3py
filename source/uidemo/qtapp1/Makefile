ROOTDIR  =../../..
PROJNAME =qtapp1
APPTYPE  =qt

include $(ROOTDIR)/config.mk

TARGET   =$(INSTALL_DIR)/$(PROJNAME)$(APPEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

INCLUDES += -I$(INTERFACE_DIR)/example \
            -I"$(QTDIR)/include"

LIBS     += $(LIBPATHFLAG)"$(QTDIR)/lib" \
            $(LIBFLAG)QtCore4$(LIBEND) \
            $(LIBFLAG)QtGui4$(LIBEND)

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
