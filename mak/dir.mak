
all:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i $(NEWLINE) )

depend:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i depend $(NEWLINE) )

clean:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i clean $(NEWLINE) )

tests:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i tests $(NEWLINE) )

gen:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i gen $(NEWLINE) )

sub:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i sub $(NEWLINE) )

genclass:
	@ $(foreach i, $(DIRS), $(MAKE) -C $i genclass $(NEWLINE) )
