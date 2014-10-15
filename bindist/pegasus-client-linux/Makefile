ifndef PREFIX
  PREFIX=/usr/ws/sdk/pegasus
endif

ifndef VERSION
  VERSION=2.7.0
endif

##==============================================================================

ifndef PEGASUS_ROOT
    $(error "Please define PEGASUS_ROOT")
endif

ifndef PEGASUS_HOME
    $(error "Please define PEGASUS_HOME")
endif

ifndef PEGASUS_PLATFORM
    $(error "Please define PEGASUS_PLATFORM")
endif

.PHONY: bindist clean build incdir libdir bindir

NAME=pegasus-client-$(VERSION)-linux-$(MACHINE)
DESTDIR=$(shell pwd)/$(NAME)
export EXTRA_LINK_ARGUMENTS=-Xlinker -rpath -Xlinker $(PREFIX)/lib
INCLUDE=$(PEGASUS_ROOT)/InterfaceArchive/v002005/include

MACHINE=$(shell uname -m)
BINDIR=$(DESTDIR)/$(PREFIX)/bin
LIBDIR=$(DESTDIR)/$(PREFIX)/lib
INCDIR=$(DESTDIR)/$(PREFIX)/include
TARGET=$(NAME).tar.gz

$(TARGET): build incdir libdir bindir extras
	tar zcvf $(TARGET) $(NAME)
	@ echo "Created $(TARGET)"

clean:
	( cd $(PEGASUS_ROOT)/src/Pegasus/Common; make clean )
	( cd $(PEGASUS_ROOT)/src/Pegasus/Client; make clean )
	rm -rf $(DESTDIR)/$(PREFIX)
	rm -rf $(NAME)
	rm -f $(TARGET)

build:
	( cd $(PEGASUS_ROOT)/src/Pegasus/Common; make )
	( cd $(PEGASUS_ROOT)/src/Pegasus/Client; make )

CONFIG_H=$(INCDIR)/Pegasus/Common/Config.h

incdir:
	mkdir -p $(DESTDIR)/$(PREFIX)/include/Pegasus
	cp -r $(INCLUDE)/Pegasus/Common $(INCDIR)/Pegasus
	cp -r $(INCLUDE)/Pegasus/Client $(INCDIR)/Pegasus
	rm -f $(CONFIG_H)
	echo "#ifndef PEGASUS_PLATFORM_$(PEGASUS_PLATFORM)" >> $(CONFIG_H)
	echo "#  define PEGASUS_PLATFORM_$(PEGASUS_PLATFORM)" >> $(CONFIG_H)
	echo "#endif" >> $(CONFIG_H)
	cat $(INCLUDE)/Pegasus/Common/Config.h >> $(CONFIG_H)

libdir:
	mkdir -p $(DESTDIR)/$(PREFIX)/lib
	cp $(PEGASUS_HOME)/lib/libpegclient.so* $(LIBDIR)
	cp $(PEGASUS_HOME)/lib/libpegcommon.so* $(LIBDIR)

bindir:
	mkdir $(DESTDIR)/$(PREFIX)/bin

extras:
	cp install.sh $(DESTDIR)
	cp -r examples $(DESTDIR)/$(PREFIX)
	echo "PREFIX=$(PREFIX)" > $(DESTDIR)/$(PREFIX)/examples/config.mak

