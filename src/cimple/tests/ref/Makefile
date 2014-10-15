TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_ref

SOURCES = main.cpp \
          X.cpp \
	  Y.cpp \
	  repository.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r X Y

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
