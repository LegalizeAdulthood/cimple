###
###  This Makefile creates the options.h file located in the
##   cimple/src/cimple directory. It will update this file
##   for each change of the config.options file.
TOP = ../..
include $(TOP)/mak/config.mak

OPTIONS_H=$(TOP)/src/cimple/options.h

all: $(OPTIONS_H)

### target is cimple/config.options

$(OPTIONS_H): ../../config.options
ifeq ($(PLATFORM),WIN32_IX86_MSVC)
	echo #define CIMPLE_PLATFORM_$(PLATFORM)> $(OPTIONS_H)
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
	echo "#define CIMPLE_PLATFORM_$(PLATFORM)" > $(OPTIONS_H)
  ifeq ($(ENABLE_STATIC_OPT),1)
	echo "#define CIMPLE_STATIC" >> $(OPTIONS_H)
  endif
  ifdef WITH_NAMESPACE_OPT
	echo "#define CIMPLE_NAMESPACE $(WITH_NAMESPACE_OPT)">> $(OPTIONS_H)
  endif
  ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
	echo "#define CIMPLE_ENABLE_EMBEDDED_INSTANCES" >> $(OPTIONS_H)
  endif
  ifdef CIMPLEHOME_ENVVAR_OPT
	echo "#define CIMPLEHOME_ENVVAR \"$(CIMPLEHOME_ENVVAR_OPT)\"" >> $(OPTIONS_H)
  else
	echo "#define CIMPLEHOME_ENVVAR \"CIMPLE_HOME\"" >> $(OPTIONS_H)      
  endif


endif



clean:
	$(call rm,$(OPTIONS_H))

include $(TOP)/mak/rules.mak
