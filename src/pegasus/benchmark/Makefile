TOP = ../../..
include $(TOP)/mak/config.mak

DIRS = Benchmark1 Benchmark2 Benchmark3 Benchmark4 Create1 Create2

include $(TOP)/mak/dir.mak

CACHEGRIND=/opt/valgrind/bin/valgrind --tool=cachegrind

reg:
	$(MAKE) -C Benchmark1 reg
	$(MAKE) -C Benchmark2 reg
	$(MAKE) -C Benchmark3 reg
	$(MAKE) -C Benchmark4 reg

bench1: start
	CLI ei -niq Benchmark1 --sum --t
	cimserver -s

bench2: start
	CLI ei -niq Benchmark2 --sum --t
	cimserver -s

bench3: start
	CLI ei -niq Benchmark3 --sum --t
	cimserver -s

bench4: start
	CLI ei -niq Benchmark4 --sum --t
	cimserver -s

start:
	rm -f cachegrind.out.*
	$(CACHEGRIND) cimserver
	sleep 5

load1:
	loadmod $(LIB_DIR)/libBenchmark1Provider.so.1 Benchmark1_Provider

load2:
	loadmod $(LIB_DIR)/libBenchmark2Provider.so.1 Benchmark2_Provider

PID=$(shell echo cachegrind.out.* | cut -d. -f3)
ann:
	cg_annotate --$(PID) --auto=yes > cachegrind.txt
	vi cachegrind.txt
