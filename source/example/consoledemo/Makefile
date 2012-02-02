ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =consoledemo
EXETYPE  =console

include $(ROOTDIR)/config.mk

TARGET   =$(INSTALL_DIR)/$(PROJNAME)$(APPEXT)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.$(OBJ))

CPPFLAGS += -DCONSOLE

$(TARGET): $(OBJS)
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
