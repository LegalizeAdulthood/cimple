BINARY_TARGET = $(call bin_target,$(BINARY))

$(BINARY_TARGET): $(OBJECTS) $(BIN_DIR)/target
	$(call make_bin,$(BINARY),$(OBJECTS),$(LIBRARIES))

size:
	$(SIZE) $(BINARY_TARGET)

gen:

include $(TOP)/mak/sub.mak

clean:
	$(RM) $(OBJECTS) $(BINARY_TARGET) $(CLEAN) depend.mak
