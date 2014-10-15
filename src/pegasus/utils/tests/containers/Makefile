TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_containers

SOURCES = main.cpp Class1.cpp Assoc1.cpp Class2.cpp Class3.cpp Class4.cpp \
    Class5.cpp Assoc2.cpp repository.cpp

LIBRARIES = cimplepegutils pegcommon cimple

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	genclass -r Class1 Assoc1 Class2 Class3 Class4 Class5 Assoc2

include ../../../check-pegasus.mak

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
