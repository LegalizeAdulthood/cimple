STATIC_LIBRARY_TARGET = $(call static_library_target,$(_STATIC_LIBRARY))
SHARED_LIBRARY_TARGET = $(call shared_library_target,$(_SHARED_LIBRARY))

ifdef _STATIC_LIBRARY
    DEPENDENCIES += $(STATIC_LIBRARY_TARGET)
endif

ifdef _SHARED_LIBRARY
    DEPENDENCIES += $(SHARED_LIBRARY_TARGET)
endif

all: $(DEPENDENCIES)
ifdef _SHARED_LIBRARY
	@ echo "$(SHARED_LIBRARY_TARGET) is up to date"
endif
ifdef _STATIC_LIBRARY
	@ echo "$(STATIC_LIBRARY_TARGET) is up to date"
endif

$(STATIC_LIBRARY_TARGET): $(OBJECTS)
	$(MKDIRHIER) $(LIB_DIR)
	$(call make_lib,$(STATIC_LIBRARY_TARGET),$(OBJECTS))

$(SHARED_LIBRARY_TARGET): $(OBJECTS)
	$(MKDIRHIER) $(LIB_DIR)
	$(call make_shlib,$(_SHARED_LIBRARY),$(OBJECTS),$(_LIBRARIES))


size:
	size $(SHARED_LIBRARY_TARGET)

CLEAN += $(call shlib_clean_targets,$(_SHARED_LIBRARY))
CLEAN += $(OBJECTS)
CLEAN += $(STATIC_LIBRARY_TARGET)
CLEAN += depend.mak

clean: 
	$(RM) $(CLEAN)

gen:

include $(TOP)/mak/sub.mak
