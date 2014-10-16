TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_file2c

SOURCES = main.cpp

tests:
	$(TARGET)

main.cpp: test.h
test.h: test.txt
	$(BINDIR)/file2c test.txt -n TEST_FILE2C > test.h

include $(TOP)/mak/rules.mak
