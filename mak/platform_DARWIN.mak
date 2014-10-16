##==============================================================================
##
## CIMPLE_UNIX
##
##==============================================================================

CIMPLE_UNIX=1

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

cp = cp $(1) $(2)

##==============================================================================
##
## rm(files)
##
##==============================================================================

rm = rm -f $(1)

##==============================================================================
##
## mkdirhier(directory)
##
##==============================================================================

mkdirhier = mkdir -p $(1)

##==============================================================================
##
## rmdirhier(directory)
##
##==============================================================================

rmdirhier = rm -rf $(1)

##==============================================================================
##
## cpdirhier(source_dir, destination_dir)
##
##==============================================================================

cpdirhier = cp -r $(1) $(2)

##==============================================================================
##
## CXX
##
##==============================================================================

ifndef CXX
  CXX = g++
endif

##==============================================================================
##
## CC
##
##==============================================================================

ifndef CC
  CC = gcc
endif

##==============================================================================
##
## AR
##
##==============================================================================

ifndef AR
  AR = ar
endif

##==============================================================================
##
## FLAGS
##
##==============================================================================

FLAGS = -Wall -W -Wno-unused -fPIC

ifdef CIMPLE_WERROR
  FLAGS += -Werror
endif

ifdef ENABLE_DEBUG_OPT
  FLAGS += -g
else
  FLAGS += -O2
endif

##==============================================================================
##
## OBJ
##
##==============================================================================

OBJ = .o

##==============================================================================
##
## SIZE_OPTIMIZATION_FLAGS
##
##==============================================================================

SIZE_OPTIMIZATION_FLAGS = -fno-exceptions

##==============================================================================
##
## GCC_VERSION
##
##==============================================================================

GCC_VERSION = $(shell $(CXX) -dumpversion)

##==============================================================================
##
## -fvisibility
##
##==============================================================================

ifeq ($(shell expr $(GCC_VERSION) '>=' 4.0), 1)
  FLAGS += -fvisibility=hidden
endif

##==============================================================================
##
## DEFINES
##
##==============================================================================

DEFINES += -D_GNU_SOURCE

##==============================================================================
##
## LINK_FLAGS
##
##==============================================================================

LINK_FLAGS +=

##==============================================================================
##
## LDPATH
##
##==============================================================================

ifeq ($(WITH_PEGASUS_LIBDIR_OPT),)
  LDPATH = $(addprefix -L,$(LIBDIR))
else
  LDPATH = $(addprefix -L,$(LIBDIR) $(WITH_PEGASUS_LIBDIR_OPT))
endif

##==============================================================================
##
## LD_LIBRARY_PATH
##
##==============================================================================

ifeq ($(WITH_PEGASUS_LIBDIR_OPT),)
  export LD_LIBRARY_PATH=$(LIBDIR)
else
  export LD_LIBRARY_PATH=$(LIBDIR):$(WITH_PEGASUS_LIBDIR_OPT)
endif

##==============================================================================
##
## RPATH
##
##==============================================================================

RPATH_OPTION = -Wl,-rpath=
RPATH_ARGS = $(LIBDIR_OPT)

ifdef RPATH1
 RPATH_ARGS += $(RPATH1)
endif

ifdef RPATH2
 RPATH_ARGS += $(RPATH2)
endif

#RPATH = $(addprefix $(RPATH_OPTION),$(RPATH_ARGS))

##==============================================================================
##
## shlib_target(SHARED_LIBRARY)
##
##==============================================================================

shlib_target = $(LIBDIR)/lib$(1).dylib

##==============================================================================
##
## lib_target(STATIC_LIRARY)
##
##==============================================================================

lib_target = $(LIBDIR)/lib$(1).a

##==============================================================================
##
## binary_target(BINARY)
##
##==============================================================================

binary_target = $(BINDIR)/$(1)

##==============================================================================
##
## _SYS_LIBS
##
##==============================================================================

_SYS_LIBS = -ldl -lpthread

##==============================================================================
##
## make_shlib(shlib, objects, libraries)
##
##==============================================================================

_full_libs = $(addprefix -l,$(1))

make_shlib = \
    $(CXX) $(RPATH) $(LINK_FLAGS) -dynamiclib \
    -o $(call shlib_target,$(1)) \
    $(2) \
    $(LDPATH) \
    $(call _full_libs,$(3)) \
    $(_SYS_LIBS) $(NL)

##==============================================================================
##
## clean_shlib(library)
##
##==============================================================================

clean_shlib = $(call rm,$(call shlib_target,$(1)) $(call lib_target,$(1)))

##==============================================================================
##
## clean_lib(library)
##
##==============================================================================

clean_lib = $(call rm,$(call shlib_target,$(1)) $(call lib_target,$(1)))

##==============================================================================
##
## make_lib(library, objects)
##
##==============================================================================

make_lib = $(AR) r $(call lib_target,$(1)) $(2)

##==============================================================================
##
## make_bin(target, objects, libraries)
##
##==============================================================================

make_bin = \
    $(CXX) $(FLAGS) $(RPATH) -o \
    $(call binary_target,$(1)) \
    $(2) \
    $(LDPATH) \
    $(call _full_libs,$(3)) \
    $(_SYS_LIBS)

##==============================================================================
##
## make_obj
##
##==============================================================================

make_obj = $(CXX) -c $(FLAGS) $(DEFINES) $(INCLUDES) -o $*.o $*.cpp

##==============================================================================
##
## make_c_obj -- create an object file (from a C source file).
##
##==============================================================================

make_c_obj = $(CC) -c $(FLAGS) $(DEFINES) $(INCLUDES) -o $*.o $*.c

##==============================================================================
##
## abs_path(path)
##
##==============================================================================

abs_path = $(shell mkdir -p $(1); cd $(1); pwd)

##==============================================================================
##
## install_shlib
##
##==============================================================================

install_shlib = \
    $(call cp,$(call shlib_target,$1) $(DESTDIR)$(LIBDIR_OPT)/lib$(1).dylib)

##==============================================================================
##
## uninstall_shlib
##
##==============================================================================

uninstall_shlib = $(call rm,$(DESTDIR)$(LIBDIR_OPT)/lib$(1).dylib \
    $(DESTDIR)$(LIBDIR_OPT)/lib$(1).a)

##==============================================================================
##
## install_lib
##
##==============================================================================

install_lib = \
    $(call cp,$(call lib_target,$1) $(DESTDIR)$(LIBDIR_OPT)/lib$(1).a)

##==============================================================================
##
## uninstall_lib
##
##==============================================================================

uninstall_lib = $(call rm,$(DESTDIR)$(LIBDIR_OPT)/lib$(1).dylib \
    $(DESTDIR)$(LIBDIR_OPT)/lib$(1).a)

##==============================================================================
##
## install_bin(BINARY)
##
##==============================================================================

install_bin = $(call cp,$(call binary_target,$(1)) \
    $(DESTDIR)$(BINDIR_OPT)/$(1))

##==============================================================================
##
## uninstall_bin(BINARY)
##
##==============================================================================

uninstall_bin = $(call rm,$(DESTDIR)$(BINDIR_OPT)/$(1))

##==============================================================================
##
## grep(pattern,path)
##
##==============================================================================

grep = $(shell grep -l $(1) $(2))

##==============================================================================
##
## ECHONL
##
##==============================================================================

ECHONL=@echo ""
