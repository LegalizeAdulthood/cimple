TARGET = $(call lib_target,$(LIBRARY))

$(TARGET): $(OBJECTS) $(LIB_DIR)/target
	$(call make_lib,$(TARGET),$(OBJECTS))

size:
	size $(TARGET)

gen:

clean:
	$(RM) $(OBJECTS) $(TARGET) $(CLEAN) depend.mak

clean_target:
	$(RM) $(TARGET)

include $(TOP)/mak/sub.mak
