all:
	@ echo "To install patch type \"make patch\""

DIR=$(PEGASUS_ROOT)/src/Pegasus/ProviderManager2

patch:
	cp patch.diff $(DIR); 
	( cd $(DIR); patch -p0 < patch.diff; make; rm -f patch.diff )
