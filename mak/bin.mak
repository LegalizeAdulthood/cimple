TARGET = $(call bin_target,$(BINARY))

$(TARGET): $(OBJECTS) $(BIN_DIR)/target
	$(call make_bin,$(BINARY),$(OBJECTS),$(LIBRARIES))

size:
	$(SIZE) $(TARGET)

gen:

include $(TOP)/mak/sub.mak

clean:
	$(RM) $(OBJECTS) $(TARGET) $(CLEAN) depend.mak
