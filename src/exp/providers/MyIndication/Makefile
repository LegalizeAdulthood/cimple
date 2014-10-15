include $(PEGASUS_ROOT)/mak/config.mak

DIR = cimple/pegasus/indications/MyIndication/Provider

LIBRARY = MyIndicationProvider

LIBRARIES = \
    pegqueryexpression \
    pegprovider \
    pegcql \
    pegwql \
    pegquerycommon \
    pegclient \
    pegcommon
	
SOURCES = MyIndicationProvider.cpp

include $(PEGASUS_ROOT)/mak/dynamic-library.mak

register:
	cimmofl MyIndication.mof
	cimmofl -n root/PG_InterOp Registration.mof
