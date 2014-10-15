TOP = $(HOME)/cimple
include $(TOP)/mak/config.mak

all: cim211 cim211 cim212 cim212 cim2131 cim2131 cim214 cim214

cim211:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim211 genclass
	$(MAKE) -f schema.mak

cim211e:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim211e genclass
	$(MAKE) -f schema.mak

cim212:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim212 genclass
	$(MAKE) -f schema.mak

cim212e:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim212e genclass
	$(MAKE) -f schema.mak

cim2131:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim2131 genclass
	$(MAKE) -f schema.mak

cim2131e:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim2131e genclass
	$(MAKE) -f schema.mak

cim214:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim214 genclass
	$(MAKE) -f schema.mak

cim214e:
	$(MAKE) -f schema.mak clean
	$(MAKE) -f schema.mak CIMPLE_MOF_PATH=$(HOME)/cim/cim214e genclass
	$(MAKE) -f schema.mak

clean:
	$(MAKE) -f schema.mak clean

include $(TOP)/mak/rules.mak
