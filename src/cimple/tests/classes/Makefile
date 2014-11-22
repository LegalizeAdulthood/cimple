TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_classes

GENCLASS_SOURCES = \
    A.cpp \
    AA.cpp \
    B.cpp \
    BB.cpp \
    C.cpp \
    Employee.cpp \
    Everything.cpp \
    EverythingDefaults.cpp \
    Link.cpp \
    Manager.cpp \
    OutOfOfficeNotice.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r A AA B BB C Employee Everything \
		EverythingDefaults Link Manager OutOfOfficeNotice
