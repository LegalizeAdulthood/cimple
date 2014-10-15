##
##	Shared library makefile
##      includes targets to:
##         - make shared libraries
##         - clean object files from shared libraries
##         - install and uninstall shared libraries
##
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
##    remove all of the object files and call the platform
##    specific clean_shlib
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
## NOTE: Depends on Makefile variables INSTALL or INSMOD
##       Uses target insmod if MODULE keyword set in Makefile.
##          MODULE used for provider installation
##       Uses target install, uninstall if INSTALL keyword set in Makefile
##          INSTALL used for shared library installation.
##       Install installs header files in addition to the shared library files.
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
