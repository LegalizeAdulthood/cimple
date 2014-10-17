TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_serialize

GENCLASS_SOURCES = \
    All_Embedded.cpp \
    All_Properties.cpp

SOURCES = \
	$(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass All_Properties All_Embedded

