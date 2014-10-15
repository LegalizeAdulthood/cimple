TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_value

SOURCES = main.cpp MyClass.cpp

LIBRARIES = cimple

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

genclass:
	$(BINDIR)/genclass MyClass
