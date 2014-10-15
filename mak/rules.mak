
ifdef LIBRARY
  OBJECTS = $(SOURCES:.cpp=$(OBJ))
  include $(TOP)/mak/lib.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
endif

ifdef SH_LIBRARY
  OBJECTS = $(SOURCES:.cpp=$(OBJ))
  include $(TOP)/mak/shlib.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
endif

ifdef BINARY
  OBJECTS = $(SOURCES:.cpp=$(OBJ))
  include $(TOP)/mak/bin.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
endif

ifdef DIRS
  include $(TOP)/mak/dir.mak
endif

$(BIN)/target:
	$(MKDIRHIER) $(BIN)
	$(TOUCH) $(BIN)/target

$(LIB)/target:
	$(MKDIRHIER) $(LIB)
	$(MKDIRHIER) $(LIB)
	$(TOUCH) $(LIB)/target
