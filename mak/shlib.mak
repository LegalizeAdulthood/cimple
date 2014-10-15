TARGET = $(call shlib_target,$(SH_LIBRARY))

$(TARGET): $(OBJECTS)
	$(MKDIRHIER) $(LIB)
	$(call make_shlib,$(SH_LIBRARY),$(OBJECTS),$(LIBRARIES))

size:
	$(SIZE) $(TARGET)

gen:

load:
	$(BIN)/dlopen $(TARGET)

_TARGET_LIST = $(call shlib_clean_targets,$(SH_LIBRARY))

clean:
	$(RM) $(OBJECTS) $(_TARGET_LIST) $(CLEAN) depend.mak

include $(TOP)/mak/sub.mak
