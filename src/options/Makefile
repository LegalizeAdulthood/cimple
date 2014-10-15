TOP = ../..
include $(TOP)/mak/config.mak

OPTIONS_H=$(TOP)/src/cimple/options.h

all: $(OPTIONS_H)

$(OPTIONS_H):
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
endif

include $(TOP)/mak/rules.mak
