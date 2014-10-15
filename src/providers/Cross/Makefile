TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleCross

SOURCES = \
    Cross.cpp \
    Cross_Provider.cpp \
    Left.cpp \
    Left_Provider.cpp \
    Right.cpp \
    Right_Provider.cpp \
    module.cpp \
    repository.cpp

#CIMPLE_PEGASUS_MODULE=1
CIMPLE_CMPI_MODULE=1
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/PG_InterOp -n root/cimv2 -c -s $(TARGET)

genclass:
	$(BINDIR)/genclass -r Cross

genprov:
	$(BINDIR)/genprov Cross
	$(BINDIR)/genprov Left
	$(BINDIR)/genprov Right

genmod:
	$(BINDIR)/genmod Cross Cross Left Right

regLeft:
	$(BINDIR)/regmod -n Left -c $(TARGET) Left

regRight:
	$(BINDIR)/regmod -n Right -c $(TARGET) Right

regCross:
	$(BINDIR)/regmod -n Left -n Right -c $(TARGET) Cross

