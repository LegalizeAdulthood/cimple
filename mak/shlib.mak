TARGET = $(LIB)/lib$(SH_LIBRARY).so

$(TARGET): $(OBJECTS)
	mkdir -p $(LIB)
ifdef STATIC_LIBSTDCXX
	cp $(STATIC_LIBSTDCXX) $(LIB)
endif
	$(CXX) $(RPATH_OPT) $(LINK_FLAGS) -shared -o $(TARGET) $(OBJECTS) $(LIBRARIES)

size:
	size $(TARGET)

gen:

load:
	$(BIN)/dlopen $(TARGET)

include $(TOP)/mak/sub.mak
