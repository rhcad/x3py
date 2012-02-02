ROOTDIR  =../../..
PROJNAME =x3manager

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).pln
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.$(OBJ))

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
