##==============================================================================
##
## CIMPLE_VXWORKS
##
##==============================================================================

CIMPLE_VXWORKS=1

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

CXX = c++arm

##==============================================================================
##
## CC
##
##==============================================================================

CC = ccarm

##==============================================================================
##
## AR
##
##==============================================================================

AR = ararm

##==============================================================================
##
## NM
##
##==============================================================================

NM = nmarm

##==============================================================================
##
## FLAGS
##
##==============================================================================

FLAGS += -ansi
FLAGS += -W
FLAGS += -Wall
FLAGS += -Wno-unused

ifdef ENABLE_DEBUG_OPT
  FLAGS += -g
else
  FLAGS += -O2
endif

ifdef CIMPLE_WERROR
  FLAGS += -Werror
endif

FLAGS += -txscale

##==============================================================================
##
## DEFINES
##
##==============================================================================

DEFINES += -DCPU=XSCALE
DEFINES += -DTOOL_FAMILY=gnu
DEFINES += -DTOOL=gnu
DEFINES += -D_WRS_KERNEL

##==============================================================================
##
## OBJ
##
##==============================================================================

OBJ = .o

##==============================================================================
##
## GCC_VERSION
##
##==============================================================================

GCC_VERSION = $(shell $(CXX) -dumpversion)

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
## _NL
##
##==============================================================================

define _NL


endef

##==============================================================================
##
## make_bin(target, objects, libraries)
##
##==============================================================================


#ccache ccarm -c -o /home/mbrasher/pegasus/VXWORKS_XSCALE_GNU/obj/Pegasus/Common/tests/String/ctdt.o -ansi -W -Wall -Wno-unused -O2 -txscale  -fdollars-in-identifiers  -DPEGASUS_USE_SYSLOGS  -DPEGASUS_NO_PASSWORDFILE -DPEGASUS_REMOVE_SERVER_CLIENT_USAGE -DCPU=XSCALE -DTOOL_FAMILY=gnu  -DTOOL=gnu  -DPEGASUS_PLATFORM_VXWORKS_XSCALE_GNU -D_WRS_KERNEL -DPEGASUS_REMOVE_TRACE -DPEGASUS_DISABLE_PROV_USERCTXT -DPEGASUS_DISABLE_LOCAL_DOMAIN_SOCKET -DPEGASUS_EMBEDDED_INSTANCE_SUPPORT -DPEGASUS_DISABLE_EXECQUERY -DPEGASUS_ENABLE_INTEROP_PROVIDER -DPEGASUS_USE_EXPERIMENTAL_INTERFACES -DPEGASUS_USE_DEPRECATED_INTERFACES -DPEGASUS_DEST_LIB_DIR=\"lib\" -DPLATFORM_COMPONENT_NAME=\"TestString\" -DPEGASUS_INTERNALONLY -I../../../../../src  /tmp/ctdt.c
#ccache ccarm -r  -nostdlib  -Wl,-X /home/WindRiver/vxworks-6.3/target/h/tool/gnu/ldscripts/link.OUT -o /home/mbrasher/pegasus/VXWORKS_XSCALE_GNU/bin/TestString /home/mbrasher/pegasus/VXWORKS_XSCALE_GNU/obj/Pegasus/Common/tests/String/ctdt.o /home/mbrasher/pegasus/VXWORKS_XSCALE_GNU/obj/Pegasus/Common/tests/String/String.o /home/mbrasher/pegasus/VXWORKS_XSCALE_GNU/lib/libpegcommon.a

MUNCH_TCL = /home/WindRiver/vxworks-6.3/host/resource/hutils/tcl/munch.tcl

LINK_OUT = /home/WindRiver/vxworks-6.3/target/h/tool/gnu/ldscripts/link.OUT

_full_libs = $(addsuffix .a,$(addprefix $(LIBDIR)/lib,$(1)))

make_bin = \
    $(NM) $(2) $(call _full_libs,$(3)) | wtxtcl $(MUNCH_TCL) -c arm > ctdt.c \
    $(_NL) \
    $(CC) -c $(FLAGS) $(DEFINES) $(SYS_INCLUDES) -o ctdt.o ctdt.c \
    $(_NL) \
    $(CC) -r -nostdlib -Wl,-X $(LINK_OUT) -o $(call binary_target,$(1)) \
    ctdt.o $(2) $(call _full_libs,$(3)) \
    $(_NL) \
    rm -f ctdt.c \
    $(_NL) \
    rm -f ctdt.o

##==============================================================================
##
## INCLUDES
##
##==============================================================================

SYS_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip

##==============================================================================
##
## make_obj
##
##==============================================================================

make_obj = $(CXX) -c $(FLAGS) $(DEFINES) $(SYS_INCLUDES) $(INCLUDES) -o $*.o $*.cpp

##==============================================================================
##
## make_c_obj -- create an object file (from a C source file).
##
##==============================================================================

make_c_obj = $(CC) -c $(FLAGS) $(DEFINES) $(SYS_INCLUDES) $(INCLUDES) -o $*.o $*.c

##==============================================================================
##
## abs_path(path)
##
##==============================================================================

abs_path = $(shell mkdir -p $(1); cd $(1); pwd)

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

uninstall_lib = $(call rm,$(DESTDIR)$(LIBDIR_OPT)/lib$(1).so \
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
