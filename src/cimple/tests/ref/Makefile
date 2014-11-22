TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_ref

GENCLASS_SOURCES = \
    X.cpp \
    Y.cpp \
    repository.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r X Y

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
