###
###  This Makefile creates the options.h file located in the
##   cimple/src/cimple directory. It will update this file
##   for each change of the config.options file.
TOP = ../..
include $(TOP)/mak/config.mak

ifdef CIMPLE_WINDOWS_MSVC
QT:=
else
QT:="
endif

OPTIONS_H=$(TOP)/src/cimple/options.h

all: $(OPTIONS_H)

### target is cimple/config.options

$(OPTIONS_H): ../../config.options
	echo // > $(OPTIONS_H)
	echo //  This file built by CIMPLE .  See src/options/Makefile >> $(OPTIONS_H)
	echo //  It provides internal definitions for CIMPLE configure >> $(OPTIONS_H)
	echo //  options that are used within the CIMPLE code. The file is >> $(OPTIONS_H) 
	echo //  regenerated each time the configuration options >> $(OPTIONS_H)
	echo //  are changed. >> $(OPTIONS_H)
	echo //  Please do not change this file, Change options with the >> $(OPTIONS_H)
	echo //  configure script >> $(OPTIONS_H)
	echo // >> $(OPTIONS_H)

ifeq ($(OS_TYPE),windows)
	echo #define CIMPLE_PLATFORM_$(PLATFORM)>> $(OPTIONS_H)
  ifeq ($(ENABLE_STATIC_OPT),1)
	echo #define CIMPLE_STATIC>> $(OPTIONS_H)
  endif
  ifdef WITH_NAMESPACE_OPT
	echo #define CIMPLE_NAMESPACE $(WITH_NAMESPACE_OPT)>> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
	echo #define CIMPLE_ENABLE_EMBEDDED_INSTANCES>> $(OPTIONS_H)
  endif
  ifdef CIMPLEHOME_ENVVAR_OPT
	echo #define CIMPLEHOME_ENVVAR "$(CIMPLEHOME_ENVVAR_OPT)" >> $(OPTIONS_H)
  else
	echo #define CIMPLEHOME_ENVVAR "CIMPLE_HOME" >> $(OPTIONS_H)      
  endif

else
	echo $(QT)#define CIMPLE_PLATFORM_$(PLATFORM)$(QT) >> $(OPTIONS_H)
  ifeq ($(ENABLE_STATIC_OPT),1)
	echo $(QT)#define CIMPLE_STATIC$(QT) >> $(OPTIONS_H)
  endif
  ifdef WITH_NAMESPACE_OPT
	echo $(QT)#define CIMPLE_NAMESPACE $(WITH_NAMESPACE_OPT)$(QT)>> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
	echo $(QT)#define CIMPLE_ENABLE_EMBEDDED_INSTANCES$(QT) >> $(OPTIONS_H)
  endif
  ifdef CIMPLEHOME_ENVVAR_OPT
	echo $(QT)#define CIMPLEHOME_ENVVAR \"$(CIMPLEHOME_ENVVAR_OPT)\"$(QT) >> $(OPTIONS_H)
  else
	echo $(QT)#define CIMPLEHOME_ENVVAR \"CIMPLE_HOME\"$(QT) >> $(OPTIONS_H)      
  endif


endif

## Temp to confirm that the QT function works across all platforms
test:
	echo "#define CIMPLEHOME_ENVVAR \"CIMPLE_HOME\"" >> temp.txt
	echo $(QT)#defined CIMPLEHOME_ENVVAR \"CIMPLE_HOME\"$(QT) >> temp.txt

clean:
	$(call rm,$(OPTIONS_H))

include $(TOP)/mak/rules.mak
