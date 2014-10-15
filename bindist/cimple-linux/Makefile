VERSION=1.1.2
PREFIX=/usr/ws/sdk/cimple
WITH_SCHEMA=/usr/ws/schema/dmtf/2.15/final/mof

##==============================================================================

ROOT=../..
MACHINE=$(shell uname -m)
DESTDIR=$(shell pwd)/$(NAME)
NAME=cimple-$(VERSION)-linux-$(MACHINE)
TARGET=$(NAME).tar.gz

CONFIG_OPTIONS = \
    --prefix=$(PREFIX) \
    --with-schema=$(WITH_SCHEMA) \
    --with-pegasus=$(PEGASUS_HOME) \
    --with-pegasus-libdir=$(PEGASUS_HOME)/lib \
    --with-pegasus-includes=$(PEGASUS_ROOT)/src \
    --with-cmpi=$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

bindist:
	( cd $(ROOT); ./configure $(CONFIG_OPTIONS) ; make distclean )
	( cd $(ROOT); ./configure $(CONFIG_OPTIONS) ; make )
	( cd $(ROOT); make DESTDIR=$(DESTDIR) install )
	rm -rf $(DESTDIR)/$(PREFIX)/share
	cp $(ROOT)/license.txt $(DESTDIR)/$(PREFIX)
	mkdir -p $(DESTDIR)/$(PREFIX)/doc
	cp $(ROOT)/doc/Using_CIMPLE.pdf $(DESTDIR)/$(PREFIX)/doc
	cp install.sh $(DESTDIR)
	tar zcvf $(TARGET) $(NAME)
	@ echo "Created $(TARGET)"

clean:
	rm -rf $(TARGET)
	rm -rf $(NAME)
