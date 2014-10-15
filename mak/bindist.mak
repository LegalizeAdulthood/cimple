DESTDIR=$(HOME)/install
PREFIX=/usr/ws/sdk/cimple
WITH_SCHEMA=/usr/ws/schema/dmtf/2.15/final/mof
#export RPATH1=/usr/ws/sdk/pegasus/lib

bindist:
	./configure --prefix=$(PREFIX) --with-schema=$(WITH_SCHEMA) --with-pegasus=$(PEGASUS_HOME) --with-pegasus-libdir=$(PEGASUS_HOME)/lib --with-pegasus-includes=$(PEGASUS_ROOT)/src --with-cmpi=$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI
	make
	make DESTDIR=$(DESTDIR) install
	rm -rf $(DESTDIR)/$(PREFIX)/share
	cp license.txt $(DESTDIR)/$(PREFIX)
	mkdir -p $(DESTDIR)/$(PREFIX)/doc
	cp doc/Using_CIMPLE.pdf $(DESTDIR)/$(PREFIX)/doc
