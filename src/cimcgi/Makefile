TOP = ../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplcimcgi

SOURCES = module.cpp 

LIBRARIES = cimple cmplrep

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

genclass:

reg:
	$(BIN_DIR)/regmod -c $(TARGET)
