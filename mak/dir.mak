## recursive execution of the defined targets.

.PHONY: install_mak

all:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i all $(NL) )

depend:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i depend $(NL) )

clean:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i clean $(NL) )

tests:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i tests $(NL) )

live:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i live $(NL) )

gen:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i gen $(NL) )

sub:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i sub $(NL) )

genclass:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i genclass $(NL) )

genprov:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i genprov $(NL) )

genmod:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i genmod $(NL) )

regmod:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i regmod $(NL) )

insmod:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i insmod $(NL) )

rmmod:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i rmmod $(NL) )

install:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i install $(NL) )

uninstall:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i uninstall $(NL) )

chksrc:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i chksrc $(NL) )
	
register-sfcb:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i register-sfcb $(NL) )

vg:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i vg $(NL) )
	

