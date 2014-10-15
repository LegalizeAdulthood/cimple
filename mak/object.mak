%$(OBJ) : %.cpp
	$(call make_obj)
	@ $(ECHO)

%$(OBJ) : %.c
	$(call make_c_obj)
	@ $(ECHO)
