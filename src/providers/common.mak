ifdef CIMPLE_CMPI_MODULE
  DEFINES += -DCIMPLE_CMPI_MODULE
  LIBRARIES += cimplecmpiadap cimple
endif

ifdef CIMPLE_PEGASUS_MODULE
  DEFINES += -DCIMPLE_PEGASUS_MODULE
  LIBRARIES += cimplepegadap cimple
endif
