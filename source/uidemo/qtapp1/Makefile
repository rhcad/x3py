ROOTDIR  =../../..
PROJNAME =qtapp1
APPTYPE  =qt

include $(ROOTDIR)/config.mk

TARGET   =$(INSTALL_DIR)/$(PROJNAME)$(APPEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

ifdef QTDIR

INCLUDES += -I$(INTERFACE_DIR)/example \
            -I"$(QTDIR)/include" \
            -I"$(QTDIR)/include/QtGui"

LIBS     += $(LIBPATHFLAG)"$(QTDIR)/lib" \
            $(LIBFLAG)QtCore4$(LIBEND) \
            $(LIBFLAG)QtGui4$(LIBEND)

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

endif #QTDIR

clean:
	rm -rf *.d *.o *.obj
ifdef cleanall
	rm -rf $(TARGET)
endif
