##==============================================================================
##
## Fix up variables containing library names with the CIMPLE_LIBRARY_PREFIX and
## CIMPLE_LIBRARY_SUFFIX.
##
##==============================================================================

ifdef STATIC_LIBRARY
  _STATIC_LIBRARY = \
    $(CIMPLE_LIBRARY_PREFIX)$(STATIC_LIBRARY)$(CIMPLE_LIBRARY_SUFFIX)
endif

ifdef SHARED_LIBRARY
  _SHARED_LIBRARY = \
    $(CIMPLE_LIBRARY_PREFIX)$(SHARED_LIBRARY)$(CIMPLE_LIBRARY_SUFFIX)
endif

_LIBRARIES = \
  $(foreach i,$(LIBRARIES),$(CIMPLE_LIBRARY_PREFIX)$i$(CIMPLE_LIBRARY_SUFFIX))

##==============================================================================

ifneq ("$(_SHARED_LIBRARY)$(_STATIC_LIBRARY)","")
  _OBJECTS = $(SOURCES:.cpp=$(OBJ))
  OBJECTS = $(_OBJECTS:.c=$(OBJ))
  include $(TOP)/mak/lib.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
endif

ifdef BINARY
  _OBJECTS = $(SOURCES:.cpp=$(OBJ))
  OBJECTS = $(_OBJECTS:.c=$(OBJ))
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
