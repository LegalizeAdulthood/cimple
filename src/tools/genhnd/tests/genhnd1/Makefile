TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genhnd1

SOURCES = \
    Assoc1.cpp \
    Assoc2.cpp \
    Class1.cpp \
    Class2.cpp \
    Class3.cpp \
    main.cpp \
    Part.cpp \
    President.cpp \
    repository.cpp \
    Successor.cpp \
    Whole.cpp \
    SuperClass.cpp \
    SubClass.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

CLASSES = Class1 Class2 Class3 Assoc1 Assoc2 President Successor Whole SubClass SuperClass

gen:
	$(BINDIR)/genclass -r $(CLASSES)
	$(BINDIR)/genhnd $(CLASSES)

vg:
	$(VALGRIND) $(TARGET)

