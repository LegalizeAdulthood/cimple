TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_value

GENCLASS_SOURCES = MyClass.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

run:
	$(TARGET)

## This will be moved to live after we define DIFF through all possible
## platforms.
runtest:
	$(TARGET) >result
	$(DIFF) result result.master
	$(RM) result

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full  $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass MyClass
