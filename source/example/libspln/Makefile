ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libspln

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.$(OBJ))

LIBS    += $(LIBPATHFLAG)$(PLUGINS_DIR) \
           $(LIBFLAG)$(LIBPRE)pln1$(LIBEND) \
           $(LIBFLAG)$(LIBPRE)pln2$(LIBEND)

$(TARGET): $(OBJS) $(PLUGINS_DIR)/libpln1.$(LIB) $(PLUGINS_DIR)/libpln2.$(LIB)
	$(LINK) $(LDFLAGS) $(OUTFLAG)$@ $(OBJS) $(LIBS)

%.d: %.cpp
	g++ -MM $(INCLUDES) $< -MF $@
%.$(OBJ): %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $<

ifndef clean
include $(SOURCES:.cpp=.d)
endif

clean:
	rm -rf *.d *.$(OBJ)
ifdef cleanall
	rm -rf $(TARGET)
endif
