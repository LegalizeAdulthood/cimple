TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = testprov
SOURCES = main.cpp
LIBRARIES = cimpledisp cimpledisp cimple

include $(TOP)/mak/rules.mak

ifdef CIMPLE_WINDOWS
  TO_DEV_NULL= > .dev.null
else
  TO_DEV_NULL= > /dev/null
endif

tests:
	$(BINARY_TARGET) $(SHLIB) Person2 $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) Person2)"
ifdef PEGASUS_HOME
	$(BINARY_TARGET) $(SHLIB) Person $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) Person)"
	$(BINARY_TARGET) $(SHLIB) Link $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) Link)"
	$(BINARY_TARGET) $(SHLIB) Example $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) Example)"
	$(BINARY_TARGET) $(SHLIB) Fan $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) Fan)"
ifdef CIMPLE_UNIX
	$(BINARY_TARGET) $(SHLIB) UnixUser $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) UnixUser)"
endif
	$(BINARY_TARGET) $(SHLIB) LinuxComputerSystem $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(BINARY_TARGET) LinuxComputerSystem)"
endif

CLEAN += .dev.null

genclass:
