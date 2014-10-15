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
    repository.cpp \
    OutOfOfficeNotice.cpp \

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	genclass Employee Manager Link A B C OutOfOfficeNotice
