###
###  This Makefile creates the options.h file located in the
##   cimple/src/cimple directory. It will update this file
##   for each change of the config.options file.
TOP = ../..
include $(TOP)/mak/config.mak

## Define the differences between windows/MSVC and other shells/compilers with
## respect to quote marks for the define commands
ifdef CIMPLE_WINDOWS_MSVC
QT:=
DBQT:="
ECHOEMPTYLINE=echo.
else
QT:="
DBQT:=\"
ECHOEMPTYLINE= echo "" 
endif

OPTIONS_H=$(TOP)/src/cimple/options.h

all: $(OPTIONS_H)

### target is cimple/config.options. Build the #define statements that
### make up this file

$(OPTIONS_H): ../../config.options
	echo // > $(OPTIONS_H)
	echo //  This file built by CIMPLE using src/options/Makefile >> $(OPTIONS_H)
	echo //  It provides internal definitions for CIMPLE configure >> $(OPTIONS_H)
	echo //  options that are used within the CIMPLE code. The file is >> $(OPTIONS_H) 
	echo //  regenerated each time the configuration options >> $(OPTIONS_H)
	echo //  file is changed. >> $(OPTIONS_H)
	echo //  Please do not change this file, Change options with the >> $(OPTIONS_H)
	echo //  configure script or the config.options file >> $(OPTIONS_H)
	echo // >> $(OPTIONS_H)

ifeq ($(OS_TYPE),windows)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo // Define the Current target platform
	echo #define CIMPLE_PLATFORM_$(PLATFORM)>> $(OPTIONS_H)
  ifeq ($(ENABLE_STATIC_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo #define CIMPLE_STATIC>> $(OPTIONS_H)
  endif
  ifdef WITH_NAMESPACE_OPT
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo #define CIMPLE_NAMESPACE $(WITH_NAMESPACE_OPT)>> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo // The embedded instance functionality is enabled in config.options >> $(OPTIONS_H)
	echo #define CIMPLE_ENABLE_EMBEDDED_INSTANCES>> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_SCHEDULER_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo // The scheduler functionality is enabled in config.options >> $(OPTIONS_H)
	echo #define CIMPLE_ENABLE_SCHEDULER>> $(OPTIONS_H)
  endif
  ifeq ($(DISABLE_LOG_MACROS_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo // Disables compile of the macros in log.h >> $(OPTIONS_H)
	echo #define DISABLE_LOG_MACROS_OPT>> $(OPTIONS_H)
  endif
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo // Define  the name of the env var used for runtime home >> $(OPTIONS_H)
  ifdef CIMPLEHOME_ENVVAR_OPT
	echo #define CIMPLEHOME_ENVVAR "$(CIMPLEHOME_ENVVAR_OPT)" >> $(OPTIONS_H)
  else
	echo #define CIMPLEHOME_ENVVAR "CIMPLE_HOME" >> $(OPTIONS_H)      
  endif

## definitions for non-windows platforms.  
else
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)#define CIMPLE_PLATFORM_$(PLATFORM)$(QT) >> $(OPTIONS_H)
  ifeq ($(ENABLE_STATIC_OPT),1)
	echo $(QT)#define CIMPLE_STATIC$(QT) >> $(OPTIONS_H)
  endif
  ifdef WITH_NAMESPACE_OPT
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)#define CIMPLE_NAMESPACE $(WITH_NAMESPACE_OPT)$(QT)>> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)// The embedded instance functionality is enabled in config.options$(QT) >> $(OPTIONS_H)
	echo $(QT)#define CIMPLE_ENABLE_EMBEDDED_INSTANCES$(QT) >> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_SCHEDULER_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)// The scheduler functionality is enabled in config.options$(QT) >> $(OPTIONS_H)
	echo $(QT)#define CIMPLE_ENABLE_SCHEDULER$(QT) >> $(OPTIONS_H)
  endif
  ifeq ($(DISABLE_LOG_MACROS_OPT),1)
	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)// Disables compile of the macros in log.h$(QT) >> $(OPTIONS_H)
	echo $(QT)#define DISABLE_LOG_MACROS_OPT$(QT)>> $(OPTIONS_H)
  endif

	$(ECHOEMPTYLINE) >> $(OPTIONS_H)
	echo $(QT)// Define the name of the env var used for runtime home$(QT) >> $(OPTIONS_H)
  ifdef CIMPLEHOME_ENVVAR_OPT
	echo $(QT)#define CIMPLEHOME_ENVVAR $(DBQT)$(CIMPLEHOME_ENVVAR_OPT)$(DBQT)$(QT) >> $(OPTIONS_H)
  else
	echo $(QT)#define CIMPLEHOME_ENVVAR $(DBQT)CIMPLE_HOME$(DBQT)$(QT) >> $(OPTIONS_H)      
  endif

endif

	echo // END_OF_FILE >> $(OPTIONS_H)

##Confirm that the QT function works across all platforms
## Note that this is not an automatic test.
test:
	echo "#define CIMPLEHOME_ENVVAR \"CIMPLE_HOME\"" > result.txt
	echo $(QT)#define CIMPLEHOME_ENVVAR $(DBQT)CIMPLE_HOME$(DBQT)$(QT) >> result.txt
	$(DIFF) result.txt result.master
	$(RM) result.txt

clean:
	$(call rm,$(OPTIONS_H))
	$(RM) result.txt

include $(TOP)/mak/rules.mak
