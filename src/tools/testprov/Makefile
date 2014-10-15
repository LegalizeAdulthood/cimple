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
	$(TARGET) $(SHLIB) Person $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) Person)"
	$(TARGET) $(SHLIB) Link $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) Link)"
	$(TARGET) $(SHLIB) Example $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) Example)"
	$(TARGET) $(SHLIB) Fan $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) Fan)"
ifdef CIMPLE_UNIX
	$(TARGET) $(SHLIB) UnixUser $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) UnixUser)"
endif
	$(TARGET) $(SHLIB) LinuxComputerSystem $(TO_DEV_NULL)
	@ $(ECHO) "+++++ passed all tests ($(TARGET) LinuxComputerSystem)"

CLEAN += .dev.null
