##
##  Include specific make files depending on keyword.
ifdef SOURCES
  _OBJECTS = $(SOURCES:.cpp=$(OBJ))
  OBJECTS = $(_OBJECTS:.c=$(OBJ))
endif

ifdef LIBRARY
  ifdef ENABLE_STATIC_OPT
    STATIC_LIBRARY = $(LIBRARY)
  else
    SHARED_LIBRARY = $(LIBRARY)
  endif
endif

ifdef SHARED_LIBRARY
  include $(TOP)/mak/shlib.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
  include $(TOP)/mak/chksrc.mak
endif

ifdef STATIC_LIBRARY
  include $(TOP)/mak/lib.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
  include $(TOP)/mak/chksrc.mak
endif

ifdef BINARY
  include $(TOP)/mak/bin.mak
  include $(TOP)/mak/object.mak
  include $(TOP)/mak/depend.mak
  include $(TOP)/mak/chksrc.mak
endif

ifdef DIRS
  include $(TOP)/mak/dir.mak
endif

insmod:
rmmod:
regmod:
live:
genclass:
genprov:
genmod:
tests:
vg:
