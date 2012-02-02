ROOTDIR  =../../..
PKGNAME  =example
PROJNAME =libpln1
CPPFLAGS += -D_LIB

include $(ROOTDIR)/config.mk

TARGET   =$(PLUGINS_DIR)/$(PROJNAME).$(LIB)
SOURCES  =$(wildcard *.cpp)
OBJS     =$(SOURCES:.cpp=.$(OBJ))

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS)$@ $(OBJS)

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
