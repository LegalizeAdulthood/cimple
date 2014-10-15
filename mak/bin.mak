##==============================================================================
##
## target:
##
##==============================================================================

TARGET = $(call binary_target,$(BINARY))

LINK_TARGETS = $(call link_clean_targets,$(BINARY))

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
## TODO - make the manifest delete windows only.
## TODO -- Windows delete pdb files also
clean:
	echo CLEAN = $(CLEAN)  link_targets $(LINK_TARGETS)
	$(call rm,$(OBJECTS) $(TARGET) $(CLEAN) \
	    $(LINK_TARGETS) \
	    depend.mak)
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

##==============================================================================
##
## share:
##
##==============================================================================

share:
	$(cp) $(TARGET) /share
