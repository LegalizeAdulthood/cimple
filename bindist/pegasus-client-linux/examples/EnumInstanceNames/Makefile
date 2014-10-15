include ../config.mak
TARGET=EnumInstancesNames
INCDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib
RPATH=-Xlinker -rpath -Xlinker $(LIBDIR)

all:
	g++ -Wall -O2 -I$(INCDIR) -o $(TARGET) main.cpp -L $(LIBDIR) -lpegclient -lpegcommon $(RPATH)

clean:
	rm -f $(TARGET)
