##==============================================================================
##
## target:
##
##==============================================================================

TARGET = $(call binary_target,$(BINARY))

all: $(TARGET)
	@ echo "$(TARGET) is up to date"

$(TARGET): $(OBJECTS)
	$(call mkdirhier,$(BINDIR))
	$(call make_bin,$(BINARY),$(OBJECTS),$(LIBRARIES))
	$(ECHONL)

##==============================================================================
##
## clean
##
##==============================================================================

clean:
	$(RM) $(OBJECTS) $(TARGET) $(CLEAN) depend.mak
	$(ECHONL)

##==============================================================================
##
## install/uninstall:
##
##==============================================================================

ifdef INSTALL
install:
	$(call mkdirhier,$(DESTDIR)$(BINDIR_OPT))
	$(call install_bin,$(BINARY))
	$(ECHONL)

uninstall:
	$(call uninstall_bin,$(BINARY))
	$(ECHONL)
endif
