TOP = ../../..
include $(TOP)/mak/config.mak

DIRS += \
    rep \
    client1 \
    client2 \
    client3 \
    client4 \
    client5 \
    client6 \
    client7 \
    client8 \
    client9 \
    client10 \
    client11 \
    client12 \
    client13

include $(TOP)/mak/dir.mak

publish:
	$(foreach i,$(DIRS),$(MAKE) -C $i publish $(NL) )
