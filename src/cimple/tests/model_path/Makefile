TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_model_path

SOURCES = main.cpp Part.cpp Glue.cpp repository.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

genclass:
	$(BINDIR)/genclass -r Part Glue
