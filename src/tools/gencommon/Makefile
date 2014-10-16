TOP = ../../..
include $(TOP)/mak/config.mak

STATIC_LIBRARY = cimplegencommon

SOURCES = gencommon.cpp

LIBRARIES = cimplemof cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof

DEFINES += -DGENCOMMON_INTERNAL

DEFINES += -DCIMPLE_DEFAULT_SCHEMA=\"$(WITH_SCHEMA_OPT)\"

include $(TOP)/mak/rules.mak

zzz:
	echo $(DEFINES) $(SRC_DIR)
