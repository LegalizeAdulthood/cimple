STATIC_LIBRARY_TARGET = $(call static_library_target,$(STATIC_LIBRARY))
SHARED_LIBRARY_TARGET = $(call shared_library_target,$(SHARED_LIBRARY))

ifdef STATIC_LIBRARY
    DEPENDENCIES += $(STATIC_LIBRARY_TARGET)
endif

ifdef SHARED_LIBRARY
    DEPENDENCIES += $(SHARED_LIBRARY_TARGET)
endif

all: $(DEPENDENCIES)
ifdef SHARED_LIBRARY
	@ echo "$(SHARED_LIBRARY_TARGET) is up to date"
endif
ifdef STATIC_LIBRARY
	@ echo "$(STATIC_LIBRARY_TARGET) is up to date"
endif

$(STATIC_LIBRARY_TARGET): $(OBJECTS)
	$(MKDIRHIER) $(LIB_DIR)
	$(call make_lib,$(STATIC_LIBRARY_TARGET),$(OBJECTS))

$(SHARED_LIBRARY_TARGET): $(OBJECTS)
	$(MKDIRHIER) $(LIB_DIR)
	$(call make_shlib,$(SHARED_LIBRARY),$(OBJECTS),$(LIBRARIES))


size:
	size $(SHARED_LIBRARY_TARGET)

CLEAN += $(call shlib_clean_targets,$(SHARED_LIBRARY))
CLEAN += $(OBJECTS)
CLEAN += $(STATIC_LIBRARY_TARGET)
CLEAN += depend.mak

clean:
	$(RM) $(CLEAN)

gen:

include $(TOP)/mak/sub.mak
