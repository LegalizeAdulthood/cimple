##==============================================================================
##
## CIMPLE_WINDOWS
##
##==============================================================================

CIMPLE_WINDOWS=1

##==============================================================================
##
## ECHO
##
##==============================================================================

ECHO = @echo

##==============================================================================
##
## cp(source,dest)
##
##==============================================================================

cp = copy $(subst /,\,$(1)) $(subst /,\,$(2))

##==============================================================================
##
## rm(files)
##
##==============================================================================

rm = - del /q $(subst /,\,$(1))

##==============================================================================
##
## _win_path(path)
##
##==============================================================================

_win_path = $(subst /,\,$(1))

##==============================================================================
##
## mkdirhier(directory)
##
##==============================================================================

mkdirhier = - mkdir $(subst /,\,$(1))

##==============================================================================
##
## rmdirhier(directory)
##
##==============================================================================

rmdirhier = - rmdir /q /s $(subst /,\,$(1))

##==============================================================================
##
## cpdirhier(source_dir, destination_dir)
##
##==============================================================================

cpdirhier = XCOPY /E /I /F $(subst /,\,$(1)) $(subst /,\,$(2))

##==============================================================================
##
## CXX
##
##==============================================================================

CXX = cl -nologo

##==============================================================================
##
## CC
##
##==============================================================================

CC = cl -nologo

##==============================================================================
##
## AR
##
##==============================================================================

AR = link

##==============================================================================
##
## FLAGS
##
##==============================================================================

FLAGS = -EHsc -GR -W3 -MD

ifdef DEBUG_OPT
  FLAGS += -Od -Zi
else
  FLAGS += -O2
endif

##==============================================================================
##
## OBJ
##
##==============================================================================

OBJ = .obj

##==============================================================================
##
## DEFINES
##
##==============================================================================

#DEFINES += -D_CRT_SECURE_NO_DEPRECATE

##==============================================================================
##
## LINK_FLAGS
##
##==============================================================================

#LINK_FLAGS += -L$(LIBDIR)

LINK_FLAGS += -nologo -dll

ifdef DEBUG_OPT
  LINK_FLAGS += -debug
endif

##==============================================================================
##
## LIB_FLAGS
##
##==============================================================================

LIB_FLAGS += -nologo

##==============================================================================
##
## shlib_target(name)
##
##==============================================================================

shlib_target = $(BINDIR)/$(1).dll

##==============================================================================
##
## lib_target(name)
##
##==============================================================================

lib_target = $(LIBDIR)/$(1).lib

##==============================================================================
##
## exp_target(name)
##
##==============================================================================

exp_target = $(LIBDIR)/$(1).exp

##==============================================================================
##
## binary_target(binary)
##
##==============================================================================

binary_target = $(BINDIR)/$(1).exe

##==============================================================================
##
## LDPATH
##
##==============================================================================

LDPATH = -libpath:$(subst /,\,$(LIBDIR))

ifneq ($(WITH_PEGASUS_OPT),)
  LDPATH += -libpath:$(subst /,\,$(WITH_PEGASUS_OPT)/lib)
endif

##==============================================================================
##
## _full_libs(libraries)
##
##==============================================================================

_full_libs = $(addsuffix .lib,$(1))

##==============================================================================
##
## make_shlib(shlib, objects, libraries)
##
##==============================================================================

_SYS_LIBS = ws2_32.lib advapi32.lib netapi32.lib 

make_shlib = link $(LINK_FLAGS) \
    $(LDPATH) \
    -out:$(call shlib_target,$(1)) \
    -implib:$(call lib_target,$(1)) \
    $(2) \
    $(call _full_libs,$(3)) \
    posix.lib \
    $(_SYS_LIBS) $(EXTRA_SYS_LIBS) $(NL)

##==============================================================================
##
## make_lib(static_library, objects)
##
##==============================================================================

make_lib = lib $(LIB_FLAGS) -out:$(call lib_target,$(1)) $(2)

##==============================================================================
##
## clean_shlib(library)
##
##==============================================================================

clean_shlib = \
    $(call rm,$(call shlib_target,$(1))) $(NL) \
    $(call rm,$(call lib_target,$(1))) $(NL) \
    $(call rm,$(call exp_target,$(1)))

##==============================================================================
##
## clean_lib(library)
##
##==============================================================================

clean_lib = \
    $(call rm,$(call shlib_target,$(1))) $(NL) \
    $(call rm,$(call lib_target,$(1))) $(NL) \
    $(call rm,$(call exp_target,$(1)))

##==============================================================================
##
## make_bin(target, objects, libraries)
##
##==============================================================================

make_bin = $(CXX) $(FLAGS) \
    -Fe$(call binary_target,$(1)) \
    $(2) \
    $(call _full_libs,$(3)) \
    posix.lib \
    $(_SYS_LIBS) \
    -link $(LDPATH)

##==============================================================================
##
## make_obj -- create an object file.
##
##==============================================================================

make_obj = $(CXX) -c $(FLAGS) $(DEFINES) $(INCLUDES) -Fo$*.obj $*.cpp

##==============================================================================
##
## abs_path(path)
##
##==============================================================================

abs_path = $(subst \,/,$(shell cd $(call _win_path,$(1)) && cd))

##==============================================================================
##
## INCLUDES
##
##==============================================================================

ifndef POSIX_MAKEFILE
  INCLUDES += -I$(TOP)/src/posix
endif

##==============================================================================
##
## install_shlib
##
##==============================================================================

install_shlib = \
    $(call cp,$(call shlib_target,$1) $(BINDIR_OPT)/$(1).dll) $(NL) \
    $(call cp,$(call lib_target,$1) $(LIBDIR_OPT)/$(1).lib)

##==============================================================================
##
## uninstall_shlib
##
##==============================================================================

uninstall_shlib = \
    $(call rm,$(BINDIR_OPT)/$(1).dll) $(NL) \
    $(call rm,$(LIBDIR_OPT)/$(1).lib)

##==============================================================================
##
## install_lib
##
##==============================================================================

install_lib = \
    $(call cp,$(call lib_target,$1) $(LIBDIR_OPT)/$(1).lib)

##==============================================================================
##
## uninstall_lib
##
##==============================================================================

uninstall_lib = $(call rm,$(LIBDIR_OPT)/$(1).lib)

##==============================================================================
##
## install_bin(BINARY)
##
##==============================================================================

install_bin = $(call cp,$(call binary_target,$(1)) $(BINDIR_OPT)/$(1).exe)

##==============================================================================
##
## uninstall_bin(BINARY)
##
##==============================================================================

uninstall_bin = $(call rm,$(BINDIR_OPT)/$(1).exe)

##==============================================================================
##
## grep(pattern,path)
##
##==============================================================================

grep = $(shell findstr /M /R $(1) $(subst /,\,$(2)))

##==============================================================================
##
## ECHONL
##
##==============================================================================

ECHONL=@ $(subst /,\,$(TOP)/mak/echonl.bat)

