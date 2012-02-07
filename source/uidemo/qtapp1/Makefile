ROOTDIR  =../../..
PROJNAME =qtapp1
APPTYPE  =qt

include $(ROOTDIR)/config.mk

TARGET   =$(INSTALL_DIR)/$(PROJNAME)$(APPEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=$(OBJEXT))

ifdef QT4_INCLUDE

INCLUDES += -I$(INTERFACE_DIR)/example \
            -I"$(QT4_INCLUDE)" \
            -I"$(QT4_INCLUDE)/QtGui"

ifdef IS_WIN
QTLIB_EXT =4$(LIBEND)
else
QTLIB_EXT =$(LIBEND)
endif

LIBS     += $(LIBPATHFLAG)"$(QT4_LIB)" \
            $(LIBFLAG)QtCore$(QTLIB_EXT) \
            $(LIBFLAG)QtGui$(QTLIB_EXT)

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

endif #QT4_INCLUDE

clean:
	rm -rf *.d *.o *.obj
ifdef cleanall
	rm -rf $(TARGET)
endif
