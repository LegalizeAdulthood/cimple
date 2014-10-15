DIR = cimple/pegasus/indications/LampIndic/ClientListener

include $(PEGASUS_ROOT)/mak/config.mak

PROGRAM = LampIndicClientListener

LIBRARIES = \
    peglistener \
    pegqueryexpression \
    pegprovider \
    pegcql \
    pegwql \
    pegquerycommon \
    pegclient \
    pegcommon
	
SOURCES = LampIndicClientListener.cpp

include $(PEGASUS_ROOT)/mak/program.mak

run:
	$(PROGRAM)

tests:
