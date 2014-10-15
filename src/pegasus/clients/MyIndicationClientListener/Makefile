DIR = cimple/pegasus/indications/MyIndication/ClientListener

include $(PEGASUS_ROOT)/mak/config.mak

PROGRAM = MyIndicationClientListener

LIBRARIES = \
    peglistener \
    pegqueryexpression \
    pegprovider \
    pegcql \
    pegwql \
    pegquerycommon \
    pegclient \
    pegcommon
	
SOURCES = MyIndicationClientListener.cpp

include $(PEGASUS_ROOT)/mak/program.mak

run:
	$(PROGRAM)

tests:

genclass:

chksrc:
	chksrc $(SOURCES)
