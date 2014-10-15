##==============================================================================
##
## target:
##
##==============================================================================

TARGET=$(call lib_target,$(STATIC_LIBRARY))

all: $(TARGET)
	@ echo "$(TARGET) is up to date"

$(TARGET): $(OBJECTS)
	$(call mkdirhier,$(LIBDIR))
	$(call make_lib,$(STATIC_LIBRARY),$(OBJECTS))
	$(ECHONL)

##==============================================================================
##
## clean:
##
##==============================================================================

CLEAN += $(OBJECTS)

clean: 
##	TODO get rid of these two lines. echo lib.mak.clean $(OBJECTS)
##	echo lib.mak.clean CLEAN = $(CLEAN)
	$(call rm,$(CLEAN))
	$(call clean_lib,$(STATIC_LIBRARY))
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
	$(foreach i, $(INSTALL_HEADERS), $(call cp,$i \
            $(DESTDIR)$(_INCDIR)/$(i)) $(NL))
	$(call mkdirhier,$(DESTDIR)$(LIBDIR_OPT))
	$(call install_lib,$(STATIC_LIBRARY))
	$(ECHONL)

uninstall:
	$(call uninstall_lib,$(STATIC_LIBRARY))
	$(foreach i, $(INSTALL_HEADERS), \
            $(call rm,$(DESTDIR)$(_INCDIR)/$(i)) $(NL))
	$(ECHONL)
endif
