TOP = ../../..
include $(TOP)/mak/config.mak

## Note that this produces a single executable because the
## the cimplemof is a non-shared library.

INSTALL=1

BINARY = mof2html

SOURCES = main.cpp

LIBRARIES = cimplemof

INCLUDES += -I..

include $(TOP)/mak/rules.mak

run:
	$(MAKE) -C cim218
