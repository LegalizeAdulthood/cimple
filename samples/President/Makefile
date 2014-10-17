
PH=$(HOME)/dev/pegasus/home
PR=$(HOME)/dev/pegasus

GENCLASS_SOURCES = \
    President.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    President_Provider.cpp \
    module.cpp

LDPATH = -L/opt/cimple/lib -L$(PH)/lib
LIBRARIES = -lcimplepegadap -lcimple -lpegprovider -lpegcommon
INCLUDES = -I/opt/cimple/include -I$(PR)/src
FLAGS = -fPIC
RPATH = -Wl,-rpath=$(PH)/lib -Wl,-rpath=/opt/cimple/lib

all: $(SOURCES)
	gcc $(INCLUDES) $(FLAGS) $(LDPATH) $(RPATH) -shared -o libPresident.so $(SOURCES) $(LIBRARIES)


genclass $(GENCLASS_SOURCES): repository.mof
	genclass -r President

genprov:
	genprov -m -f President

PROVIDERS=$(PH)/lib

install:
	cp libPresident.so $(PROVIDERS)

# chgrp pegasus $(PROVIDERS)/libPresident.so
# chcon -t texrel_shlib_t $(PROVIDERS)/libPresident.so

uninstall:
	rm -f $(PROVIDERS)/libPresident.so

regmod:
	regmod -c $(PROVIDERS)/libPresident.so

start:
	/sbin/service tog-pegasus start

stop:
	/sbin/service tog-pegasus stop

clean:
	rm -f libPresident.so
