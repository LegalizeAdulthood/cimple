
ifneq ("$(SHARED_LIBRARY)$(STATIC_LIBRARY)","")
  OBJECTS = $(SOURCES:.cpp=$(OBJ))
  include $(TOP)/mak/lib.mak
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

$(BIN_DIR)/target:
	$(MKDIRHIER) $(BIN_DIR)
	$(TOUCH) $(BIN_DIR)/target

$(LIB_DIR)/target:
	$(MKDIRHIER) $(LIB_DIR)
	$(MKDIRHIER) $(LIB_DIR)
	$(TOUCH) $(LIB_DIR)/target
