##==============================================================================
##
## target:
##
##==============================================================================

TARGET=$(call shlib_target,$(SHARED_LIBRARY))

all: $(TARGET)
	@ echo "$(TARGET) is up to date"

$(TARGET): $(OBJECTS)
	$(call mkdirhier,$(BINDIR))
	$(call mkdirhier,$(LIBDIR))
	$(call make_shlib,$(SHARED_LIBRARY),$(OBJECTS),$(LIBRARIES))
	$(ECHONL)

##==============================================================================
##
## clean:
##
##==============================================================================

CLEAN += $(OBJECTS)

clean: 
	$(call rm,$(CLEAN))
	$(call clean_shlib,$(SHARED_LIBRARY))
	$(ECHONL)

##==============================================================================
##
## install/uninstall:
##
##==============================================================================

_INCDIR = $(INCLUDEDIR_OPT)/$(INSTALL_HEADERS_DIR)

ifdef INSTALL

install: uninstall
	$(call mkdirhier,$(DESTDIR)$(_INCDIR))
	$(foreach i, $(INSTALL_HEADERS), \
            $(call cp,$i $(DESTDIR)$(_INCDIR)/$(i)) $(NL))
	$(call mkdirhier,$(DESTDIR)$(LIBDIR_OPT))
	$(call mkdirhier,$(DESTDIR)$(BINDIR_OPT))
	$(call install_shlib,$(SHARED_LIBRARY))
	$(ECHONL)

uninstall:
	$(call uninstall_shlib,$(SHARED_LIBRARY))
	$(foreach i, $(INSTALL_HEADERS), \
            $(call rm,$(DESTDIR)$(_INCDIR)/$i) $(NL))
	$(ECHONL)

endif

ifdef MODULE

insmod:
	$(call mkdirhier,$(LIBDIR_OPT))
	$(call install_shlib,$(SHARED_LIBRARY))
	$(ECHONL)

rmmod:
	$(call uninstall_shlib,$(SHARED_LIBRARY))
	$(ECHONL)

endif
