TARGET = $(BIN)/$(BINARY)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN)
ifdef STATIC_LIBSTDCXX
	cp $(STATIC_LIBSTDCXX) $(LIB)
endif
	$(CXX) $(FLAGS) $(RPATH_OPT) -o $(TARGET) $(OBJECTS) -L$(LIB) $(LIBRARIES)

size:
	size $(TARGET)

gen:

include $(TOP)/mak/sub.mak
