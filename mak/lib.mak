TARGET = $(LIB)/lib$(LIBRARY).a

$(TARGET): $(OBJECTS)
	mkdir -p $(LIB)
	$(AR) $(AR_OPTS) $(TARGET) $(OBJECTS)

size:
	size $(TARGET)

gen:

include $(TOP)/mak/sub.mak
