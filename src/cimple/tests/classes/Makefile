TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_classes

SOURCES = \
    Employee.cpp \
    Link.cpp \
    main.cpp \
    Manager.cpp \
    A.cpp \
    B.cpp \
    C.cpp \
    AA.cpp \
    BB.cpp \
    repository.cpp \
    OutOfOfficeNotice.cpp \
    Everything.cpp \
    EverythingDefaults.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR) genclass Employee Manager Link A B C AA BB OutOfOfficeNotice Everything \
	EverythingDefaults
