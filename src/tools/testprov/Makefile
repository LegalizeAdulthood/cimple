TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = testprov
SOURCES = main.cpp
LIBRARIES = -lcimpledisp -lcimpledisp -lcimple

include $(TOP)/mak/rules.mak

TO_DEV_NULL=> /dev/null

tests:
	$(TARGET) $(LIB) Person $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) Person)"
	$(TARGET) $(LIB) Link $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) Link)"
	$(TARGET) $(LIB) Example $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) Example)"
	$(TARGET) $(LIB) Fan $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) Fan)"
	$(TARGET) $(LIB) UnixUser $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) UnixUser)"
	$(TARGET) $(LIB) LinuxComputerSystem $(TO_DEV_NULL)
	@ echo "+++++ passed all tests ($(TARGET) LinuxComputerSystem)"
