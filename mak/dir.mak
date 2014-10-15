all:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i $(NL) )

depend:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i depend $(NL) )

clean:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i clean $(NL) )

tests:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i tests $(NL) )

gen:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i gen $(NL) )

sub:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i sub $(NL) )

genclass:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i genclass $(NL) )
