TOP = $(HOME)/cimple
include $(TOP)/mak/config.mak

SHARED_LIBRARY = repository

SOURCES = $(wildcard *.cpp)

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -s -r

CLEAN += $(wildcard *.cpp *.h)
